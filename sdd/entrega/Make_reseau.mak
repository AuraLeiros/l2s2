CC = gcc
CFLAGS = -Wall -Iinclude
LDFLAGS = -lm
.PHONY: clean

ReseauMain : ReconstitueReseau.o Reseau.o Reseau_aux.o Chaine.o Chaine_aux.o SVGwriter.o
	$(CC) -o $@ $^ $(LDFLAGS)
	rm -f *.o

ReconstitueReseau.o : src/ReconstitueReseau.c include/Reseau.h include/Reseau_aux.h
	$(CC) $(CFLAGS) -c $< -o $@

Reseau.o : src/Reseau.c include/Reseau.h include/Reseau_aux.h include/Chaine.h include/SVGwriter.h
	$(CC) $(CFLAGS) -c $< -o $@

Reseau_aux.o : src/Reseau_aux.c include/Reseau_aux.h include/Chaine.h include/Chaine_aux.h
	$(CC) $(CFLAGS) -c $< -o $@

Chaine.o : src/Chaine.c include/Chaine.h include/Chaine_aux.h include/SVGwriter.h 
	$(CC) $(CFLAGS) -c $< -o $@

Chaine_aux.o : src/Chaine_aux.c include/Chaine_aux.h include/Chaine.h
	$(CC) $(CFLAGS) -c $< -o $@

SVGwriter.o : src/SVGwriter.c include/SVGwriter.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f ReseauMain