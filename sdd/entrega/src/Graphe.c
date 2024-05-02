#include "../include/Graphe.h"
#include "../include/Reseau.h"
#include "../include/StructListe.h"

#include <stdlib.h>
#include <stdio.h>
#include <limits.h> 

Graphe* creerGraphe(Reseau* R) {
    if (R == NULL) {
        return NULL;
    }

    Graphe* G = nouveauGraphe(R);
    if (!G){
        fprintf(stderr, "Erreur dans la création d'un nouveau graphe.\n");
        return NULL;
    }

    if (traitementNoeuds(G, (R->noeuds)) != 0){
        libererGraphe(G);
        return NULL;
    }

    if (traitementCommodites(G, R) != 0){
        libererGraphe(G);
        return NULL;
    }

    if (traitementVoisins(G, (R->noeuds)) != 0){
        libererGraphe(G);
        return NULL;
    }

    return G;
}




int cheminPlusCourt(Graphe* G, int u, int v){
    if (!G || u >= G->nbsom || v >= G->nbsom || u <= 0 || v <= 0){
        fprintf(stderr, "Erreur dans les paramètres.\n");
        return -1;
    }

    int* peres = malloc(G->nbsom * sizeof(int));
    int* distance = malloc(G->nbsom * sizeof(int));

    for (int x=0; x < (G->nbsom); x++){
        distance[x] = INT_MAX;
        peres[x] = 0;
        
    }

    S_file* f = malloc(sizeof(S_file));
    if (!f){
        fprintf(stderr, "Erreur pour créer une nouvelle liste");
    }
    Init_file(f);
    enfile(f, u);
    peres[u] = 1;
    distance[u] = 0;

    while (!estFileVide(f)){
        int actuel = defile(f);
        Cellule_arete* adjointes = G->T_som[actuel]->L_voisin;

        while (adjointes != NULL){
            int voisin = (adjointes->a->u == actuel) ? (adjointes->a->v) : (adjointes->a->u);
            if (!peres[voisin]){
                peres[voisin] = 1;
                distance[voisin] = distance[actuel] + 1;
                enfile(f, voisin);

                if (voisin != v){
                    int mieuxDistance = distance[voisin];
                    free(distance);
                    free(peres);
                    free(f);
                    return mieuxDistance;
                }
            }
            adjointes = adjointes->suiv;
        }

        free(f);
        free(peres);
        free(distance);

        return -1;
    }
}

int* arborescenceChemins();


