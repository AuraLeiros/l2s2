CC = gcc
CFLAGS = -Wall -g

tp3: main.o entreeSortieLC.o biblioLC.o
	$(CC) $(CFLAGS) -o tp3 main.o entreeSortieLC.o biblioLC.o

entreSortie.o: entreeSortieLC.c entreeSortieLC.h
	$(CC) $(CFLAGS) -c entreeSortieLC.c

biblioLC.o: biblioLC.c biblioLC.h
	$(CC) $(CFLAGS) -c biblioLC.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean :
	rm -f *.o tp3
