CC = gcc
CFLAGS = -O2 -Wall -I ..

all: adder

adder: adder.c
	$(CC) $(CFLAGS) -Og -g -o adder adder.c

clean:
	rm -f adder *~
