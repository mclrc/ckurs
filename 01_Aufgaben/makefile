CC=gcc
CFLAGS=-std=c11 -g -Wall -lm

build: 01ex_test.c
	$(CC) 01ex_test.c -o 01ex_test.o $(CFLAGS)

test: build
	./01ex_test.o $(test)

clean:
	rm 01ex_test.o
