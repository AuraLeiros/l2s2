/* Aura Leirós García - 21218034 */
/* aura.leiros@etu.sorbonne-universite.fr */
/* entreeSortieLC.c - TP3 & TP4 SDD */

#include <stdio.h>
#include "entreeSortieLC.h"
#include "biblioLC.h"


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

    Livre *curr = b->Livre;
    Livre *temp;
    char* titre = NULL;
    char* auteur = NULL;
    char* buffer = NULL;
    int numLiv;
    size_t memLen;

    /* Ouverture et vérification du fichier */
    FILE *fptr = fopen(nomfic, "a");
    if (!fptr){
        printf("Failed to open file!\n");
        exit(-1);
    }

    while(curr != NULL){
        temp = curr->suiv;

        /* Parcourir et sauvegarder les données dans des variables temporaires */
        titre = strdup(curr->titre);
        if (!titre){
            fclose(fptr);
            exit(EXIT_FAILURE);
        }
        auteur = strdup(curr->auteur);
        if (!auteur){
            free(titre);
            fclose(fptr);
            exit(EXIT_FAILURE);
        }
        numLiv = curr->num;

        /* Allocation mémoire du buffer */
        memLen = (snprintf(NULL, 0, "%s %d %s\n", titre, numLiv, auteur)) + 1;
        buffer = malloc(memLen * sizeof(char));
        if (!buffer) {
            free(titre);
            free(auteur);
            fclose(fptr);
            exit(EXIT_FAILURE); 
        }

        /* Écrire dans le fichier */
        snprintf(buffer, memLen, "%s %d %s\n", titre, numLiv, auteur);
        fprintf(fptr, "%s", buffer);

        /* Libération de la mémoire des variables temporaires */
        free(titre);
        free(auteur);
        free(buffer);

        curr=temp;
    }

    fclose(fptr);
}