/* Aura Leirós García - 21218034 */
/* aura.leiros@etu.sorbonne-universite.fr */
/* entreeSortieH.c - TP3 & TP4 SDD */

#include <stdio.h>
#include "biblioH.h"
#include "entreeSortieH.h"
#define BUF_SIZE 256

/* Inserer n livres dans une bibliotèque depuis un fichier */
BiblioH* charger_n_entrees_h(char* nomfic, int m, int n){

    int countLines = 0;
    int ch = 0;
    char* token;
    char ligne[(3 * BUF_SIZE)];
    char titre[BUF_SIZE];
    char auteur[BUF_SIZE];
    char delimiter[] = " ";
    int num;

    /* Création d'une bibliothèque et ouverture du fichier */
    BiblioH* newBiblio = creer_biblio(m);
    if (!newBiblio){
        fprintf(stderr, "Erreur dans la création d'une nouvelle bibliothéque");
        return NULL;
    }
    
    FILE *fptr = fopen(nomfic, "r");
    if (!fptr){
        fprintf(stderr, "Le fichier n'a pas pu être ouvert !\n");
        liberer_biblio(newBiblio);
        return NULL;
    }

    for (int x=1;x<=n;x++){
        if(!fgets(ligne, (3 * BUF_SIZE), fptr)){
            fprintf(stderr, "EOF, plus d'éléments á lire dans le fichier");
            printf("Le fichier contient uniquement %d éléments qui ont été introduits dans la bibliothèque.", countLines);
            break;
        }

        /* Tokenization de chaque élément dans une ligne */
        token = strtok(ligne, delimiter);
        num = atoi(token);
        token = strtok(NULL, delimiter);
        strncpy(titre, token, BUF_SIZE);
        titre[(BUF_SIZE - 1)] = '\0';
        token = strtok(NULL, delimiter);
        strncpy(auteur, token, BUF_SIZE);
        auteur[(BUF_SIZE - 1)] = '\0';

        inserer(newBiblio, num, titre, auteur);
        countLines++;
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

            if ((snprintf(buffer, (memLen + 1), "%s %d %s\n", curr->titre, curr->num, curr->auteur)) == -1){
                fprintf(stderr, "Erreur mémoire, arrêt de la fonction\n");
                free(buffer);
                fclose(fptr);
                return;
            }   

            fprintf(fptr, "%s", buffer); 
            free(buffer);
            curr = curr->suivant;
        }
    }
    fclose(fptr);
}