#include <stdio.h>
#include <stdlib.h>

#include "Chaine.h"
#define BUF_SIZE 256


Chaines* lectureChaine(FILE* f){

    // Vérification que le fichier passé en paramètre n'est pas NULL
    if (!f){
        fprintf(stderr, "Le fichier passé en parametre est NULL\n");
        return NULL;
    }
    
    // Création et allocation mémoire d'une nouvelle chaîne.
    Chaines* newChaine = malloc(sizeof(Chaines));
    if (!newChaine){
        fprintf(stderr, "Erreur dans l'allocation mémoire de l'ensemble de chaines\n");
        return NULL;
    } 

    char* buffer = malloc(sizeof(char) * BUF_SIZE);
    if (!buffer){
        fprintf(stderr, "Erreur dans l'allocation mémoire du buffer\n");
        libererChaines(newChaine);
        return NULL;
    }

    char* token = NULL;
    char* separators = " \n";

    // Lecture du nombre de chaines
    if (!fgets(buffer, BUF_SIZE, f)){
        fprintf(stderr, "Erreur dans la lecture du fichier\n");
        libererChaines(newChaine);
        free(buffer);
        return NULL;
    }

    token = strtok(buffer, separators);
    token = strtok(NULL, separators);
    newChaine->nbChaines = atoi(token);

    // Lecture du gamma
    if (!fgets(buffer, BUF_SIZE, f)){
        fprintf(stderr, "Erreur dans la lecture du fichier\n");
        libererChaines(newChaine);
        free(buffer);
        return NULL;
    }

    token = strtok(NULL, separators);
    token = strtok(NULL, separators);
    newChaine->gamma = atoi(token);

    // Declaration des variables auxiliares au boucle de lecture des chaines
    CellChaine* headChaine = NULL;
    CellChaine* tailChaine = NULL;
    CellChaine* newElem = NULL;
    int numPoints = 0;

    // Lecture des chaines
    while (fgets(buffer, BUF_SIZE, f) != NULL) {
    
        // Allocation mémoire d'un nouveau élément.
        newElem = malloc(sizeof(CellChaine));
        if (!newElem){
            fprintf(stderr, "Erreur dans l'allocation mémoire d'une liste de chaines\n");
            libererCellChaine(headChaine);
            libererChaines(newChaine);
            free(buffer);
            return NULL;
        }

        // Lecture du numéro de chaine et le nombre de points de la chaine.
        token = strtok(buffer, separators);
        newElem->numero = atoi(token);

        token = strtok(NULL, separators);
        numPoints = atoi(token);

        CellPoint* headPoint = NULL;
        CellPoint* tailPoint = NULL; 
        CellPoint* newPoint = NULL;
        
        for (int x=0; x < numPoints; x++){
            newPoint = malloc(sizeof(CellPoint));
            if (!newPoint){
                fprintf(stderr, "Erreur dans l'allocation mémoire d'un nouveau point\n");
                libererCellChaine(headChaine);
                libererCellChaine(newElem);                   
                libererPoint(headPoint);
                libererChaines(newChaine);
                free(buffer);
                return NULL;
            }

            // Avancer au prochain jeu de coordonnées.
            token = strtok(NULL, separators);

            if (sscanf(token, "%lf.%lf", &newPoint->x, &newPoint->y) != 2){
                fprintf(stderr, "Erreur dans le parse des coordonées\n");
                libererCellChaine(headChaine);
                libererCellChaine(newElem);
                libererPoint(headPoint);
                libererPoint(newPoint);
                libererChaines(newChaine);
                free(buffer);
                return NULL;            
            }

            if (!headPoint){
                headPoint = newPoint;
                tailPoint = headPoint;
            } else {
                tailPoint->suiv = newPoint;
                tailPoint = tailPoint->suiv;      
            }

            newPoint->suiv = NULL;
        }

        newElem->points = headPoint;

        if (!headChaine){
            headChaine = newElem;
            tailChaine = headChaine;
        } else {
            tailChaine->suiv = newElem;
            tailChaine = tailChaine->suiv;
        }

        newElem->suiv = NULL;
    }
    
    newChaine->chaines = headChaine;
    free(buffer);

    return newChaine;
}



// Fonction pour liberer une liste chainee de points.
void libererPoint(CellPoint* point){

    if (!point){
        return;
    }

    CellPoint* curr = point;
    CellPoint* next = NULL;

    while(curr != NULL){
        next = curr->suiv;
        free(curr);
        curr = next;
    }

    return;
}

// Fonction pour libérer une liste chainee de chaines.
void libererCellChaine(CellChaine* chaine){

    if (!chaine){
        return;
    }

    CellChaine* curr = chaine;
    CellChaine* next = NULL;

    while(curr != NULL){
        next = curr->suiv;
        
        if (curr->points != NULL){
            libererPoint(curr->points);
        }

        free(curr);
        curr = next;
    }

    return;
}

// Fonction pour libérer l'ensemble des chaînes
void libererChaines(Chaines* chaine){

    if (!chaine){
        return;
    }

    if (chaine->chaines != NULL){
        libererCellChaine(chaine->chaines);
    }

    free(chaine);

    return;
}
