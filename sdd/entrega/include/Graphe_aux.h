#ifndef __GRAPHE_AUX_H__
#define __GRAPHE_AUX_H__

#include "common.h"


/* --- --- --- --- --- --- --- --- */
/*             Graphes             */
/* --- --- --- --- --- --- --- --- */

/* Crée et initialise un graphe */
Graphe* nouveauGraphe(Reseau* R);

/* Libère un graphe */
void libererGraphe(Graphe* G);

/* --- --- --- --- --- --- --- --- */
/*             Sommets             */
/* --- --- --- --- --- --- --- --- */

/* Crée et initialise une structure somment */
Sommet* nouveauSommet(Noeud* nd);

/* Libère tous les sommets d'un graphe */
void libererSommets(Graphe* G);

/* --- --- --- --- --- --- --- --- */
/*              Aretes             */
/* --- --- --- --- --- --- --- --- */

/* Crée et initialise un arete */
Arete* nouveauArete(int u, int v);

/* Crée et initialise une structure Cellule_arete */
Cellule_arete* nouveauCellule_arete(Arete* at);

/* Crée un arete et deux Cellule_arete et les ajoute au graphe */
int creerAjouterArete(Graphe* G, int u, int v);


/* --- --- --- --- --- --- --- --- */
/*            Commodites           */
/* --- --- --- --- --- --- --- --- */


Commod* nouvelleCommod(int e1, int e2);

/* Libère un tableau de commodités */
void libererCommodites(Graphe* G);


/* --- --- --- --- --- --- --- --- */
/*               AUX               */
/* --- --- --- --- --- --- --- --- */

/* Transformation de noeuds en sommets */
int traitementNoeuds(Graphe* G, CellNoeud* cn);

/* Passage des voisins au graphe */
int traitementVoisins(Graphe* G, CellNoeud* cn);

/* Passage des commodites au graphe */
int traitementCommodites(Graphe* G, Reseau* R);

void libererVoisins(Graphe* G, int idx);

void deconnecterVoisin(Sommet* sm, int num);

#endif