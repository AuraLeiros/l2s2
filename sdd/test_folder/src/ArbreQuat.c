#include "../include/ArbreQuat.h"
#include "../include/ArbreQuat_aux.h"
#include "../include/Chaine.h"
#include "../include/Reseau.h"
#include "../include/Reseau_aux.h"

void chaineCoordMinMax(Chaines* C, double* xmin, double* ymin, double* xmax, double* ymax){
    if (!C || !xmin || !ymin || !xmax || !ymax){
        fprintf(stderr, "Erreur relative aux chaînes passées en paramètre.\n");
        return;
    }

    CellChaine* chaine = C->chaines;
    CellPoint* point = chaine->points;

    *xmin = point->x;
    *ymin = point->y;

    *xmax = point->x;
    *ymax = point->y;

    while (chaine != NULL){

        point = chaine->points;

        while (point != NULL){
            if (point->x < *xmin){
                *xmin = point->x;
            }

            if (point->y < *ymin){
                *ymin = point->y;
            }

            if (point->x > *xmax){
                *xmax = point->x;
            }

            if (point->y > *ymax){
                *ymax = point->y;
            }

            point = point->suiv;
        }

        chaine = chaine->suiv;
    }

    return;
}

ArbreQuat* creerArbreQuat(double xc, double yc, double coteX, double coteY){

    ArbreQuat* newArbre = calloc(1, sizeof(ArbreQuat));
    if (!newArbre){
        fprintf(stderr, "Erreur dans l'allocation mémoire et initialisation d'un arbre.\n");
        return NULL;
    }
    
    newArbre->xc = xc;
    newArbre->yc = yc;
    newArbre->coteX = coteX;
    newArbre->coteY = coteY;
    
    // calloc initialise déjà les pointeurs à NULL,
    // mais nous le faisons explicitement pour des raisons de bonnes pratiques.

    newArbre->noeud = NULL;
    newArbre->so = NULL;
    newArbre->se = NULL;
    newArbre->no = NULL;
    newArbre->ne = NULL;

    return newArbre;
}

void insererNoeudArbre(Noeud* n, ArbreQuat** a, ArbreQuat* parent){

    double xc, yc, coteX, coteY;

    // Cas 1: Abre (*a) == NULL
    if (!(*a)){

       auxCasArbreVide(n, a, parent);

       if (!(*a)){
        fprintf(stderr, "Erreur du traitement dans le cas arbre vide.\n");
       }

       return;
    }

    if ((*a)->noeud != NULL){

        if ((*a)->noeud->x < (*a)->xc && (*a)->noeud->y < (*a)->yc)
            insererNoeudArbre((*a)->noeud, &((*a)->so), *a);
        if ((*a)->noeud->x >= (*a)->xc && (*a)->noeud->y < (*a)->yc)
            insererNoeudArbre((*a)->noeud, &((*a)->se), *a);
        if ((*a)->noeud->x < (*a)->xc && (*a)->noeud->y >= (*a)->yc)
            insererNoeudArbre((*a)->noeud, &((*a)->no), *a);
        if ((*a)->noeud->x >= (*a)->xc && (*a)->noeud->y >= (*a)->yc)
            insererNoeudArbre((*a)->noeud, &((*a)->ne), *a);
            
        (*a)->noeud = NULL;

        if (n->x < (*a)->xc && n->y < (*a)->yc)
            insererNoeudArbre(n, &((*a)->so), *a);
        if (n->x >= (*a)->xc && n->y < (*a)->yc)
            insererNoeudArbre(n, &((*a)->se), *a);
        if (n->x < (*a)->xc && n->y >= (*a)->yc)
            insererNoeudArbre(n, &((*a)->no), *a);
        if (n->x >= (*a)->xc && n->y >= (*a)->yc)
            insererNoeudArbre(n, &((*a)->ne), *a);

        return;
    }

    if (((*a) != NULL) && ((*a)->noeud == NULL)) {

        double xc = (*a)->xc;
        double yc = (*a)->yc;

        if (n->x < xc) {
            (n->y < yc) ? (insererNoeudArbre(n, &((*a)->so), *a)) : (insererNoeudArbre(n, &((*a)->no), *a));
        } else {
            (n->y < yc) ? (insererNoeudArbre(n, &((*a)->se), *a)) : (insererNoeudArbre(n, &((*a)->ne), *a));
        }
    }
}

Noeud* rechercheCreeNoeudArbre(Reseau* R, ArbreQuat** a, ArbreQuat* parent, double x, double y){
    if (!R){
        fprint(stderr, "Erreur liée aux paramètres.\n");
        return;
    }

    Noeud* newNoeud = NULL;

    if (!(*a)){
        newNoeud = creerAjouterNode_AQ(R, a, parent, x, y);
        if (!newNoeud){
            fprintf(stderr, "Erreur lors de la création / ajout au réseau d'un noeud.\n");
            return NULL;
        }
        
        return newNoeud;
    }

    if ((*a)->noeud != NULL){

        // S'est le node actuel on le retourne.
        Noeud* nodeActuel = (*a)->noeud;
        if (fabs(nodeActuel->x - x) <= 0.0001 && fabs(nodeActuel->y - y) <= 0.0001)
            return nodeActuel;

        // Sinon, on crée et ajoute un au réseau et au AQ.
        newNoeud = creerAjouterNode_AQ(R, a, parent, x, y);
        if (!newNoeud){
            fprintf(stderr, "Erreur lors de la création / ajout au réseau d'un noeud.\n");
            return NULL;
        }

        return newNoeud;
    }

    if ((*a)->noeud == NULL){

        double xc = (*a)->xc;
        double yc = (*a)->yc;

        if (x < xc){
            (y < yc) ? (rechercheCreeNoeudArbre(R, &((*a)->so), *a, x, y)) : (rechercheCreeNoeudArbre(R, &((*a)->no), *a, x, y));
        } else { 
            (y < yc) ? (rechercheCreeNoeudArbre(R, &((*a)->se), *a, x, y)) : (rechercheCreeNoeudArbre(R, &((*a)->ne), *a, x, y));
        }
    }

}

Reseau* reconstitueReseauArbre(Chaines *C){

    // Création d'un nouveau réseau.
    Reseau* R = nouveauReseau();
    if (!R){
        fprintf(stderr, "Erreur dans la création d'un nouveau réseau.\n");
        return NULL;
    }

    // Création d'un nouveau arbre
    ArbreQuat* newArbre = creerArbreChaine(C);
    if (!newArbre){
        fprintf(stderr, "Erreur dans la création d'un nouveau arbre.\n");
        libererReseau(R);
        return NULL;
    }

    CellChaine* chaine = C->chaines;
    
    while (chaine != NULL){ 

        if (traitementChaineAQ(R, newArbre, (chaine->points)) != 0){
            fprintf(stderr, "Erreur dans le traitement d'une chaine.\n");
            libererReseau(R);
            libererArbreQuat(newArbre);
            return NULL;
        }

        chaine = chaine->suiv;
    }

    return R;
}


