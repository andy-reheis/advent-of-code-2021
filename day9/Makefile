CC=gcc
CFLAGS=-std=gnu99 -I. -Wall -Wextra
LIBS=

all: smokeBasin

smokeBasin: smokeBasin.c

% : %.c
	$(CC) -o $@ $< $(CFLAGS) $(LIBS)

clean:
	rm -f smokeBasin

.PHONY: all clean
