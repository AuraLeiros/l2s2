/* Aura Leirós García - 21218034 */
/* aura.leiros@etu.sorbonne-universite.fr */
/* entreeSortieH.c - TP3 & TP4 SDD */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "biblioH.h"
#include "entreeSortieH.h"
#define BUF_SIZE 256

BiblioH* charger_n_entrees_h(char* nomfic, int n){
    if (!nomfic || nomfic[0] == '\0' || n < 1){
        fprintf(stderr, "Un des paramètres n'est pas valide\n");
        return NULL;
    }

    char* ligne = NULL;
    char* token = NULL;
    char* titre = NULL;
    char* auteur = NULL;
    char delimiter[] = " ";
    int countLines = 0;
    int num = 0;


    int m = floor(n / 0.99);
    BiblioH* newBiblio = creer_biblio_h(m);
    if (!newBiblio){
        fprintf(stderr, "Erreur dans la création de la bibliothèque\n");
        return NULL;
    }

    FILE* fptr = fopen(nomfic, "r");
    if (!fptr){
        fprintf(stderr, "Erreur dans l'ouverture du fichier\n");
        liberer_biblio_h(newBiblio);
        return NULL;
    }

    ligne = malloc((3 * BUF_SIZE));
    if (!ligne){
            fprintf(stderr, "Erreur dans l'allocation mémoire\n");
            liberer_biblio_h(newBiblio);
            fclose(fptr);
            return NULL;
    }

    for(int x=1; x<=n; x++){

        if (!fgets(ligne, (3 * BUF_SIZE), fptr)){
            fprintf(stderr, "EOF, plus d'éléments á lire dans le fichier\n");
            printf("Le fichier contient uniquement %d éléments qui ont été introduits dans la bibliothèque.\n", countLines);
            free(ligne);
            break;
        }

        token = strtok(ligne, delimiter);
        if (!token){
            fprintf(stderr, "Erreur dans le format\n");
            liberer_biblio_h(newBiblio);
            free(ligne);
            fclose(fptr);
            return NULL;
        }

        num = atoi(token);

        token = strtok(NULL, delimiter);
        if (!token){
            fprintf(stderr, "Erreur dans le format\n");
            liberer_biblio_h(newBiblio);
            free(ligne);
            fclose(fptr);
            return NULL;
        }
        titre = strndup(token, BUF_SIZE);
        if (!titre){
            fprintf(stderr, "Erreur dans l'allocation mémoire\n");
            liberer_biblio_h(newBiblio);
            free(ligne);
            fclose(fptr);
            return NULL;
        }

        token = strtok(NULL, delimiter);
        if (!token){
            fprintf(stderr, "Erreur dans le format\n");
            liberer_biblio_h(newBiblio);
            free(ligne);
            free(titre);
            fclose(fptr);
            return NULL;
        }
        auteur = strndup(token, BUF_SIZE);
        if (!auteur){
            fprintf(stderr, "Erreur dans l'allocation mémoire\n");
            liberer_biblio_h(newBiblio);
            free(ligne);
            free(titre);
            fclose(fptr);
            return NULL;
        }

        inserer_h(newBiblio, num, titre, auteur);
        countLines++;

        free(titre);
        free(auteur);
    }

    if (ligne != NULL){
        free(ligne);
    }

    fclose(fptr);
    return newBiblio;
}

/* Stocker une bibliotheque au bon format*/
void enregistrer_biblio_h(BiblioH* b, char* nomfic){

    LivreH* curr = NULL;
    char* buffer = NULL;
    size_t memLen = 0;

    FILE *fptr = fopen(nomfic, "w");
    if (!fptr){
        fprintf(stderr, "Le fichier n'a pas pu être ouvert !\n");
        return;
    }

    for(int i=0; i < b->m; i++){
        curr = b->T[i];
        while(curr != NULL){
            /* Calcul de la taille mémoire du buffer */
            memLen = (snprintf(NULL, 0, "%s %d %s\n", curr->titre, curr->num, curr->auteur));
            if (memLen < 0){
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

            if ((snprintf(buffer, (memLen + 1), "%s %d %s\n", curr->titre, curr->num, curr->auteur)) == -1){
                fprintf(stderr, "Erreur mémoire, arrêt de la fonction\n");
                free(buffer);
                fclose(fptr);
                return;
            }   

            fputs(buffer, fptr);
            free(buffer);
            curr = curr->suivant;
        }
    }
    fclose(fptr);
}



