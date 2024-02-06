/* Aura Leirós García - 21218034 */
/* aura.leiros@etu.sorbonne-universite.fr */
/* entreeSortieLC.c - TP3 & TP4 SDD */

#include <stdio.h>
#include "entreeSortieLC.h"
#include "biblioLC.c"


Biblio* charger_n_entrees(char* nomfic, int n){

    char ligne[100];
    char delimiter[] = " "
    int numLiv;
    char titre[50];
    chat auteur[50];

    Biblio* maBiblio = creer_biblio();

    /* Ouverture du fichier et vérification en mémoire */
    FILE *fptr = fopen(nomfic, "r");
    if (!fptr){
        printf("failed to open file\n")
        exit(-1)
    }

    /* Traitement du fichier */
    for (x=1;x<=n;x++){

        /* Obtention d'une ligne */
        fgets(ligne, 100, fptr);

        /* Tokenization de chaque élément dans une ligne */
        char *token = strtok(ligne, delimiter);
        numLiv = atoi(token);
        token = strtok(NULL, delimiter);
        titre = strcpy(titre, token);
        token = strtok(NULL, delimiter);
        auteur = strcpy(auteur, token);

        /* Insertion en tête dans notre bibliothèque */
        inserer_en_tete(maBiblio, numLiv, titre, auteur);
    }

    /* Fermeture du fichier et return du résultat */
    fclose(fptr);
    return maBiblio;

}

void enregistrer_biblio(Biblio *b, char* nomfic){


    FILE *fptr = fopen(nomfic, "w");
    Livre *curr = b->Livre;
    int numLiv;
    char titre[50];
    char auteur[50];

    while(curr != NULL){
        





    }
}