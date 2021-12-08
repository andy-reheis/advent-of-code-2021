CC=gcc
CFLAGS=-std=c99 -I. -Wall -Wextra
LIBS=

all: lanternfish

lanternfish: lanternfish.c

% : %.c
	$(CC) -o $@ $< $(CFLAGS) $(LIBS)

clean:
	rm -f lanternfish

.PHONY: all clean
