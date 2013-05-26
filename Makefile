CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors -std=gnu99 -O2 -lasound

tpmic: tpmic.c
	$(CC) $(CFLAGS) -o $@ $<
