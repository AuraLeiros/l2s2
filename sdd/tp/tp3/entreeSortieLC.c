/* Aura Leirós García - 21218034 */
/* aura.leiros@etu.sorbonne-universite.fr */
/* entreeSortieLC.c - TP3 & TP4 SDD */

#include <stdio.h>
#include "entreeSortieLC.h"

Biblio* charger_n_entrees(char* nomfic, int n){

    FILE *monFichier = fopen(nomfic, "r");
    
    if (!monFichier){
        printf("failed to open file\n")
        exit(-1)
    }


    
    

}