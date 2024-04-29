#include "../include/Graphe.h"
#include "../include/Reseau.h"

Graphe* creerGraphe(Reseau* R) {

    Graphe* G = nouveauGraphe((R->nbNoeuds));
    if (!G || !(G->T_som)){
        fprintf(stderr, "Erreur à l'heure de créer / initialiser un graphe.\n");
        return NULL;
    }

    CellNoeud* cn = R->noeuds;

    for (int x=0; x < (G->nbsom); x++){
        G->T_som[x] = calloc(1, sizeof(Sommet));
        if (!(G->T_som[x])){
            fprintf(stderr, "Erreur dans l'allocation mémoire d'un sommet");
            while (x--) {
                free(G->T_som[x]);
            }
            free(G->T_som);
            free(G);
            return NULL;
        }

        R->noeuds->nd->x;

        G->T_som[x]->num = x;
        G->T_som[x]->x = cn->nd->x;
        G->T_som[x]->y = cn->nd->y;
        G->T_som[x]->L_voisin = NULL; 

        cn = cn->suiv;
    }



    // Allocate memory for the graph
    Graphe* g = malloc(sizeof(Graphe));
    if (!g) {
        perror("Memory allocation failed for graph");
        return NULL;
    }

    // Initialize the graph's fields
    g->nbsom = r->nbNodes; // Assuming nbNodes is the number of nodes in the network
    g->T_som = malloc(g->nbsom * sizeof(Sommet*));
    if (!g->T_som) {
        perror("Memory allocation failed for graph nodes");
        free(g);
        return NULL;
    }

    // Initialize the sommets (nodes)
    for (int i = 0; i < g->nbsom; ++i) {
        g->T_som[i] = malloc(sizeof(Sommet));
        if (!g->T_som[i]) {
            perror("Memory allocation failed for a graph node");
            // Free previously allocated memory
            while (i--) {
                free(g->T_som[i]);
            }
            free(g->T_som);
            free(g);
            return NULL;
        }
        g->T_som[i]->num = i; // Assuming the position in the array corresponds to the node number
        g->T_som[i]->x = r->nodes[i].x; // Assuming nodes have x coordinates
        g->T_som[i]->y = r->nodes[i].y; // Assuming nodes have y coordinates
        g->T_som[i]->L_voisin = NULL; // Initialize the adjacency list
    }

    // Assuming r->edges is an array of edges in the network
    for (int i = 0; i < r->nbEdges; ++i) {
        int u = r->edges[i].u;
        int v = r->edges[i].v;

        // Allocate and set the edge
        Arete* edge = malloc(sizeof(Arete));
        if (!edge) {
            perror("Memory allocation failed for an edge");
            // Free previously allocated memory
            // ... (similar cleanup as above)
            return NULL;
        }
        edge->u = u;
        edge->v = v;

        // Add the edge to the adjacency list of u
        Cellule_arete* cell_u = malloc(sizeof(Cellule_arete));
        if (!cell_u) {
            perror("Memory allocation failed for cell_u");
            free(edge);
            // Free previously allocated memory
            // ... (similar cleanup as above)
            return NULL;
        }
        cell_u->a = edge;
        cell_u->suiv = g->T_som[u]->L_voisin;
        g->T_som[u]->L_voisin = cell_u;

        // Add the edge to the adjacency list of v
        Cellule_arete* cell_v = malloc(sizeof(Cellule_arete));
        if (!cell_v) {
            perror("Memory allocation failed for cell_v");
            free(edge);
            // Free previously allocated memory
            // ... (similar cleanup as above)
            return NULL;
        }
        cell_v->a = edge;
        cell_v->suiv = g->T_som[v]->L_voisin;
        g->T_som[v]->L_voisin = cell_v;
    }

    // Assuming gamma and commodities are part of the network and need to be copied or processed
    // g->gamma = ...
    // g->nbcommod = ...
    // g->T_Commod = ...

    return g;
}


Graphe* nouveauGraphe(int nbSomm){
    Graphe* G = calloc(1, sizeof(Graphe));
    if (!G){
        fprintf(stderr, "Erreur à le heure d'allouer mémoire pour un graphe.\n");
        return NULL;
    }

    G->nbsom = nbSomm;
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


}

