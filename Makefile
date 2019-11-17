CC = gcc
CFLAGS = -ansi -Wall

all: cgol dyngol

cgol: cgol.o funcs.o
	$(CC) $(CFLAGS) -o cgol cgol.o funcs.o

dyngol: dyngol.o funcs.o
	$(CC) $(CFLAGS) -o dyngol dyngol.o funcs.o

cgol.o: cgol.c
	$(CC) $(CFLAGS) -c cgol.c

dyngol.o: dyngol.c
	$(CC) $(CFLAGS) -c dyngol.c

funcs.o:
	$(CC) $(CFLAGS) -c funcs.c

clean:
	rm *.o cgol dyngol
