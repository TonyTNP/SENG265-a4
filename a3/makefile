# Makefile for compiling the student performance analyzer
# Author: Ashton Majachani
# Date: March 20, 2025

CC=gcc
CFLAGS=-c -Wall -g -DDEBUG -D_GNU_SOURCE -std=c99 -O0

all: spf_analyzer

# Linking the final executable
spf_analyzer: spf_analyzer.o list.o emalloc.o student.o
	$(CC) spf_analyzer.o list.o emalloc.o student.o -o spf_analyzer

# Compiling individual source files
spf_analyzer.o: spf_analyzer.c list.h emalloc.h student.h
	$(CC) $(CFLAGS) spf_analyzer.c

list.o: list.c list.h emalloc.h
	$(CC) $(CFLAGS) list.c

emalloc.o: emalloc.c emalloc.h
	$(CC) $(CFLAGS) emalloc.c

student.o: student.c student.h
	$(CC) $(CFLAGS) student.c

# Cleaning compiled files
clean:
	rm -rf *.o spf_analyzer output.csv
