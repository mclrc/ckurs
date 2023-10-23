CC=gcc
CFLAGS=-std=c11 -g -Wall -lm

build: 03ex_test.c
	$(CC) 03ex_test.c -o 03ex_test.o $(CFLAGS)

test: build
	./03ex_test.o $(test)

clean:
	rm 03ex_test.o
