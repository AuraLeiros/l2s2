#ifndef __GRAPHE_H__ 
#define __GRAPHE_H__

#include <stdlib.h>
#include <stdio.h>
#include "../include/StructListe.h"
#include "../include/common.h"

typedef struct arete{
    int u, v;
} Arete;

typedef struct cellule_arete {
    Arete* a;
    Cellule_arete* suiv;
} Cellule_arete;

typedef struct sommet {
    int num;
    double x, y;
    Cellule_arete* L_voisin;
} Sommet;

typedef struct commod {
    int e1, e2;
} Commod;

typedef struct graphe {
    int nbsom;
    Sommet** T_som;
    int gamma;
    int nbcommod;
    Commod** T_Commod;
} Graphe;



Graphe* creerGraphe(Reseau* R);

int cheminPlusCourt(Graphe* G, int u, int v);


#endif




