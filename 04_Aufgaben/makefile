CC=gcc
CFLAGS=-std=c11 -g -Wall -lm

build: 04ex_test.c
	$(CC) 04ex_test.c 04ex_helpers.c -o 04ex_test.o $(CFLAGS) 

test: build
	./04ex_test.o $(test)

clean:
	rm 04ex_test.o
