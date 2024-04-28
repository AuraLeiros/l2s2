#include "../include/Reseau.h"
#include "../include/Reseau_aux.h"
#include "../include/Chaine.h"
#include "../include/SVGwriter.h"

#include <stdio.h>

/* Recherche un noeud avec les coordonnées données dans le réseau, le crée et l'ajoute s'il n'existe pas. */
Noeud* rechercheCreeNoeudListe(Reseau* R, double x, double y){
    if (!R){
        fprintf(stderr, "Le réseau passé en paramètre n'est pas valide.\n");
        return NULL;
    }

    // Chercher le node sur la liste de nodes.
    CellNoeud* idx = R->noeuds;
    while (idx != NULL){

        if (((idx->nd->x) == x) && ((idx->nd->y) == y)){
            return (idx->nd);
        }
        
        idx = idx->suiv;
    }

    // Si on a arrive ici, le noeud avec les coordonnées recherchées n'est pas dans la liste.

    // Creation d'un nouveau node.
    Noeud* newNode = nouveauNoeud(((R->nbNoeuds) + 1), x, y);
    if (!newNode) {
        fprintf(stderr, "Erreur dans la création d'un nouveau noeud.\n");
        return NULL;
    }

    // Création d'un nouveau noued, sa cellule et ajout à notre réseau.
    if ((creerAjouterCellNoeud_RS(R, newNode)) == NULL){
        fprintf(stderr, "Erreur dans la création et ajout d'une nouvelle cellule.\n");
        free(newNode);
        return NULL;
    }

    return newNode;

}


Reseau* reconstitueReseauListe(Chaines *C){

    // Vérification de que le point marchr
    if (!C) {
        fprintf(stderr, "Erreur dans la chaîne passée en paramètre.\n");
        return NULL;
    }

    // Création de notre réseau.
    Reseau* monReseau = nouveauReseau();
    if (!monReseau){
        fprintf(stderr, "Erreur dans la creation d'un nouveau reseau.\n");
        return NULL;
    }

    // Ajouter le gamma sur le nouveau reseau.
    monReseau->gamma = C->gamma;

    // Itération et traitement sur les chaines.
    CellChaine* chaine = C->chaines;
    while (chaine != NULL){
        
        // Traitement de la chaine (Noeuds + Commodités)
        if ((traitementChaineRS(monReseau, (chaine->points))) != 0){
            fprintf(stderr, "Erreur dans le traitement de la chaine.\n");
            libererReseau(monReseau);
            return NULL;
        }

        chaine = chaine->suiv;

    }

    return monReseau;
}


int nbCommodites(Reseau* R){

    if (!R){
        fprintf(stderr, "Erreur en relation avec le réseau passé en paramètre.\n");
        return -1;
    }

    CellCommodite* idx = R->commodites;
    int res = 0;

    while (idx != NULL){
        res++;
        idx = idx->suiv;
    }

    return res;
}

int nbLiaisons(Reseau* R){
    
    if (!R){
        fprintf(stderr, "Erreur en relation avec le réseau passé en paramètre.\n");
        return -1;
    }

    CellNoeud* cn = R->noeuds;
    CellNoeud* voisins = NULL;

    int res = 0;

    while (cn != NULL){
        voisins = cn->nd->voisins;
        while (voisins != NULL){
            if ((voisins->nd->num) > (cn->nd->num)){
                res++;
            }
            voisins = voisins->suiv;
        }
        cn = cn->suiv;
    }
    
    return res;
}

void ecrireReseau(Reseau* R, FILE* f){

    if (!R || !f){
        fprintf(stderr, "Erreur dans les paramétres.\n");
        return;
    }

    // Calcul et ajout des 4 premieres lignes.
    int liaisons = nbLiaisons(R);
    int commodites = nbCommodites(R);

    if ((liaisons <= 0) || ((R->gamma) <= 0) || ((R->nbNoeuds) <= 0) || (commodites <= 0)){
        fprintf(stderr, "Erreur concernant les données du réseau.\n");
        return;
    } else if (fprintf(f, "NbNoeuds: %d\nNbLiaisons: %d\nNbCommodites: %d\nGamma: %d\n\n", R->nbNoeuds, liaisons, commodites, R->gamma) < 0){
        fprintf(stderr, "Erreur lors de l'ajout des donnés au fichier.\n");
        return;
    }

    // Printer les noeuds.
    if (printNoeuds((R->noeuds), f) != 0){
        fprintf(stderr, "Erreur lors du printage des noeuds dans le fichier.\n");
        return;
    }

    // Printer les voisins.
    if (printVoisins((R->noeuds), f) != 0){
        fprintf(stderr, "Erreur lors du printage des voisins.\n");
        return;
    }

    // Printer les commodités.
    if (printCommodites((R->commodites), f) != 0){
        fprintf(stderr, "Erreur lors du printage des commodités");
        return;
    }

    return;
}


void afficheReseauSVG(Reseau *R, char* nomInstance){
    CellNoeud *courN,*courv;
    SVGwriter svg;
    double maxx=0,maxy=0,minx=1e6,miny=1e6;

    courN=R->noeuds;
    while (courN!=NULL){
        if (maxx<courN->nd->x) maxx=courN->nd->x;
        if (maxy<courN->nd->y) maxy=courN->nd->y;
        if (minx>courN->nd->x) minx=courN->nd->x;
        if (miny>courN->nd->y) miny=courN->nd->y;
        courN=courN->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    courN=R->noeuds;
    while (courN!=NULL){
        SVGpoint(&svg,500*(courN->nd->x-minx)/(maxx-minx),500*(courN->nd->y-miny)/(maxy-miny));
        courv=courN->nd->voisins;
        while (courv!=NULL){
            if (courv->nd->num<courN->nd->num)
                SVGline(&svg,500*(courv->nd->x-minx)/(maxx-minx),500*(courv->nd->y-miny)/(maxy-miny),500*(courN->nd->x-minx)/(maxx-minx),500*(courN->nd->y-miny)/(maxy-miny));
            courv=courv->suiv;
        }
        courN=courN->suiv;
    }
    SVGfinalize(&svg);
}
