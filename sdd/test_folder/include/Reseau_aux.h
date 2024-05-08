#ifndef __RESEAU_AUX_H__
#define __RESEAU_AUX_H__

#include <stdio.h>

typedef struct cellPoint CellPoint;
typedef struct cellChaine CellChaine;
struct Chaines;

typedef struct cellnoeud CellNoeud;
typedef struct cellCommodite CellCommodite;
typedef struct noeud Noeud;
struct Reseau;
/* --- --- --- --- --- --- --- --- */
/*       Gestion des noeuds        */
/* --- --- --- --- --- --- --- --- */

/* Crée et initialise un noeud */
Noeud* nouveauNoeud(int num, double x, double y);

/* Crée un nouveau CellNoeud et l'initialise avec un noeud */
CellNoeud* nouveauCellNoeud(Noeud* nd);

/* RÉSEAU: Ajoute une cellule à un réseau donné */
int ajouterCellNoeud_RS(Reseau* R, CellNoeud* cn);

/* RÉSEAU : Crée un nouveau CellNoeud, l'initialise et l'ajoute au réseau. */
CellNoeud* creerAjouterCellNoeud_RS(Reseau* R, Noeud* nd);

/* Libère un noeud ainsi que sa liste de voisins (sans libérer les noeuds).*/
void libererNoeud(Noeud* nd);

/* Libère un CellNoeud sans libèrer la mémoire */
void libererCellNoeud(CellNoeud* cn);

/* Libère une liste chaînée de CellNoeuds sans libèrer les noeuds associés */
void libererListeCellNoeuds(CellNoeud* cn);

/* AUX à ecrireReseau, imprime les noeuds d'un réseau dans le fichier */
int printNoeuds(CellNoeud* cn, FILE* f);

/* --- --- --- --- --- --- --- --- */
/*      Gestion des commodites     */
/* --- --- --- --- --- --- --- --- */

/* Crée et initialise une commodite */
CellCommodite* nouvelleCommodite(Noeud* a, Noeud* b);

/* Ajoute une commodité en tête de liste d'une chaîne de commodités d'un réseau. */
int ajouterCommodite(Reseau* R, CellCommodite* commodite);

/* Crée et ajoute une commodité à un réseau existant */
int creerAjouterCommodite(Reseau* R, Noeud* a, Noeud* b);

/* Libere une liste de commodites SANS liberer les nodes associés */
void libererListeCommodites(CellCommodite* cc);

/* AUX à ecrireReseau, ecris les commodités d'un réseau au file f */
int printCommodites(CellCommodite* cc, FILE* f);

/* --- --- --- --- --- --- --- --- */
/*       Gestion d'un reseau       */
/* --- --- --- --- --- --- --- --- */

/* Crée et initialise un nouveau reseau */
Reseau* nouveauReseau();

/* Traitement d'une chaine pour l'ajouter à un réseau */
int traitementChaineRS(Reseau* R, CellPoint* point);

/* Liberer un réseau */
void libererReseau(Reseau* R);

/* Test des fonctions principales avec le fichier 00014_burma.cha */
int testReseau();


/* --- --- --- --- --- --- --- --- */
/*       Gestion des voisins       */
/* --- --- --- --- --- --- --- --- */

/* Ajoute un noeud à la liste de voisins d'un autre s'il n'est pas encore présent. */
int ajouterVoisin(Noeud* noeud_ou_inserer, Noeud* noeud_a_ajouter);

/* Libere une liste de voisins SANS liberer les noeuds pointes et sans actualiser des autres listes de voisinage. */
void libererVoisins(CellNoeud* cnd);

/* AUX à ecrireReseau, printe tous les voisins sur le réseau sans duplicatas */
int printVoisins(CellNoeud* cn, FILE* f);


/* --- --- --- --- --- --- --- --- */
/*       ReconstitueReseau.c       */
/* --- --- --- --- --- --- --- --- */

/* Lecture du nom du fichier et de l'option choisie par l'utilisateur */
int dataInput(char* file_name, int* selection, int maxSize);





#endif


