CC = gcc
CFLAGS = -Wall -Iinclude
LDFLAGS = -lm
.PHONY: clean

MainProgram : Main.o Reseau.o Reseau_aux.o Hachage.o Hachage_aux.o Chaine.o Chaine_aux.o SVGwriter.o Test.o ArbreQuat.o ArbreQuat_aux.o
	$(CC) -o $@ $^ $(LDFLAGS)
	rm -f *.o

Main.o : src/Main.c include/Hachage_aux.h include/Hachage.h include/Reseau.h include/Reseau_aux.h include/Chaine.h include/Test.h include/ArbreQuat.h
	$(CC) $(CFLAGS) -c $< -o $@

Test.o : src/Test.c include/Test.h include/Hachage_aux.h include/Hachage.h include/Reseau.h include/Reseau_aux.h include/Chaine.h include/ArbreQuat.h
	$(CC) $(CFLAGS) -c $< -o $@

ArbreQuat.o : src/ArbreQuat.c include/ArbreQuat.h include/ArbreQuat_aux.h include/Reseau.h include/Reseau_aux.h include/Chaine.h
	$(CC) $(CFLAGS) -c $< -o $@

ArbreQuat_aux.o : src/ArbreQuat_aux.c include/ArbreQuat_aux.h include/Reseau.h include/Reseau_aux.h include/Chaine.h
	$(CC) $(CFLAGS) -c $< -o $@

Hachage.o : src/Hachage.c include/Hachage.h include/Hachage_aux.h include/Reseau.h include/Reseau_aux.h include/Chaine.h
	$(CC) $(CFLAGS) -c $< -o $@

Hachage_aux.o : src/Hachage_aux.c include/Hachage_aux.h include/Hachage.h include/Reseau.h include/Reseau_aux.h include/Chaine.h
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
	rm -f MainProgram