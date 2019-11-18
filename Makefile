CC = gcc
CFLAGS = -ansi -Wall

all: cgol dynCGOL

cgol: cgol.o funcs.o
	$(CC) $(CFLAGS) -o cgol cgol.o funcs.o

dynCGOL: dynCGOL.o funcs.o
	$(CC) $(CFLAGS) -o dynCGOL dynCGOL.o funcs.o

cgol.o: cgol.c
	$(CC) $(CFLAGS) -c cgol.c

dynCGOL.o: dynCGOL.c
	$(CC) $(CFLAGS) -c dynCGOL.c

funcs.o:
	$(CC) $(CFLAGS) -c funcs.c

clean:
	rm *.o cgol dynCGOL
