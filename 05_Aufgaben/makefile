CC=gcc
CFLAGS=-std=c11 -g -Wall -lm

build: 05ex_test.c
	$(CC) $(CFLAGS) 05ex_test.c -o 05ex_test.o

test: build
	./05ex_test.o $(test)

clean:
	rm 05ex_test.o
