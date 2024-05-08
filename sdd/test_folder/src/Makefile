CC = gcc
CFLAGS = -Wall
LDFLAGS = -lm

MainProgram : Chaine.o Chaine_aux.o Reseau.o Reseau_aux.o Hachage.o Hachage_aux.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	rm -f *.o

Chaine.o : Chaine.c Chaine_aux.c
	$(CC) $(CFLAGS) -c $< -o $@

Chaine_aux.o : Chaine_aux.c Chaine.c
	$(CC) $(CFLAGS) -c $< -o $@

Reseau.o : Reseau.c Reseau_aux.c
	$(CC) $(CFLAGS) -c $< -o $@

Reseau_aux.o : Reseau_aux.c Reseau.c
	$(CC) $(CFLAGS) -c $< -o $@

Hachage.o : Hachage.o Hachage_aux.o
	$(CC) $(CFLAGS) -c $< -o $@

Hachage_aux.o : Hachage_aux.o Hachage.o
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f ChaineTest


