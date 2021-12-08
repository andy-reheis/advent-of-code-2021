CC=gcc
CFLAGS=-std=c99 -I. -Wall -Wextra
LIBS=

all: treacheryOfWhales

treacheryOfWhales: treacheryOfWhales.c

% : %.c
	$(CC) -o $@ $< $(CFLAGS) $(LIBS)

clean:
	rm -f treacheryOfWhales

.PHONY: all clean
