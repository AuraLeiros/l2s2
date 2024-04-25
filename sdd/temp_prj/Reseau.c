#include "Reseau.h"
#include "Reseau_aux.h"
#include "Chaine.h"

#include <stdio.h>
#include <stdlib.h>

/* Recherche un noeud avec les coordonnées données dans le réseau, le crée et l'ajoute s'il n'existe pas. */
Noeud* rechercheCreeNoeudListe(Reseau* R, double x, double y){
    if (!R){
        fprintf(stderr, "Le réseau passé en paramètre n'est pas valide.\n");
        return NULL;
    }

    // Chercher le node sur la liste de nodes
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

    // Création et ajout d'un CellNoeud à notre réseau.
    if ((creerAjouterCelluleNoeud(R, newNode)) != 0){
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
        if ((chaineVersReseau(monReseau, (chaine->points))) != 0){
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