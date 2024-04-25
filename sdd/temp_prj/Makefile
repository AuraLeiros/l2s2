CC = gcc
CFLAGS = -Wall
LDFLAGS = -lm

ChaineTest : ChaineMain.o Chaine.o Chaine_aux.o  SVGwriter.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	rm -f *.o

ChaineMain.o : ChaineMain.c
	$(CC) $(CFLAGS) -c $< -o $@

Chaine.o : Chaine.c
	$(CC) $(CFLAGS) -c $< -o $@

Chaine_aux.o : Chaine_aux.c Chaine.c
	$(CC) $(CFLAGS) -c $< -o $@

SVGwriter.o : SVGwriter.c
	$(CC) $(CFLAGS) -c $< -o $@

ReseauTest : Chaine.o Chaine_aux.o ReconstitueReseau.o Reseau.o Reseau_aux.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

ReconstitueReseau.o : ReconstitueReseau.c
	$(CC) $(CFLAGS) -c $< -o $@

Reseau_aux.o : Reseau_aux.c Reseau.c
	$(CC) $(CFLAGS) -c $< -o $@

Reseau.o : Reseau.c
	$(CC) $(CFLAGS) -c $< -o $@



clean:
	rm -f *.o
	rm -f ChaineTest