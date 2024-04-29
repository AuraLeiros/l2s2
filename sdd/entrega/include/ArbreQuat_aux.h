#ifndef __ARBRE_QUAT_AUX_H__
#define __ARBRE_QUAT_AUX_H__

typedef struct reseau Reseau;
typedef struct noeud Noeud;
typedef struct arbreQuat ArbreQuat;
typedef struct cellPoint CellPoint;
typedef struct chaines Chaines;

Noeud* creerAjouterNode_AQ(Reseau* R, ArbreQuat** a, ArbreQuat* parent, double x, double y);

/*AUX à insererNoeudArbre, traite le cas où l'arbre (*a) est vide */
void auxCasArbreVide(Noeud* n, ArbreQuat** a, ArbreQuat* parent);

int traitementChaineAQ(Reseau* R, ArbreQuat* a, CellPoint* cp);

ArbreQuat* creerArbreChaine(Chaines* C);

void libererArbreQuat(ArbreQuat* a);

#endif