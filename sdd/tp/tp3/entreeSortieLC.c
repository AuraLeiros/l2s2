/* Aura Leirós García - 21218034 */
/* aura.leiros@etu.sorbonne-universite.fr */
/* entreeSortieLC.c - TP3 & TP4 SDD */

#include <stdio.h>
#include <stdlib.h>
#include "entreeSortieLC.h"
#include "biblioLC.h"
#define BUF_SIZE 256

Biblio* charger_n_entrees(char* nomfic, int n){

    char ligne[BUF_SIZE];
    char titre[64];
    char auteur[64];
    int numLiv;
    char delimiter[] = " ";
    int countLines = 0;

    /* Création d'une bibliotheque */
    Biblio* newBiblio = creer_biblio();

    /* Ouverture du fichier et vérification en mémoire */
    FILE *fptr = fopen(nomfic, "r");
    if (!fptr){
        printf("failed to open file\n");
        exit(-1);
    }

    /* Vérification que le nombre de lignes present dans le fichier est >= n sortie du programme sinon exit*/
    int ch;
    while ((ch = fgetc(fptr)) != EOF) {
        if (ch == '\n') {
            countLines++;
        }
    }

    if (ch != '\n' && countLines != 0) {
        countLines++;
    }

    if (n > countLines) {
        printf("Le nombre de lignes passé en paramétre est inferieur au nombre de lignes dans le fichier\n");
        exit(EXIT_FAILURE);
    }

    /* Retourner le pointer à l'origine avant de faire le traitement */
    rewind(fptr);

    /* Traitement du fichier */
    for (int x=1;x<=n;x++){
        
        /* Obtention d'une ligne */
        fgets(ligne, BUF_SIZE, fptr);

        /* Tokenization de chaque élément dans une ligne */
        char *token = strtok(ligne, delimiter);
        numLiv = atoi(token);
        token = strtok(NULL, delimiter);
        strcpy(titre, token);
        token = strtok(NULL, delimiter);
        strcpy(auteur, token);

        /* Insertion en tête dans notre bibliothèque */
        inserer_en_tete(newBiblio, numLiv, titre, auteur);

    }

    /* Fermeture du fichier et return du résultat */
    fclose(fptr);
    return newBiblio;
}


void enregistrer_biblio(Biblio *b, char* nomfic){

    Livre *curr = b->l;
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
        memLen = (snprintf(NULL, 0, "%s %d %s\n", titre, numLiv, auteur));
        if (memLen == -1){
            free(titre);
            free(auteur);
            fclose(fptr);
            exit(EXIT_FAILURE);
        }

        /* Allocation du buffer, le +1 c'est pour le null terminator */
        buffer = malloc((memLen + 1) * sizeof(char));
        if (!buffer) {
            free(titre);
            free(auteur);
            fclose(fptr);
            exit(EXIT_FAILURE); 
        }

        /* Écriture dans le buffer */
        memLen = snprintf(buffer, memLen, "%s %d %s\n", titre, numLiv, auteur);
        if (memLen == -1){
            free(titre);
            free(auteur);
            free(buffer);
            fclose(fptr);
            exit(EXIT_FAILURE);
        }
        
        /* Écriture dans le fichier */
        fprintf(fptr, "%s", buffer);

        /* Libération de la mémoire des variables temporaires */
        free(titre);
        free(auteur);
        free(buffer);

        curr=temp;
    }

    fclose(fptr);
}