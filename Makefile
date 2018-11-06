CC = gcc
CDEBUG = -g -Wall
CFLAGS = -Wall

default: automata.c convert.o util.o
	$(CC) -o auto automata.c convert.o util.o

debug:	automata.c convert.o util.o
	$(CC) $(CDEBUG) -o debug automata.c convert.o util.o

test-convert: convert.o unitests.c
	$(CC) $(CDEBUG) -o test unitests.c convert.o -lcunit

convert.o:	convert.c convert.h
	$(CC) $(CDEBUG) -c convert.c

util.o:	util.c
	$(CC) $(CDEBUG) -c util.c

clean:	FORCE
	rm -rf *.o a.out auto debug test

cells:	FORCE
	echo `(perl -e 'for ($$i=0; $$i < 100; $$i++) { print rand(100) % 2; }')` > cells

FORCE:	
