CC=gcc
CFLAGS=-std=c11 -I. -Wall -Wextra
LIBS=

all: binaryDiagnostic

binaryDiagnostic: binaryDiagnostic.c

% : %.c
	$(CC) -o $@ $< $(CFLAGS) $(LIBS)

clean:
	rm -f binaryDiagnostic

.PHONY: all clean
