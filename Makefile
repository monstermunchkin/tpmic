PROGRAM = tpmic
PREFIX := /usr/local

CC := gcc
CFLAGS += -Wall -Wextra -pedantic-errors -O2 -std=gnu99
LIBS = -lasound

.PHONY: all install clean

all: $(PROGRAM)

$(PROGRAM): $(PROGRAM).c
	$(CC) $(CFLAGS) $(LIBS) -o $@ $<

install:
	install -Dm 4755 $(PROGRAM) $(PREFIX)/bin/$(PROGRAM)

clean:
	rm -f $(PROGRAM)
