CC=gcc
CFLAGS=-std=c11 -I. -Wall -Wextra
LIBS=

all: bingo

bingo: bingo.c

% : %.c
	$(CC) -o $@ $< $(CFLAGS) $(LIBS)

clean:
	rm -f bingo

.PHONY: all clean
