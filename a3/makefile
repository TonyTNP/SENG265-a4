CC=gcc
CFLAGS=-c -Wall -g -DDEBUG -D_GNU_SOURCE -std=c99 -O0

all: spf_analyzer

spf_analyzer: spf_analyzer.o list.o emalloc.o student.o
	$(CC) spf_analyzer.o list.o emalloc.o student.o -o spf_analyzer

spf_analyzer.o: spf_analyzer.c list.h emalloc.h student.h
	$(CC) $(CFLAGS) spf_analyzer.c

list.o: list.c list.h emalloc.h
	$(CC) $(CFLAGS) list.c

emalloc.o: emalloc.c emalloc.h
	$(CC) $(CFLAGS) emalloc.c

student.o: student.c student.h
	$(CC) $(CFLAGS) student.c

clean:
	rm -rf *.o spf_analyzer output.csv
