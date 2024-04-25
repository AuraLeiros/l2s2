#include "Reseau.h"
#include "Reseau_aux.h"
#include "Chaine.h"

#include <stdio.h>

#define MAX_LENGTH 256

int main(int argc, char* argv[]){

    char file_name[MAX_LENGTH];
    int maxSize = MAX_LENGTH;
    int selection;
    
    if (dataInput(file_name, &selection, maxSize) != 0){
        return -1;
    }

    FILE* f = fopen(file_name, "r");
    Chaines* ch = lectureChaines(f);
    Reseau* r = reconstitueReseauListe(ch);
    int liaisons = nbLiaisons(r);

    printf("%d", liaisons);
    

    /*
    switch (selection) {
        case 1:
            fprintf(stdout, "Vous avez choisi: Listes\n");
            nbLiaisons()
        case 2:
            fprintf(stdout, "Vous avez choisi: Tables de Hachage\n");
        case 3:
            fprintf(stdout, "Vous avez choisi: Arbres");
        default:
            fprintf(stdout, "Votre option n'est pas supporté, fermeture du programme");
            return -1;

    */
    }

