CC=gcc
CFLAGS=-std=gnu99 -I. -Wall -Wextra
LIBS=

all: hydrothermalVenture

hydrothermalVenture: hydrothermalVenture.c

% : %.c
	$(CC) -o $@ $< $(CFLAGS) $(LIBS)

clean:
	rm -f hydrothermalVenture

.PHONY: all clean
