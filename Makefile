CC=gcc
CFLAGS=-g -Wall
all: main

cmdproc.o: cmdproc.c cmdproc.h
	$(CC) $(CFLAGS) -c cmdproc.c

main.o: main.c cmdproc.h
	$(CC) $(CFLAGS) -c main.c

main: cmdproc.o main.o
	$(CC) $(CFLAGS) cmdproc.o main.o -o main

	./main

clean:
	rm -f *.o main
