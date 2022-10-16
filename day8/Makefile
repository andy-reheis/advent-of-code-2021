CC=gcc
CFLAGS=-std=gnu99 -I. -Wall -Wextra
LIBS=

all: sevenSegmentSearch

sevenSegmentSearch: sevenSegmentSearch.c

% : %.c
	$(CC) -o $@ $< $(CFLAGS) $(LIBS)

clean:
	rm -f sevenSegmentSearch

.PHONY: all clean
