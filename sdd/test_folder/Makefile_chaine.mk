CC = gcc
CFLAGS = -Wall
LDFLAGS = -lm

ChaineTest : ChaineMain.o Chaine.o Chaine_aux.o SVGwriter.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	rm -f *.o

ChaineMain.o : ChaineMain.c Chaine.c Chaine_aux.c
	$(CC) $(CFLAGS) -c $< -o $@

Chaine.o : Chaine.c Chaine_aux.c
	$(CC) $(CFLAGS) -c $< -o $@

Chaine_aux.o : Chaine_aux.c
	$(CC) $(CFLAGS) -c $< -o $@

SVGwriter.o : SVGwriter.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f ChaineTest