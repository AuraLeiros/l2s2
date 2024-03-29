#include <stdio.h>
#include <stdlib.h>

#include "Chaine.h"
#define BUF_SIZE 256






Chaines* lectureChaine(FILE* f){

    // Vérification que le fichier passé en paramètre n'est pas NULL
    if (!f){
        perror("Le fichier passé en parametre est NULL\n");
        return NULL;
    }
    
    // Création et allocation mémoire d'une nouvelle chaîne.
    Chaines* newChaine = malloc(sizeof(Chaines));
    if (!newChaine){
        perror("Erreur dans l'allocation mémoire de la chaine\n");
        return NULL;
    } 

    char* buffer = malloc(sizeof(char) * BUF_SIZE);
    if (!buffer){
        perror("Erreur dans l'allocation mémoire du buffer\n");
        free(newChaine);
        return NULL;
    }
    
    // Lire les deux premières lignes.
    char* token = NULL;

    for (int x=0; x<2; x++){
        fgets(buffer, BUF_SIZE, f);
        token = NULL;
        token = strtok(buffer, " ");
        token = strtok(NULL, " ");
    
        if (x == 0) {
            newChaine->nbChaines = atoi(token);
        } else {
            newChaine->gamma = atoi(token);
        }
    }

    newChaine->chaines = malloc(sizeof(CellChaine) * newChaine->nbChaines);
    if (!newChaine->chaines){
        perror("Erreur dans l'allocation mémoire de la liste de chaines\n");
        free(buffer);
        free(newChaine);
        return NULL;
    }

    // Variable auxiliaire pour faciliter la lisibilité du code.
    CellChaine* chaine_aux = newChaine->chaines;
    char* token_coor = NULL;

    // Récuperer les chaines et le stocker dans la structure.
    while (fgets(buffer, BUF_SIZE, f) != NULL){

        token = strtok(buffer, " ");
        chaine_aux->numero = atoi(token);
        token = strtok(NULL, " ");

        chaine_aux->points = malloc(sizeof(CellPoint) * atoi(token));
        if (!chaine_aux->points){
            perror("Erreur dans l'allocation mémoire de la liste de points\n");
            free(buffer);
            free(chaine_aux);
            free(newChaine);
            return NULL;
        }

        CellPoint* point_aux = chaine_aux->points;
        token_coor = NULL;

        while (token != NULL){
            token = strtok(NULL, " ");

            token_coor = strtok(token, ".");
            point_aux->x = atoi(token_coor);
            
            token_coor = strtok(NULL, ".");
            point_aux->y = atoi(token_coor);

            point_aux = point_aux->suiv;        
        }

        chaine_aux = chaine_aux->suiv;
    }

    // Nettoyer la mémoire et fermer le fichier avant fermer.
    free(buffer);
    fclose(f);

    return newChaine;

}



