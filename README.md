tpmic
=====

A tool which toggles the capture device together with the LED on Thinkpads.

In order for it to work, the kernel must be compiled with the option `CONFIG_THINKPAD_ACPI_UNSAFE_LEDS=y`.
So far it has only been tested on a Thinkpad T530.

As of kernel version 3.10 or 3.11, the thinkpad\_acpi module has to be patched in order for the LED to work.
