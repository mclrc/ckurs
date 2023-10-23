CC=gcc
CFLAGS=-std=c11 -g -Wall -lm

build: 06ex_test.c
	$(CC) 06ex_test.c -o 06ex_test.o $(CFLAGS)

test: build
	./06ex_test.o $(test)

clean:
	rm 06ex_test.o
