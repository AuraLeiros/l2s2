#include "Reseau.h"
#include "Reseau_aux.h"


/* --- --- --- --- --- --- --- --- */
/*       Gestion des noeuds        */
/* --- --- --- --- --- --- --- --- */

/* Crée et initialise un noeud */
Noeud* nouveauNoeud(int num, double x, double y){
    Noeud* newNode = malloc(sizeof(Noeud));
    if (!newNode){
        fprintf(stderr, "Erreur dans la création d'un nouveau nœud.\n");
        return NULL;
    }

    newNode->num = num;
    newNode->x = x;
    newNode->y = y;
    newNode->voisins = NULL;

    return newNode;
}

/* Crée une nouvelle CellNoeud et l'ajoute au réseau */
CellNoeud* nouvelleCelluleNoeud(Noeud* nd){
    if (!nd){
        fprintf(stderr, "Le noeud passé en paramètre n'est pas valide.\n");
        return NULL;
    }

    CellNoeud* newCell = malloc(sizeof(CellNoeud));
    if (!newCell){
        fprintf(stderr, "Erreur lors de l'allocation mémoire d'une nouvelle cellule.\n");
        return NULL;
    }

    newCell->nd = nd;
    newCell->suiv = NULL;

    return newCell;
}

/* Ajoute une cellule à un réseau donné */
int ajouterCelluleNoeud(Reseau* R, CellNoeud* cn){
    if (!R || !cn){
        fprintf(stderr, "Le réseau ou le CellNoeud passés en paramètre ne sont pas valides.\n");
        return -1;
    }

    cn->suiv = R->noeuds;
    R->noeuds = cn;
    R->nbNoeuds++;

    return 0;
}

/* Crée une nouvelle cellule et l'ajoute au réseau */
int creerAjouterCelluleNoeud(Reseau* R, Noeud* nd){
    if (!R || !nd){
        fprintf(stderr, "Le réseau ou le noeud passés en paramètre ne sont pas valides.\n");
        return -1;
    }

    CellNoeud* maCellule = nouvelleCelluleNoeud(nd);
    if (!maCellule){
        fprintf(stderr, "Erreur lors de la création d'une nouvelle cellule");
        return -1;
    }

    if ((ajouterCelluleNoeud(R, maCellule)) != 0){
        fprintf(stderr, "Erreur lors de l'ajout d'une cellule au réseau.\n");
        free(maCellule);
        return -1;
    }

    return 0;
}

/* --- --- --- --- --- --- --- --- */
/*      Gestion des commodites     */
/* --- --- --- --- --- --- --- --- */


/* Crée et initialise une commodite */
CellCommodite* nouvelleCommodite(Noeud* a, Noeud* b){
    if (!a || !b){
        fprintf(stderr, "Problème lié aux noeuds passés en paramètre.\n");
        return NULL;
    }

    CellCommodite* maCommodite = malloc(sizeof(CellCommodite));
    if (!maCommodite){
        fprintf(stderr, "Erreur lors de l'allocation mémoire d'une nouvelle commodité.\n");
        return NULL;
    }

    maCommodite->extrA = a;
    maCommodite->extrB = b;
    maCommodite->suiv = NULL;

    return maCommodite;
}

/* Ajoute une commodité en tête de liste d'une chaîne de commodités d'un réseau. */
int ajouterCommodite(Reseau* R, CellCommodite* commodite){

    if (!R || !commodite){
        fprintf(stderr, "Erreur en relation aux arguments passés en paramètre.\n");
        return -1;
    } 

    commodite->suiv = R->commodites;
    R->commodites = commodite;

    return 0;
}

/* Crée et ajoute une commodité à un réseau existant */
int creerAjouterCommodite(Reseau* R, Noeud* a, Noeud* b){
    if (!R || !a || !b){
        fprintf(stderr, "Erreur en relation aux arguments passés en paramètre.\n");
        return -1;
    }

    CellCommodite* maCommodite = nouvelleCommodite(a, b);
    if (!maCommodite){
        fprintf(stderr, "Erreur dans la création d'une nouvelle commodité.\n");
        return -1;
    }

    if ((ajouterCommodite(R, maCommodite)) != 0){
        fprintf(stderr, "Erreur dans l'ajout d'une commodité à notre réseau.\n");
        free(maCommodite);
        return -1;
    }

    return 0;
}


/* Libere une liste de commodites SANS liberer les nodes associés */
void libererListeCommodites(CellCommodite* cc){

    if (!cc){
        return;
    }

    CellCommodite* idx = cc;
    CellCommodite* suiv = NULL;

    while (idx != NULL){
        suiv = idx->suiv;
        free(idx);
        idx = suiv;
    }

    return;

}

/* --- --- --- --- --- --- --- --- */
/*       Gestion d'un reseau       */
/* --- --- --- --- --- --- --- --- */


/* Crée et initialise un nouveau reseau */
Reseau* nouveauReseau(){
    Reseau* newReseau = malloc(sizeof(Reseau));
    if (!newReseau){
        fprintf(stderr, "Erreur dans l'allocation mémoire d'un reseau.\n");
        return NULL;
    }

    newReseau->nbNoeuds = 0;
    newReseau->gamma = 0;
    newReseau->noeuds = NULL;
    newReseau->commodites = NULL;

    return newReseau;
}

/* Traitement d'une chaine pour le ajouter à un réseau */
int chaineVersReseau(Reseau* R, CellPoint* point){

    // Vérification des paramètres.
    if (!R || !point){
        fprintf(stderr, "Erreur en relation aux arguments passés en paramètre.\n");
        return -1;
    }

    // Variables pour la création de la commodité.
    Noeud* premier = NULL;
    Noeud* dernier = NULL;
    
    // Variables pour le contrôle de la boucle.
    Noeud* actuel = NULL;
    Noeud* avant = NULL;

    // Traitement de la chaine.
    while (point != NULL){

        actuel = rechercheCreeNoeudListe(R, point->x, point->y);
        if (!actuel){
            fprintf(stderr, "Erreur lors de la recherche / création d'un nouveau noeud.\n");
            return -1;
        }

        if (avant != NULL){
            if (((ajouterVoisin(avant, actuel)) != 0) || ((ajouterVoisin(actuel, avant) != 0))){
                fprintf(stderr, "Erreur lors de la gestion des voisins.\n");
                return -1;
            }
        }

        if (!avant){
            premier = actuel;
        }

        if (!(point->suiv)){
            dernier = actuel;
        }

        avant = actuel;
        point = point->suiv;
    }

    if ((creerAjouterCommodite(R, premier, dernier)) != 0){
        fprintf(stderr, "Erreur dans la création et ajout d'une commodité.\n");
        return -1;
    }

    return 0;
}

void libererReseau(Reseau* R){

    if (!R){
        return;
    }

    // Liberer les commodités
    libererListeCommodites(R->commodites);

    CellNoeud* idx = R->noeuds;
    CellNoeud* suiv = NULL;

    while (idx != NULL){
        suiv = idx->suiv;
        libererVoisins(idx->nd->voisins);
        free(idx->nd);
        free(idx);
        idx = suiv;
    }

    free(R);

}

/* --- --- --- --- --- --- --- --- */
/*       Gestion des voisins       */
/* --- --- --- --- --- --- --- --- */


/* Ajoute un noeud à la liste de voisins d'un autre s'il n'est pas encore présent. */
int ajouterVoisin(Noeud* noeud_ou_inserer, Noeud* noeud_a_ajouter){

    if (!noeud_ou_inserer || !noeud_a_ajouter){
        fprintf(stderr, "Erreur en relation avec les noeuds passés en paramètre.\n");
        return -1;
    }

    CellNoeud* idx = noeud_ou_inserer->voisins;

    while(idx != NULL){
        if ((idx->nd) == (noeud_a_ajouter)){
            return 0;
        }
        idx = idx->suiv;
    }

    CellNoeud* newCellNoeud = nouvelleCelluleNoeud(noeud_a_ajouter);
    if (!newCellNoeud){
        fprintf(stderr, "Erreur dans la creation d'une nouvelle cellule.\n");
        return -1;
    }

    newCellNoeud->suiv = noeud_ou_inserer->voisins;
    noeud_ou_inserer->voisins = newCellNoeud;

    return 0;
}





/* Libere une liste de voisins SANS liberer les noeuds pointes et sans actualiser des autres listes de voisinage. */
static void libererVoisins(CellNoeud* cnd){

    if (!cnd){
        return;
    }

    CellNoeud* idx = cnd;
    CellNoeud* suiv = NULL;

    while (idx != NULL){
        suiv = idx->suiv;
        free(idx);
        idx = suiv;
    }

    return;
}


/* --- --- --- --- --- --- --- --- */
/*       ReconstitueReseau.c       */
/* --- --- --- --- --- --- --- --- */

/* Lecture du nom du fichier et de l'option choisie par l'utilisateur */
int dataInput(char* file_name, int* selection, int maxSize){

    // Lecture du nom du fichier
    fprintf(stdout, "Nom du fichier:\n");

    if (!(fgets(file_name, maxSize, stdin))) {
        fprintf(stderr, "Erreur lors de la lecture du nom du fichier.\n");
        return -1;
    }

    // Lecture de l'option.

    char temp[12];

    fprintf(stdout, "1.- Liste\n2.- Table de Hachage\n3.- Arbre\n");
    fprintf(stdout, "Veuillez selectionner la option souhaitée.\n");

    if (fgets(temp, sizeof(temp), stdin)){
        if (sscanf(temp, "%d", selection) != 1){
            fprintf(stdout, "Erreur lors de la lecture de l'option.\n");
            return -1;
        }
    } else {
        fprintf(stdout, "Erreur lors de la lecture de l'option.\n");
        return -1;
    }

    return 0;
}