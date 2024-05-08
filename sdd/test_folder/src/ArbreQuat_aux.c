#include "../include/ArbreQuat.h"
#include "../include/ArbreQuat_aux.h"
#include "../include/Reseau.h"
#include "../include/Reseau_aux.h"
#include "../include/Chaine.h"

#include <stdio.h>


Noeud* creerAjouterNode_AQ(Reseau* R, ArbreQuat** a, ArbreQuat* parent, double x, double y){
    if (!R){
        fprintf(stderr, "Erreur avec le réseau passé en paramètre.\n");
        return NULL;
    }

    Noeud* newNoeud = nouveauNoeud(((R->nbNoeuds) + 1), x, y);
    if (!newNoeud){
        fprintf(stderr, "Erreur lors de la création d'un nouveau noeud.\n");
        return NULL;
    }

    if (!(creerAjouterCellNoeud_RS(R, newNoeud))){
        fprintf(stderr, "Erreur lors de la création / ajout d'un nouveau CellNoeud.\n");
        return NULL;
    }

    insererNoeudArbre(newNoeud, a, parent);

    return newNoeud;

}


void auxCasArbreVide(Noeud* n, ArbreQuat** a, ArbreQuat* parent){
    if (!n || !parent){
        fprintf(stderr, "Erreur en relation avec l'un des paramètres.\n");
        return;
    }

    double xc = parent->xc;
    double yc = parent->yc;

    double coteX = parent->coteX;
    double coteY = parent->coteY;

    
    if ((n->x) < xc){
        if (n->y < yc){
            *a = creerArbreQuat((xc - (coteX / 4)), (yc - (coteY / 4)), (coteX / 2), (coteY / 2));
            parent->so = *a;
        } else {
            *a = creerArbreQuat((xc - (coteX / 4)), (yc + (coteY / 4)), (coteX / 2), (coteY / 2));
            parent->no = *a;
        }
    } else {
        if (n->y < yc){
            *a = creerArbreQuat((xc + (coteX / 4)), (yc - (coteY / 4)), (coteX / 2), (coteY / 2));
            parent->se = *a;
        } else {
            *a = creerArbreQuat((xc + (coteX / 4)), (yc + (coteY / 4)), (coteX / 2), (coteY / 2));
            parent->ne = *a;
        }
    }

    ((*a)->noeud) = n;

}

static int traitementChaineAQ(Reseau* R, ArbreQuat* a, CellPoint* cp){
    if(!R || !a || !cp){
        fprintf(stderr, "Erreur dans les paramètres.\n");
        return -1;
    }

    // Variables pour la création de la commodité
    Noeud* premier = NULL;
    Noeud* dernier = NULL;

    // Variables pour le contrôle de la boucle.
    Noeud* actuel = NULL;
    Noeud* avant = NULL;

    CellPoint* point = cp;
    
    while (point != NULL){

        actuel = rechercheCreeNoeudArbre(R, (&a), NULL, point->x, point->y);
        if (!actuel){
            fprintf(stderr, "Erreur dans la recherche / ajout d'un noeud à l'arbre.");
            return -1;
        }

        if (avant != NULL){
            if (((ajouterVoisin(avant, actuel)) != 0) || ((ajouterVoisin(actuel, avant) != 0))){
                fprintf(stderr, "Erreur lors de la gestion des voisins.\n");
                return -1;
            }
        }

        if (!avant) {
            premier = actuel;
        }
        
        // Commodities
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

ArbreQuat* creerArbreChaine(Chaines* C){
    if (!C){
        fprintf(stderr, "Erreur dans le paramètre.\n");
        return NULL;
    }

    // Récuperation des données de l'arbre
    double xmin, ymin, xmax, ymax;
    chaineCoordMinMax(C, (&xmin), (&ymin), (&xmax), (&ymax));

    double coteX = xmax - xmin;
    double coteY = ymax - ymin;

    ArbreQuat* newArbre = creerArbreQuat((xmin + (coteX / 2)), (ymin + (coteY / 2)), coteX, coteY);
    if (!newArbre){
        fprintf(stderr, "Erreur dans la création d'un nouveau arbre");
        return NULL;
    }

    return newArbre;
}


void libererArbreQuat(ArbreQuat* a) {
    // If the current tree is NULL, there is nothing to free.
    if (a == NULL) {
        return;
    }

    // Recursively free the subtrees.
    libererArbreQuat(a->so);
    libererArbreQuat(a->se);
    libererArbreQuat(a->no);
    libererArbreQuat(a->ne);

    // Free the node stored in the current tree cell, if it exists.
    if (a->noeud != NULL) {
        free(a->noeud); // Assuming that the Noeud structure can be freed directly.
        a->noeud = NULL; // It's a good practice to set the pointer to NULL after freeing.
    }

    // Finally, free the current tree cell itself.
    free(a);
}


void libererArbreQuat(ArbreQuat* a){
    if (!a){
        return;
    }

    libererArbreQuat(a->so);
    libererArbreQuat(a->se);
    libererArbreQuat(a->no);
    libererArbreQuat(a->ne);

    (a->noeud != NULL) ? libererNoeud(a->noeud) : NULL;

    free(a); 

    return;
}