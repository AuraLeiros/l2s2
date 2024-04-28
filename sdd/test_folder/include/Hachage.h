#ifndef __HACHAGE_H__
#define __HACHAGE_H__

struct Noeud;
struct CellNoeud;
struct Reseau;

typedef struct tablehachage{
  int taille;
  CellNoeud** T;
} TableHachage;


/* --- --- --- --- --- --- --- --- */
/*              Hachage            */
/* --- --- --- --- --- --- --- --- */


/* Géneration d'une clef avec la fonction de hachage donné dans le sujet adapté aux coordonées */
int clef(double x, double y);

/* Géneration d'un index de case avec la fonction de hachage donné dans le sujet adapté aux coordonées */
int hachage(int M, double x, double y);



/* --- --- --- --- --- --- --- --- */
/*                TdH              */
/* --- --- --- --- --- --- --- --- */

/* Recherche un noeud du réseau sur la table de hachage, si le trouve le retourne, si non le crée et l'ajoute sur le réseau et sur la table. */
Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage* H, double x, double y);

/* Réconstitue un réseau et une table de hachage depuis une structure Chaines */
Reseau* reconstitueReseauHachage(Chaines* C, int M);

#endif