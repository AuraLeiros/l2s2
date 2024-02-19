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
    int num;
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

    for (int x=1; x<=n; x++){
        if (!fgets(ligne, (3 * BUF_SIZE), fptr)){
            fprintf(stderr, "EOF, plus d'éléments á lire dans le fichier");
            printf("Le fichier contient uniquement %d éléments qui ont été introduits dans la bibliothèque.");
            break;
        }

        token = strtok(ligne, delimiter);
        if (!token){
            fprintf(stderr, "Erreur dans le format");
            liberer_biblio(newBiblio);
            fclose(fptr);
            return NULL;
        }
        num = atoi(token);

        token = strtok(NULL, delimiter);
        if (token == NULL) {
            fprintf(stderr, "Titre manquant.\n");
            liberer_biblio(newBiblio);
            fclose(fptr);
            return NULL;
        }
        strncpy(titre, token, BUF_SIZE - 1);
        titre[BUF_SIZE - 1] = '\0';

        token = strtok(NULL, delimiter);
        if (token == NULL) {
            fprintf(stderr, "Auteur manquant\n");
            liberer_biblio(newBiblio);
            fclose(fptr);
            return NULL;
        }
        strncpy(auteur, token, BUF_SIZE - 1);
        auteur[BUF_SIZE - 1] = '\0';

        inserer_en_tete(newBiblio, num, titre, auteur);        
    }
}

void enregistrer_biblio(Biblio *b, char* nomfic){

    Livre *curr = b->l;
    Livre *temp;
    char* buffer = NULL;
    size_t memLen;

    /* Ouverture et vérification du fichier */
    FILE *fptr = fopen(nomfic, "w");
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
