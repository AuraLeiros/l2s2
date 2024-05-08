#include "../include/Graphe.h"
#include "../include/Graphe_aux.h"
#include "../include/Reseau.h"

#include <stdio.h>
#include <stdlib.h>

/* --- --- --- --- --- --- --- --- */
/*             Graphes             */
/* --- --- --- --- --- --- --- --- */


Graphe* nouveauGraphe(Reseau* R){
    if (!R){
        fprintf(stderr, "Erreur en relation au reseau passé en parametre.\n");
        return NULL;
    }

    Graphe* G = calloc(1, sizeof(Graphe));
    if (!G){
        fprintf(stderr, "Erreur à le heure d'allouer mémoire pour un graphe.\n");
        return NULL;
    }

    G->nbsom = R->nbNoeuds;
    G->gamma = R->gamma;
    G->nbcommod = nbCommodites(R);
    G->T_som = calloc(G->nbsom, sizeof(Sommet*));
    if (!G->T_som){
        fprintf(stderr, "Erreur à l'heure d'allouer mémoire pour les sommets.\n");
        free(G);
        return NULL;
    }

    return G;
}

void libererGraphe(Graphe* G){
    if (!G){
       return; 
    }

    libererSommets(G);
    libererCommodites(G);
    free(G);

    return;
}


/* --- --- --- --- --- --- --- --- */
/*             Sommets             */
/* --- --- --- --- --- --- --- --- */


Sommet* nouveauSommet(Noeud* nd){
    if (!nd){
        fprintf(stderr, "Erreur liée aux parametres.\n");
        return NULL;
    }

    Sommet* sm = calloc(1, sizeof(Sommet)); 
    if (!sm){
        fprintf(stderr, "Erreur dans l'allocation mémoire / initialisation d'un nouveau sommet.\n");
        return NULL;
    }

    sm->num = nd->num;
    sm->x = nd->x;
    sm->y = nd->y;
    sm->L_voisin = NULL;

    return sm;
}



void libererSommets(Graphe* G){
    if (!G){
        return;
    }

    for (int x=0; x < (G->nbsom); x++){
        libererVoisins(G, x);
        free(G->T_som[x]);
    }
    free(G->T_som);
    return;
}



/* --- --- --- --- --- --- --- --- */
/*              Aretes             */
/* --- --- --- --- --- --- --- --- */


Arete* nouveauArete(int u, int v){

    Arete* at = calloc(1, sizeof(Arete));
    if (!at){
        fprintf(stderr, "Erreur dans l'allocation mémoire d'un arete.\n");
        return NULL;
    }

    at->u = u;
    at->v = v;

    return at;
}


Cellule_arete* nouveauCellule_arete(Arete* at){
    if (!at){
        fprintf(stderr, "Erreur liée aux paramètres.\n");
        return NULL;
    }

    Cellule_arete* ca = calloc(1, sizeof(Cellule_arete));
    if (!ca){
        fprintf(stderr, "Erreur dans l'allocation mémoire d'une structure Cellule_arete");
        return NULL;
    }

    ca->a = at;
    ca->suiv = NULL;

    return ca;
}

int creerAjouterArete(Graphe* G, int u, int v){
    Arete* at = nouveauArete(u, v);
    if (!at){
        fprintf(stderr, "Erreur dans la création d'un nouveau arete.\n");
        return -1;
    }

    Cellule_arete* ca1 = nouveauCellule_arete(at);
    if (!ca1){
        fprintf(stderr, "Erreur dans la création d'un nouveau CelluleArete");
        free(at);
        return -1;
    }

    Cellule_arete* ca2 = nouveauCellule_arete(at);
    if (!ca2){
        fprintf(stderr, "Erreur dans la création d'un nouveau CelluleArete");
        free(at);
        free(ca1);
        return -1;
    }

    ca1->suiv = G->T_som[(u-1)]->L_voisin;
    G->T_som[(u-1)]->L_voisin = ca1;

    ca2->suiv = G->T_som[(v-1)]->L_voisin;
    G->T_som[(v-1)]->L_voisin = ca2;

    return 0;
}

/* --- --- --- --- --- --- --- --- */
/*            Commodites           */
/* --- --- --- --- --- --- --- --- */


Commod* nouvelleCommod(int e1, int e2){
    if (e1 <= 0 || e2 <= 0){
        fprintf(stderr, "Erreur liée aux paramètres.\n");
        return NULL;
    }

    Commod* cm = calloc(1, sizeof(Commod));
    if (!cm){
        fprintf(stderr, "Erreur lors de l'allocation d'une commodité.\n");
        return NULL;
    }

    cm->e1 = e1;
    cm->e2 = e2;

    return cm;
}

void libererCommodites(Graphe* G){
    if (!G){
        return;
    }

    for(int x=0; (x < G->nbcommod); x++){
        free(G->T_Commod[x]);
    }

    return;
}


/* --- --- --- --- --- --- --- --- */
/*               AUX               */
/* --- --- --- --- --- --- --- --- */



int traitementNoeuds(Graphe* G, CellNoeud* cn){
    if (!G || !cn){
        fprintf(stderr, "Erreur liée aux paramètres.\n");
        return -1;
    }

    CellNoeud* actuel = cn;
    Sommet* sm = NULL;
    int idx = 0;

    while (actuel != NULL){

        G->T_som[idx] = nouveauSommet(actuel->nd);
        if (!(G->T_som[idx])){
            fprintf(stderr, "Erreur dans la création d'un nouveau sommet");
            return -1;
        }

        actuel = actuel->suiv;
        idx++;
    }

    return 0;
}


int traitementVoisins(Graphe* G, CellNoeud* cn){
    if (!G || !cn){
        fprintf(stderr, "Erreur liée aux paramètres.\n");
        return -1;
    }

    CellNoeud* actuel = cn;
    CellNoeud* voisins;
    
    while (actuel != NULL){

        voisins = actuel->nd->voisins;
        while (voisins != NULL){
            if (voisins->nd->num > actuel->nd->num){
                if (creerAjouterArete(G, (actuel->nd->num), (voisins->nd->num))){
                    fprintf(stderr, "Erreur dans la création et l'ajout d'un arete.\n");
                    return -1;
                }
            }

            voisins = voisins->suiv;
        }

        actuel = actuel->suiv;
    }

    return 0;
}

int traitementCommodites(Graphe* G, Reseau* R){
    if (!G || !R){
        fprintf(stderr, "Erreur liée aux paramètres.\n");
        return -1;
    }

    G->nbcommod = nbCommodites(R);

    CellCommodite* cc = R->commodites;
    int idx = 0;

    while (cc != NULL){
        G->T_Commod[idx] = nouvelleCommod(cc->extrA->num, cc->extrB->num);
        if (!(G->T_Commod[idx])){
            fprintf(stderr, "Erreur lors de la création d'une nouvelle commodité.\n");
            return -1;
        }

        idx++;
        cc = cc->suiv;
    }

    return 0;
}

void libererVoisins(Graphe* G, int idx){
    if (!G){
        return;
    }

    Cellule_arete* actuel = G->T_som[idx]->L_voisin;
    Sommet* sommetActuel = G->T_som[idx];
    Cellule_arete* temp = NULL;

    while (actuel != NULL){
        temp = actuel->suiv;
       
        if (actuel->a->u == sommetActuel->num) {
            deconnecterVoisin((G->T_som[((actuel->a->v) - 1)]), (actuel->a->u));
        } else if (actuel->a->v == sommetActuel->num) {
            deconnecterVoisin((G->T_som[((actuel->a->u) - 1)]), (actuel->a->v));
        }

        free(actuel->a);
        free(actuel);

        actuel = temp;
    }

    G->T_som[idx]->L_voisin = NULL;
}





void deconnecterVoisin(Sommet* sm, int num){
    
    Cellule_arete* courant = sm->L_voisin;
    Cellule_arete* avant = NULL;


    while (courant != NULL){
        if ((courant->a->u == num) || (courant->a->v == num)){
            if (!avant){
                sm->L_voisin = courant->suiv;
            } else {
                avant->suiv = courant->suiv;
            }
           
           free(courant);
           return;
        }
        avant = courant;
        courant = courant->suiv;
    }
}
