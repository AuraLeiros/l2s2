#include "../include/Chaine.h"
#include "../include/Chaine_aux.h"
#include "../include/SVGwriter.h"


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Chaines* lectureChaines(FILE *f){
    
    // Vérification du fichier
    if (!f){
        fprintf(stderr, "Le fichier passé en paramètre est invalide.\n");
        return NULL;
    }

    // Lecture des deux premières lignes du fichier
    int nbChain, gamma;

    if (lectureNombre(f, &nbChain, &gamma) != 0){
        return NULL;
    }

    // Allocation mémoire et initialisation de l'ensemble de chaines.
    Chaines* maChaine = malloc(sizeof(Chaines));
    if (!maChaine){
        fprintf(stderr, "Erreur dans l'allocation mémoire d'une chaine.\n");
        return NULL;
    }

    maChaine->nbChaines = nbChain;
    maChaine->gamma = gamma;
    maChaine->chaines = NULL;


    // Insertion de chaque ligne dans l'ensemble de chaînes.
    CellChaine* temp = NULL;
    CellChaine* tail = NULL;
    
    for (int x=0; x < (maChaine->nbChaines); x++) {

        temp = lectureLigne(f);
        if (!temp) {
            freeChaines(maChaine);
            return NULL;
        }

        if (!maChaine->chaines){
            maChaine->chaines = temp;
            tail = maChaine->chaines;
        } else {
            tail->suiv = temp;
            tail = tail->suiv;
        }
    }

    return maChaine;
}

void ecrireChaines(Chaines* c, FILE* f){

    // Vérification du fichier et la liste de chaines passé en paramètre.
    if (!f || !c) {
        fprintf(stderr, "Erreur en relation avec le fichier ou les chaines indiqués en paramètre.\n");
        return;
    }

    // Insertion du nombre de chaines et du gamma.
    if (c->nbChaines <= 0) {
        fprintf(stderr, "Erreur avec le nombre de chaines / gamma.\n");
        return;
    } else if ((fprintf(f, "NbChain: %d\nGamma: %d\n", c->nbChaines, c->gamma) < 0)){
        fprintf(stderr, "Erreur avec l'insertion du nombre de chaines / gamma.\n");
        return;
    }

    CellChaine* temp = c->chaines;
    CellPoint* tempPoint = NULL;
    int nbChainesEcrites = 0;

    while (temp != NULL){

        if ((insertDonneesChaine(f, temp)) != 0){
            fprintf(stderr, "Erreur dans l'insertion des données de la chaine.\n");
            return;
        }

        tempPoint = temp->points;

        while(tempPoint != NULL){
            if (printageCoordones(f, tempPoint) != 0){
                fprintf(stderr, "Erreur dans l'insertion de points dans la chaine.\n");
                return;
            }

            tempPoint = tempPoint->suiv;
        }

        if (temp->suiv != NULL){
            if ((fprintf(f, "\n") < 0)){
            fprintf(stderr, "Erreur dans l'insertion de la nouvelle ligne.\n");
            }
        }

        nbChainesEcrites++;
        temp = temp->suiv;
    }

    if (nbChainesEcrites != c->nbChaines){
        fprintf(stderr, "Le nombre de chaines ecrites n'est pas la meme qu'indique sur le ensemble de chaines.\n");
    }

    return;
}

// Affichage d'une chaine en format SVG.
void afficheChainesSVG(Chaines *C, char* nomInstance){
    double maxx=0,maxy=0,minx=1e6,miny=1e6;
    CellChaine *ccour;
    CellPoint *pcour;
    double precx,precy;
    SVGwriter svg;
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        while (pcour!=NULL){
            if (maxx<pcour->x) maxx=pcour->x;
            if (maxy<pcour->y) maxy=pcour->y;
            if (minx>pcour->x) minx=pcour->x;
            if (miny>pcour->y) miny=pcour->y;  
            pcour=pcour->suiv;
        }
    ccour=ccour->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        SVGlineRandColor(&svg);
        SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny)); 
        precx=pcour->x;
        precy=pcour->y;  
        pcour=pcour->suiv;
        while (pcour!=NULL){
            SVGline(&svg,500*(precx-minx)/(maxx-minx),500*(precy-miny)/(maxy-miny),500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            precx=pcour->x;
            precy=pcour->y;    
            pcour=pcour->suiv;
        }
        ccour=ccour->suiv;
    }
    SVGfinalize(&svg);
}


double longueurChaine(CellChaine* c){

    if (!c){
        fprintf(stderr, "Le pointeur passé en paramètre est nul.\n");
        return -1;
    }

    CellPoint* idx = c->points;
    CellPoint* idx_suiv = c->points->suiv;
    double res = 0;
    double x, y;

    while ((idx != NULL) && (idx_suiv != NULL)){
        x = (((idx_suiv->x) - (idx->x)) * ((idx_suiv->x) - (idx->x)));
        y = (((idx_suiv->y) - (idx->y)) * ((idx_suiv->y) - (idx->y)));
        res += sqrt((x+y));

        idx = idx_suiv;
        idx_suiv = idx_suiv->suiv;
    }

    return res;
}

double longueurTotale(Chaines *c){

    if (!c) {
        fprintf(stderr, "Le pointeur passé en paramètre est nul.\n");
        return -1;
    }

    double res = 0;
    double temp = 0;
    CellChaine* idx = c->chaines;

    while (idx != NULL){
        temp = longueurChaine(idx);
        if (temp == -1){
            fprintf(stderr, "Erreur dans le calcul d'une chaine.\n");
            return -1;
        }

        res += temp;
        
        idx = idx->suiv;
    }

    return res;
}

int comptePointsTotal(Chaines* c){

    if (!c){
        fprintf(stderr, "Le pointeur passé en paramètre est nul.\n");
        return -1;
    }

    int res = 0;

    CellChaine* temp_chaine = c->chaines;
    CellPoint* temp_point = NULL;

    while(temp_chaine != NULL){
        temp_point = temp_chaine->points;

        while(temp_point != NULL){
            res++;
            temp_point = temp_point->suiv;
        }

        temp_chaine = temp_chaine->suiv;
    }

    return res;

}


// Libère la mémoire d'une liste chaînée de points.
void freeCellPoint(CellPoint* cp){

    if (!cp){
        return;
    }
    
    CellPoint* tmp = NULL;

    while (cp != NULL){
        tmp = cp;
        cp = cp->suiv;
        free(tmp);
    }

    return;
}

// Libère la mémoire d'une liste chaînée de chaînes.
void freeCellChaine(CellChaine* cc){
    
    if (!cc){
        return;
    }

    CellChaine* tmp = NULL;

    while(cc != NULL){

        tmp = cc;
        cc = cc->suiv;

        if (tmp->points != NULL){
            freeCellPoint(tmp->points);
        }
        
        free(tmp);
    }

    return;
}

// Libère la mémoire d'un ensemble de chaînes
void freeChaines(Chaines* ch){

    if (!ch){
        return;
    }

    if (ch->chaines != NULL){
        freeCellChaine(ch->chaines);
    }

    free(ch);
    return;
}