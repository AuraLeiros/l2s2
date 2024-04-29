CC = gcc
CFLAGS = -Wall -Iinclude
LDFLAGS = -lm
.PHONY: clean

ChaineMain: ChaineMain.o Chaine.o Chaine_aux.o SVGwriter.o
	$(CC) -o $@ $^ $(LDFLAGS)
	rm -f *.o

ChaineMain.o : src/ChaineMain.c include/Chaine.h
	$(CC) $(CFLAGS) -c $< -o $@

Chaine.o : src/Chaine.c include/Chaine.h include/Chaine_aux.h include/SVGwriter.h 
	$(CC) $(CFLAGS) -c $< -o $@

Chaine_aux.o : src/Chaine_aux.c include/Chaine_aux.h include/Chaine.h
	$(CC) $(CFLAGS) -c $< -o $@

SVGwriter.o : src/SVGwriter.c include/SVGwriter.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f ChaineMain