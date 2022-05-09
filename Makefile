CC=gcc
CSTANDARD=-std=c99 -D_DEFAULT_SOURCE
CWARNINGS=-Wall -Wextra -pedantic -Wno-deprecated-declarations
COPTIMIZE=-O2
CFLAGS=$(CSTANDARD) $(CWARNINGS) $(COPTIMIZE)

PREFIX=/usr/local

all: main.o files.o util.o
	$(CC) $(CFLAGS) main.o files.o util.o -o paclfs

install:
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f paclfs $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/paclfs

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

files.o: files.c
	$(CC) $(CFLAGS) -c files.c -o files.o

util.o: util.c
	$(CC) $(CFLAGS) -c util.c -o util.o

clean:
	rm -f main.o files.o util.o
