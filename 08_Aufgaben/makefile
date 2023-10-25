CC=gcc
CFLAGS=-std=c11 -g -Wall -lm

build: 08ex_test.c
	$(CC) 08ex_test.c -o 08ex_test.o $(CFLAGS)

test: build
	./08ex_test.o $(test)

clean:
	rm 08ex_test.o
