CC=gcc
CFLAGS=-std=c11 -g -Wall -lm

build: 02ex_test.c
	$(CC) 02ex_test.c -o 02ex_test.o $(CFLAGS)

test: build
	./02ex_test.o $(test)

clean:
	rm 02ex_test.o
