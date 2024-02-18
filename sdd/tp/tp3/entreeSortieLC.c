/* Aura Leirós García - 21218034 */
/* aura.leiros@etu.sorbonne-universite.fr */
/* entreeSortieLC.c - TP3 & TP4 SDD */

#include <stdio.h>
#include <stdlib.h>
#include "entreeSortieLC.h"
#include "biblioLC.h"
#define BUF_SIZE 256

Biblio* charger_n_entrees(char* nomfic, int n){

    char ligne[(3 * BUF_SIZE)];
    char titre[BUF_SIZE];
    char auteur[BUF_SIZE];
    int numLiv;
    char delimiter[] = " ";
    int countLines = 0;
    char* token;
    int ch = 0;

    Biblio* newBiblio = creer_biblio();
    if (!newBiblio){
        return NULL;
    }

    FILE *fptr = fopen(nomfic, "r");
    if (!fptr){
        fprintf(stderr, "Le fichier n'a pas pu être ouvert !\n");
        return NULL;
    }

    /* Vérification que le nombre de lignes présent dans le fichier est >= n sortie du programme sinon retourne NULL */
    while ((ch = fgetc(fptr)) != EOF) {
        if (ch == '\n') {
            countLines++;
        }
    }

    if (ch != '\n' && countLines != 0) {
        countLines++;
    }

    if ((n > countLines) || (countLines == 0)) {
        fprintf(stderr, "Erreur dans le calcul du nombre de lignes dans le fichier.\n");
        fclose(fptr);
        return NULL;
    }

    /* Retourner le pointeur à l'origine avant de faire le traitement */
    rewind(fptr);

    /* Traitement du fichier */
    for (int x=1;x<=n;x++){
        
        fgets(ligne, (3 * BUF_SIZE), fptr);

        /* Tokenization de chaque élément dans une ligne */
        token = strtok(ligne, delimiter);
        numLiv = atoi(token);
        token = strtok(NULL, delimiter);
        strncpy(titre, token, BUF_SIZE);
        token = strtok(NULL, delimiter);
        strNcpy(auteur, token, BUF_SIZE);

        inserer_en_tete(newBiblio, numLiv, titre, auteur);

    }

    /* Fermeture du fichier et return du résultat */
    fclose(fptr);
    return newBiblio;
}


void enregistrer_biblio(Biblio *b, char* nomfic){

    Livre *curr = b->l;
    Livre *temp;
    char* buffer = NULL;
    size_t memLen;

    /* Ouverture et vérification du fichier */
    FILE *fptr = fopen(nomfic, "a");
    if (!fptr){
        fprintf(stderr, "Le fichier n'a pas pu être ouvert !\n");
        return;
    }

    while(curr != NULL){
        temp = curr->suiv;

        /* Calcul de la taille mémoire du buffer */
        memLen = (snprintf(NULL, 0, "%s %d %s\n", curr->titre, curr->num, curr->auteur));
        if (memLen == -1){
            fprintf(stderr, "Erreur mémoire, arrêt de la fonction\n");
            fclose(fptr);
            return;
        }

        /* Allocation du buffer, le +1 c'est pour le null terminator */
        buffer = malloc((memLen + 1) * sizeof(char));
        if (!buffer) {
            fprintf(stderr, "Erreur mémoire, arrêt de la fonction\n");
            fclose(fptr);
            return; 
        }

        /* Écriture dans le buffer */
        memLen = snprintf(buffer, (memLen + 1), "%s %d %s\n", curr->titre, curr->num, curr->auteur);
        if (memLen == -1){
            fprintf(stderr, "Erreur mémoire, arrêt de la fonction\n");
            free(buffer);
            fclose(fptr);
            return;
        }
        
        /* Écriture dans le fichier */
        fprintf(fptr, "%s", buffer);

        /* Libération de la mémoire des variables temporaires */
        free(buffer);

        curr=temp;
    }

    fclose(fptr);
}
