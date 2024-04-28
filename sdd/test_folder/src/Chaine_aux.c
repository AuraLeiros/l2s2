#include "../include/Chaine.h"
#include "../include/Chaine_aux.h"

#include <stdio.h>
#include <stdlib.h>


/*----------------------------------*/
/*-  Auxiliaires à lectureChaines  -*/
/*----------------------------------*/

// Lecture dynamique du nombre de chaines et du gamma
int lectureNombre(FILE *f, int* nbChain, int* gamma){
 
    if (fscanf(f, "NbChain: %d\n", nbChain) != 1){
        fprintf(stderr, "Erreur dans la lecture du nombre de chaines\n");
        return -1;
    }

    if (fscanf(f, "Gamma: %d\n", gamma) != 1){
        fprintf(stderr, "Erreur dans la lecture du gamma\n");
        return -1;
    }

    // Vérification de que nbChain et gamma est plus grand que 0.
    if ((*nbChain <= 0) || (*gamma <= 0)){
        fprintf(stderr, "NbChain / Gamma est <= 0. Le réseau ne peut pas exister.\n");
        return -1;
    }

    return 0;
}

// AUX: Lecture de chaque ligne
CellChaine* lectureLigne(FILE* f){

    // Allocation mémoire d'une nouvelle chaîne.
    CellChaine* myCC = calloc(1, sizeof(CellChaine));
    if (!myCC){
        fprintf(stderr, "Erreur dans l'allocation mémoire d'une cellchaine.\n");
        return NULL;
    }

    // Récuperation du numéro de chaîne et du nombre de points.
    int nbPoints;
    if ((fscanf(f, "%d %d ", &myCC->numero, &nbPoints)) != 2){
        fprintf(stderr, "Erreur dans la lecture du numéro de chaine / nombre de points dans la chaine.\n");
        freeCellChaine(myCC);
        return NULL;
    }

    // Création de la liste chaînée de points
    CellPoint* temp = NULL;
    CellPoint* head = NULL;
    CellPoint* tail = NULL;

    for (int x=0; x < nbPoints; x++){

        temp = calloc(1, sizeof(CellPoint));
        if (!temp){
            fprintf(stderr, "Erreur dans l'allocation mémoire d'un CellPoint.\n");
            freeCellChaine(myCC);
            freeCellPoint(head);
            return NULL;
        }

        if ((fscanf(f, "%lf %lf", &temp->x, &temp->y)) != 2){
            fprintf(stderr, "Erreur dans la lecture d'un point.\n");
            free(temp);
            freeCellChaine(myCC);
            freeCellPoint(head); 
            return NULL;
        }

        if (!head){
            tail = temp;
            head = tail;
        } else { 
            tail->suiv = temp;
            tail = tail->suiv;
        }
    }

    myCC->points = head;
    return myCC;
}

/*----------------------------------*/
/*--  Auxiliaires à ecrireChaines  -*/
/*----------------------------------*/

// Calcul et insertion des deux premiers éléments de chaque chaîne.
int insertDonneesChaine(FILE* f, CellChaine* cc){
    
    if (!f || !cc || !cc->points){
        fprintf(stderr, "Erreur avec un des données passées en paramètre.\n");
        return -1;
    }

    CellPoint* temp = cc->points;
    int idx = 0;
    
    while (temp != NULL) {
        idx++;
        temp = temp->suiv;
    }

    if (idx <= 0){
        fprintf(stderr, "La liste de points ne contient aucun élément.\n");
        return -1;
    }

    if ((fprintf(f, "%d %d", cc->numero, idx)) < 0){
        fprintf(stderr, "Erreur dans l'insertion des données dans le fichier.\n");
        return -1;
    }

    return 0;
}


int printageCoordones(FILE* f, CellPoint* cp){
    
    // 0 = int, 1 = double

    int x = ((cp->x) == (int)(cp->x)) ? 0 : 1;
    int y = ((cp->y) == (int)(cp->y)) ? 0 : 1;

    if (x && y){
        if ((fprintf(f, " %.2lf %.2lf", cp->x, cp->y)) < 0) {
            return -1;
        }
    } else if (!x && !y) {
        if ((fprintf(f, " %d %d", (int)cp->x, (int)cp->y)) < 0){
            return -1;
        }
    } else if (x && !y){
        if ((fprintf(f, " %.2lf %d", cp->x, (int)cp->y)) < 0){
            return -1;
        }
    } else if (!x && y){
        if ((fprintf(f, " %d %.2lf", (int)cp->x, (cp->y)) < 0)){
            return -1;
        }
    }

    return 0;
}
