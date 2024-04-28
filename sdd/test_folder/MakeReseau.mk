CC = gcc
CFLAGS = -Wall
LDFLAGS = -lm


ReseauTest : ReconstitueReseau.o Reseau.o Reseau_aux.o Chaine.o Chaine_aux.o SVGwriter.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	rm -f *.o

ReconstitueReseau.o : ReconstitueReseau.c
	$(CC) $(CFLAGS) -c $< -o $@

Reseau.o : Reseau.c
	$(CC) $(CFLAGS) -c $< -o $@ 

Reseau_aux.o : Reseau_aux.c
	$(CC) $(CFLAGS) -c $< -o $@

Chaine.o : Chaine.c Chaine_aux.c
	$(CC) $(CFLAGS) -c $< -o $@

Chaines_aux.o : Chaine_aux.c Chaine_aux.h
	$(CC) $(CFLAGS) -c $< -o $@

SVGwriter.o : SVGwriter.c
	$(CC) $(CFLAGS) -c $< -o $@
