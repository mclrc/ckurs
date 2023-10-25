CC=gcc
CFLAGS=-std=c11 -g -Wall -lm

build: 07ex_test.c
	$(CC) 07ex_test.c -o 07ex_test.o $(CFLAGS)

test: build
	./07ex_test.o $(test)

clean:
	rm 07ex_test.o
