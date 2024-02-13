#include <stdio.h>
#include <stdlib.h>
#include "biblioLC.h"
#include "entreeSortieLC.h"

int main(int argc, char** argv){

    if (argc != 3){
        printf("Le nombre d'arguments est different au nombre attendu\n");
        printf("Usage: <./main> <monficher.txt> <lignesalire>\n");
        return EXIT_FAILURE;
    }

    Biblio* z = charger_n_entrees(argv[1], argv[2]);

}