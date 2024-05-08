#include "../include/Hachage.h"
#include "../include/Hachage_aux.h"
#include "../include/Reseau.h"
#include "../include/Reseau_aux.h"
#include "../include/Chaine.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* --- --- --- --- --- --- --- --- */
/*              Hachage            */
/* --- --- --- --- --- --- --- --- */



int clef(double x, double y){

    // Standardiser x et y pour les convertir en entiers.
    int x_std = (int)(x * 100);
    int y_std = (int)(y * 100);

    // Calcul avec la fonction donné.
    return (((x_std + y_std) * (x_std + y_std + 1) / 2) + y_std);
}

int hachage(int taille, double x, double y){
    double A = ((sqrt(5) - 1) / 2);
    int K = clef(x, y);
    double res = floor(taille) * ((K * A) - floor(K * A));

    return (int)res;
}


/* --- --- --- --- --- --- --- --- */
/*                TdH              */
/* --- --- --- --- --- --- --- --- */


Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage* H, double x, double y){
    if (!R || !H){
        fprintf(stderr, "Erreur relative aux paramètres.\n");
        return NULL;
    }

    int caseNoeud = hachage(H->taille, x, y);

    CellNoeud* teteCase = H->T[caseNoeud];
    CellNoeud* idx = teteCase;
    	
    // Itération sur les CellNoeud de la case correspondante pour trouver le noeud.
    while (idx != NULL){

        if (((idx->nd->x) == x) && ((idx->nd->y) == y)){
            return idx->nd;
        }

        idx = idx->suiv;
    }

    // S'on a arrivé ici ce que on a pas trouvé le noeud sur notre table de hachage.

    // Création d'un nouveau noeud.
    Noeud* newNoeud = nouveauNoeud(((R->nbNoeuds) + 1), x, y);
    if (!newNoeud){
        fprintf(stderr, "Erreur lors de la création d'un nouveau noeud.\n");
        return NULL;
    }

    // Création et ajout d'un nouveau CellNoeud dans la table de hachage.
    CellNoeud* cnTH = creerAjouterCellNoeud_TH(R, H, newNoeud, caseNoeud);
    if (!cnTH){
        fprintf(stderr, "Erreur dans la création et ajout d'un nouveau CellNoeud dans la TdH\n");
        free(newNoeud);
        return NULL;
    }

    // Création et ajout d'un nouveau CellNoeud dans le réseau.
    CellNoeud* cnRS = creerAjouterCellNoeud_RS(R, newNoeud);
    if (!cnRS){
        fprintf(stderr, "Erreur dans la création et ajout d'un nouveau CellNoeud dans le réseau.\n");
        libererCellNoeud_TH(H, cnTH, caseNoeud);
        free(newNoeud);
        return NULL;
    }

    return newNoeud;
}



Reseau* reconstitueReseauHachage(Chaines* C, int M){
    if (!C){
        fprintf(stderr, "Erreur avec les chaines passées en paramétre.\n");
        return NULL;
    }

    // Crée un nouveau réseau.
    Reseau* newReseau = nouveauReseau();
    if (!newReseau){
        fprintf(stderr, "Erreur dans la création d'un nouveau réseau.\n");
        return NULL;
    }

    // Crée une nouvelle table de hachage de taille M.
    TableHachage* newTH = nouvelleTH(M);
    if (!newTH){
        fprintf(stderr, "Erreur lors de la création d'une nouvelle table de hachage.\n");
        libererReseau(newReseau); 
        return NULL;
    }

    // Traitement des chaines.
    CellChaine* chaine = C->chaines;
    while (chaine != NULL){
        if (traitementChaineTH(newReseau, newTH, (chaine->points)) != 0){
            libererReseau(newReseau);
            libererTH(newTH);
            return NULL;
        }

        chaine = chaine->suiv;
    }

    libererTH(newTH);

    return newReseau;

}