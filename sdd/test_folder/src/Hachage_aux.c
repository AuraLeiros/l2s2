#include "../include/Hachage.h"
#include "../include/Hachage_aux.h"
#include "../include/Reseau.h"
#include "../include/Reseau_aux.h"

#include <stdio.h>

/* --- --- --- --- --- --- --- --- */
/*       Gestion de la TdH         */
/* --- --- --- --- --- --- --- --- */

TableHachage* nouvelleTH(int taille){

    if (taille <= 0){
        fprintf(stderr, "La taille indiquée n'est pas valide.\n");
        return NULL;
    }

    // Allocation et initialisation mémoire d'une nouvelle table
    TableHachage* newTable = calloc(1, sizeof(TableHachage));
    if (!newTable){
        fprintf(stderr, "Erreur lors de l'allocation mémoire d'une nouvelle table de hachage.\n");
        return NULL;
    } 

    // Assignation de la taille.
    newTable->taille = taille;

    newTable->T = calloc((newTable->taille), sizeof(CellNoeud*));
    if (!(newTable->T)){
        fprintf(stderr, "Erreur lors de l'allocation mémoire pour les noeuds de la table de hachage.\n");
        free(newTable);
        return NULL;
    }
}

void ajouterEnTete_TH(TableHachage* H, int caseTableau, CellNoeud* cn){
    
    cn->suiv = H->T[caseTableau];
    H->T[caseTableau] = cn;

}

CellNoeud* creerAjouterCellNoeud_TH(Reseau* R, TableHachage* H, Noeud* nd, int caseTH){
    if (!R || !nd || !H){
        fprintf(stderr, "Erreur liée aux paramètres.\n");
        return NULL;
    }

    // Crée un nouveau CellNoeud
    CellNoeud* newCell = nouveauCellNoeud(nd);
    if (!newCell){
        fprintf(stderr, "Erreur lors de l'allocation mémoire d'une nouvelle cellule.\n");
        return NULL;       
    }

    ajouterEnTete_TH(H, caseTH, newCell);
        
    return newCell;
}

int traitementChaineTH(Reseau* R, TableHachage* H, CellPoint* cp){
    if (!R || !H || !cp){
        fprintf(stderr, "Erreur dans les paramètres.\n");
        return -1;
    }

    // Variables pour la création de la commodité.
    Noeud* premier = NULL;
    Noeud* dernier = NULL;
    
    // Variables pour le contrôle de la boucle.
    Noeud* actuel = NULL;
    Noeud* avant = NULL;

    CellPoint* point = cp;


    while (point != NULL) {

        actuel = rechercheCreeNoeudHachage(R, H, (point->x), (point->y));
        if (!actuel){
            fprintf(stderr, "Erreur lors de la recherche / création d'un nouveau noeud.\n");
            return -1;
        }

        if (avant != NULL){
            if (((ajouterVoisin(avant, actuel)) != 0) || ((ajouterVoisin(actuel, avant) != 0))){
                fprintf(stderr, "Erreur lors de la gestion des voisins.\n");
                return -1;
            }
        }

        (!avant) ? (premier = actuel) : NULL;
        (!(point->suiv)) ? (dernier = actuel) : NULL;

        avant = actuel;
        point = point->suiv;
    }

    if ((creerAjouterCommodite(R, premier, dernier)) != 0){
        fprintf(stderr, "Erreur dans la création et ajout d'une commodité.\n");
        return -1;
    }

    return 0;

}


/* --- --- --- --- --- --- --- --- */
/*       Gestion du hachage        */
/* --- --- --- --- --- --- --- --- */

void testClef(){

    int maClef = 0;

    for (int x=1; x <= 10; x++){
        for (int y=1; y <= 10; y++){
            maClef = clef((double)x, (double)y);
            fprintf(stdout, "x = %d\ny=%d\nclef:%d\n\n", x, y, maClef);
        }
    }

    return;
}

int calcTaille(int nbElem, double loadFactor){
    if ((nbElem <= 0) || (loadFactor <= 0) || (loadFactor > 1)){
        fprintf(stderr, "Erreur dans le calcul de la taille de la table de hachage.\n");
        return -1;
    }

    return (int)(ceil(nbElem / loadFactor));
}


/* --- --- --- --- --- --- --- --- */
/*       Gestion de mémoire        */
/* --- --- --- --- --- --- --- --- */

void libererCellNoeud_TH(TableHachage* H, CellNoeud* cn, int caseTableau){
    if (!H || !cn){
        fprintf(stderr, "Erreur dans les paramétres.\n");
        return;
    }

    CellNoeud* idx = H->T[caseTableau];
    CellNoeud* avant = NULL;

    while (idx != NULL){

        if (idx == cn){
            if (!avant){
                H->T[caseTableau] = cn->suiv;
                
            } else {
                avant->suiv = cn->suiv;
            }

            free(cn);
            return;
        }

        avant = idx;
        idx = idx->suiv;

    }

}

void libererTH(TableHachage* H){
    if (!H){
        return;
    }

    CellNoeud* cn = NULL;
    CellNoeud* temp = NULL;

    // Libèrer tous les cases de la table de hachage.
    for (int x=0; x < (H->taille); x++){

        cn = H->T[x];

        while (cn != NULL){
            temp = cn->suiv;
            libererNoeud(cn->nd);
            libererCellNoeud(cn);
            cn = temp;
        }
    }

    free(H->T);
    free(H);

    return;
}






