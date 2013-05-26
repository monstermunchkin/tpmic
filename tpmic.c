/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2013 Thomas Hipp
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdio.h>
#include <string.h>
#include <alsa/asoundlib.h>

int is_mic_on(void);
void set_led(int);
void set_mic(int);

int main(int argc, char *argv[]) {
	if (argc > 1) {
		if (strncmp(argv[1], "init", 4) == 0)
			set_led(is_mic_on());
		else if (strncmp(argv[1], "toggle", 6) == 0)
			set_mic(!is_mic_on());
	}
	return 0;
}

int is_mic_on(void) {
	snd_mixer_t *handle;
	snd_mixer_selem_id_t *sid;
	const char *card = "default";
	const char *selem_name = "Capture";

	snd_mixer_open(&handle, 0);
	snd_mixer_attach(handle, card);
	snd_mixer_selem_register(handle, NULL, NULL);
	snd_mixer_load(handle);

	snd_mixer_selem_id_alloca(&sid);
	snd_mixer_selem_id_set_index(sid, 0);
	snd_mixer_selem_id_set_name(sid, selem_name);
	snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);

	int val;
	if (snd_mixer_selem_has_capture_switch(elem)) {
		snd_mixer_selem_get_capture_switch(elem, SND_MIXER_SCHN_FRONT_LEFT,
				&val);
	}

	snd_mixer_close(handle);
	return val;
}

void set_mic(int val) {
	snd_mixer_t *handle;
	snd_mixer_selem_id_t *sid;
	const char *card = "default";
	const char *selem_name = "Capture";

	snd_mixer_open(&handle, 0);
	snd_mixer_attach(handle, card);
	snd_mixer_selem_register(handle, NULL, NULL);
	snd_mixer_load(handle);

	snd_mixer_selem_id_alloca(&sid);
	snd_mixer_selem_id_set_index(sid, 0);
	snd_mixer_selem_id_set_name(sid, selem_name);
	snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);

	if (snd_mixer_selem_has_capture_switch(elem)) {
		snd_mixer_selem_set_capture_switch_all(elem, val);
	}

	snd_mixer_close(handle);
	set_led(val);
}

void set_led(int val) {
	FILE *pFile = fopen("/proc/acpi/ibm/led", "w");
	if (pFile == NULL) {
		perror("fopen");
		return;
	}
	if (val == 0)
		fputs("14 on", pFile);
	else if (val == 1)
		fputs("14 off", pFile);
	fclose(pFile);
}
