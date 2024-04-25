#ifndef __RESEAU_AUX_H__
#define __RESEAU_AUX_H__

struct Reseau;
struct CellNoeud;
struct CellPoint;
struct Noeud;
struct CellCommodite;

/* --- --- --- --- --- --- --- --- */
/*       Gestion des noeuds        */
/* --- --- --- --- --- --- --- --- */

/* Crée et initialise un noeud */
Noeud* nouveauNoeud(int num, double x, double y);

/* Crée une nouvelle CellNoeud et l'ajoute au réseau */
CellNoeud* nouvelleCelluleNoeud(Noeud* nd);

/* Ajoute une cellule à un réseau donné */
int ajouterCelluleNoeud(Reseau* R, CellNoeud* cn);

/* Crée une nouvelle cellule et l'ajoute au réseau */
int creerAjouterCelluleNoeud(Reseau* R, Noeud* nd);


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



/* --- --- --- --- --- --- --- --- */
/*       Gestion d'un reseau       */
/* --- --- --- --- --- --- --- --- */

/* Crée et initialise un nouveau reseau */
Reseau* nouveauReseau();

/* Traitement d'une chaine pour l'ajouter à un réseau */
int chaineVersReseau(Reseau* R, CellPoint* point);

/* Liberer un réseau */
void libererReseau(Reseau* R);


/* --- --- --- --- --- --- --- --- */
/*       Gestion des voisins       */
/* --- --- --- --- --- --- --- --- */

/* Ajoute un noeud à la liste de voisins d'un autre s'il n'est pas encore présent. */
int ajouterVoisin(Noeud* noeud_ou_inserer, Noeud* noeud_a_ajouter);

/* --- --- --- --- --- --- --- --- */
/*       ReconstitueReseau.c       */
/* --- --- --- --- --- --- --- --- */

/* Lecture du nom du fichier et de l'option choisie par l'utilisateur */
int dataInput(char* file_name, int* selection, int maxSize);





#endif


