#ifndef __HACHAGE_AUX_H__
#define __HACHAGE_AUX_H__

typedef struct tablehachage TableHachage;
typedef struct cellnoeud CellNoeud;
typedef struct noeud Noeud;
typedef struct reseau Reseau;

/* --- --- --- --- --- --- --- --- */
/*       Gestion de la TdH         */
/* --- --- --- --- --- --- --- --- */

/* Crée une nouvelle table de hachage étant donné sa taille */
TableHachage* nouvelleTH(int taille);

/* Ajoute le noeud en tête de liste d'une case donnée dans un tableau de hachage. */
void ajouterEnTete_TH(TableHachage* H, int caseTableau, CellNoeud* cn);

/* TABLE DE HACHAGE : Crée un nouveau CellNoeud et l'ajoute à la table de hachage */
CellNoeud* creerAjouterCellNoeud_TH(Reseau* R, TableHachage* H, Noeud* nd, int caseTH);

/* HACHAGE: AUX à reconstitueReseauHachage, ajoute une chaine à une table de hachage et à un réseau */
int traitementChaineTH(Reseau* R, TableHachage* H, CellPoint* cp);

/* --- --- --- --- --- --- --- --- */
/*       Gestion du hachage        */
/* --- --- --- --- --- --- --- --- */

/* Test des valeurs données par la fonction clef avec valeurs pour x, y d'1 à 10 (inclus) */
void testClef();

/* Calcule la taille d'une table de hachage selon le nombre d'éléments et la charge souhaitée (en facteur decimal) */
int calcTaille(int nbElem, double loadFactor);


/* --- --- --- --- --- --- --- --- */
/*       Gestion de mémoire        */
/* --- --- --- --- --- --- --- --- */

/* Libère une table de hachage */
void libererTH(TableHachage* H);

/* Cherche et éfface un CellNoeud d'une case de la TdH et libère sa mémoire, mais pas celui du noeud associé */
void libererCellNoeud_TH(TableHachage* H, CellNoeud* cn, int caseTableau);




#endif