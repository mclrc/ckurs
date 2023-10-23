CC=gcc
CFLAGS=-std=c11 -g -Wall -lm

build: 05ex_test.c
	$(CC) 05ex_test.c -o 05ex_test.o $(CFLAGS)

test: build
	./05ex_test.o $(test)

clean:
	rm 05ex_test.o
