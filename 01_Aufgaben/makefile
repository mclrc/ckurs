CC=gcc
CFLAGS=-std=c11 -g -Wall -lm

build: 01ex_test.c
	$(CC) $(CFLAGS) 01ex_test.c -o 01ex_test.o

test: build
	./01ex_test.o $(test)

clean:
	rm 01ex_test.o
