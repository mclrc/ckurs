CC=gcc
CFLAGS=-std=c11 -g -Wall -lm

build: 09ex_test.c
	$(CC) 09ex_test.c -o 09ex_test.o $(CFLAGS)

test: build
	./09ex_test.o $(test)

clean:
	rm 09ex_test.o
