/* Aura Leirós García - 21218034 */
/* aura.leiros@etu.sorbonne-universite.fr */
/* entreeSortieLC.c - TP3 & TP4 SDD */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entreeSortieLC.h"
#define BUF_SIZE 256


/* Inserer n livres dans une bibliotèque depuis un fichier */
Biblio* charger_n_entrees_lc(char* nomfic, int n){

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

    Biblio* newBiblio = creer_biblio_lc();
    if (!newBiblio){
        fprintf(stderr, "Erreur dans l'allocation mémoire\n");
        return NULL;
    }

    FILE* fptr = fopen(nomfic, "r");
    if (!fptr){
        fprintf(stderr, "Erreur dans l'ouverture du fichier\n");
        liberer_biblio_lc(newBiblio);
        return NULL;
    }

    ligne = malloc((3 * BUF_SIZE));
    if (!ligne){
            fprintf(stderr, "Erreur dans l'allocation mémoire\n");
            liberer_biblio_lc(newBiblio);
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
            liberer_biblio_lc(newBiblio);
            free(ligne);
            fclose(fptr);
            return NULL;
        }

        num = atoi(token);

        token = strtok(NULL, delimiter);
        if (!token){
            fprintf(stderr, "Erreur dans le format\n");
            liberer_biblio_lc(newBiblio);
            free(ligne);
            fclose(fptr);
            return NULL;
        }
        titre = strndup(token, BUF_SIZE);
        if (!titre){
            fprintf(stderr, "Erreur dans l'allocation mémoire\n");
            liberer_biblio_lc(newBiblio);
            free(ligne);
            fclose(fptr);
            return NULL;
        }

        token = strtok(NULL, delimiter);
        if (!token){
            fprintf(stderr, "Erreur dans le format\n");
            liberer_biblio_lc(newBiblio);
            free(ligne);
            free(titre);
            fclose(fptr);
            return NULL;
        }
        auteur = strndup(token, BUF_SIZE);
        if (!auteur){
            fprintf(stderr, "Erreur dans l'allocation mémoire\n");
            liberer_biblio_lc(newBiblio);
            free(ligne);
            free(titre);
            fclose(fptr);
            return NULL;
        }

        inserer_en_tete_lc(newBiblio, num, titre, auteur);
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

void enregistrer_biblio_lc(Biblio *b, char* nomfic){

    if(!b || !nomfic || nomfic[0] == '\0'){
        fprintf(stderr, "Un des paramètres n'est pas valide\n");
        return;
    }

    Livre *curr = b->l;
    Livre *temp = NULL;
    char* buffer = NULL;
    size_t memLen;

    /* Ouverture et vérification du fichier */
    FILE *fptr = fopen(nomfic, "w");
    if (!fptr){
        fprintf(stderr, "Le fichier n'a pas pu être ouvert !\n");
        return;
    }

    while(curr != NULL){
        temp = curr->suivant;

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

        /* Écriture dans le buffer */
        memLen = snprintf(buffer, (memLen + 1), "%s %d %s\n", curr->titre, curr->num, curr->auteur);
        if (memLen < 0){
            fprintf(stderr, "Erreur mémoire, arrêt de la fonction\n");
            free(buffer);
            fclose(fptr);
            return;
        }
        
        /* Écriture dans le fichier */
        fputs(buffer, fptr);
    
        /* Libération de la mémoire des variables temporaires */
        free(buffer);

        curr=temp;
    }

    fclose(fptr);
}

