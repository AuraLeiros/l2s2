#include "Reseau.h"
#include "Reseau_aux.h"

#include <stdio.h>
#include <stdlib.h>


/* --- --- --- --- --- --- --- --- */
/*       Gestion des noeuds        */
/* --- --- --- --- --- --- --- --- */

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

CellNoeud* nouveauCellNoeud(Noeud* nd){
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

int ajouterCellNoeud_RS(Reseau* R, CellNoeud* cn){
    if (!R || !cn){
        fprintf(stderr, "Le réseau ou le CellNoeud passés en paramètre ne sont pas valides.\n");
        return -1;
    }

    cn->suiv = R->noeuds;
    R->noeuds = cn;
    R->nbNoeuds++;

    return 0;
}

CellNoeud* creerAjouterCellNoeud_RS(Reseau* R, Noeud* nd){
    if (!R || !nd){
        fprintf(stderr, "Le réseau ou le noeud passés en paramètre ne sont pas valides.\n");
        return NULL;
    }

    CellNoeud* maCellule = nouveauCellNoeud(nd);
    if (!maCellule){
        fprintf(stderr, "Erreur lors de la création d'une nouvelle cellule.\n");
        return NULL;
    }

    if ((ajouterCellNoeud_RS(R, maCellule)) != 0){
        fprintf(stderr, "Erreur lors de l'ajout d'une cellule au réseau.\n");
        free(maCellule);
        return NULL;
    }

    return maCellule;
}

void libererNoeud(Noeud* nd){
    if (!nd){
        return;
    }

    libererListeCellNoeuds(nd->voisins);
    free(nd);

    return;
}

void libererCellNoeud(CellNoeud* cn){
    if (!cn){
        return;
    }

    cn->nd = NULL;
    cn->suiv = NULL;
    free(cn);

    return;
}

void libererListeCellNoeuds(CellNoeud* cn){
    if (!cn) {
        return;
    }
    
    CellNoeud* idx = cn;
    CellNoeud* temp = NULL;

    while (idx != NULL){
        temp = idx->suiv;
        libererCellNoeud(idx);
        idx = temp;
    }

    return;
}

int printNoeuds(CellNoeud* cn, FILE* f){
    if (!cn || !f){
        fprintf(stderr, "Erreur concernant un des paramètres.\n");
        return -1;
    }

    CellNoeud* idx = cn;

    // Iteration sur les noeuds et printage.
    while (idx != NULL){
        if (fprintf(f, "v %d %lf %lf\n",idx->nd->num, idx->nd->x, idx->nd->y) < 0){
            fprintf(stderr, "Erreur lors de l'ajout d'un noeud au fichier.\n");
            return -1;
        }

        idx = idx->suiv;
    }

    // Ajout d'un saut de ligne.
    if (fprintf(f, "\n") < 0){
        fprintf(stderr, "Erreur dans l'ajout d'un saut de ligne.\n");
        return -1;
    }

    return 0;
}

/* --- --- --- --- --- --- --- --- */
/*      Gestion des commodites     */
/* --- --- --- --- --- --- --- --- */

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

int ajouterCommodite(Reseau* R, CellCommodite* commodite){

    if (!R || !commodite){
        fprintf(stderr, "Erreur en relation aux arguments passés en paramètre.\n");
        return -1;
    } 

    commodite->suiv = R->commodites;
    R->commodites = commodite;

    return 0;
}

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

int printCommodites(CellCommodite* cc, FILE* f){
    if (!cc || !f){
        fprintf(stderr, "Erreur liée aux paramètres.\n");
        return -1;
    }

    CellCommodite* idx = cc;

    while (idx != NULL){
        if ((fprintf(f, "k %d %d\n", (idx->extrA->num), (idx->extrB->num))) < 0){
            fprintf(stderr, "Erreur lors du printage d'une commodité.\n");
            return -1;
        }

        idx = idx->suiv;
    }

    return 0;
}

/* --- --- --- --- --- --- --- --- */
/*       Gestion d'un reseau       */
/* --- --- --- --- --- --- --- --- */


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

int traitementChaineRS(Reseau* R, CellPoint* point){

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

int testReseau(){

    // Test des fonctions d'un réseau avec le fichier 00014_burma.res

    // Ouverture du fichier.
    FILE* f = fopen("00014_burma.cha", "r");
    if (!f){
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        return -1;
    }

    // Lire le fichier.
    Chaines* burma = lectureChaines(f);
    if (!burma){
        fprintf(stderr, "Erreur dans la lecture du fichier.\n");
        fclose(f);
        return -1;
    }

    // TEST 1 : Reconstituer le réseau
    Reseau* burmaReseau = reconstitueReseauListe(burma);
    if (!burma){
        fprintf(stderr, "LE TEST 1 À ECHOUE.\n");
        freeChaines(burma);
        fclose(f);
        return -1;
    }

    fprintf(stdout, "TEST 1 RÉUSSI.\n");

    // TEST 2 : nbCommodites et nbLiaisons
    int commodites = nbCommodites(burmaReseau);
    int liaisons = nbLiaisons(burmaReseau);
    if ((commodites != 8) || (liaisons != 15)){
        fprintf(stderr, "LE TEST 2 À ECHOUE.\n\n");
    }

    fprintf(stdout, "nbCommodites:\n\nAttendues: 8\nObtenues:%d\n", commodites);
    fprintf(stdout, "nbLiaisons:\n\nAttendues: 15\nObtenues:%d\n\n", liaisons);
    fprintf(stdout, "TEST 2 RÉUSSI\n");

    // TEST 3 : Écrire le réseau
    FILE* testFile = fopen("testReseau.res", "w");
    ecrireReseau(burmaReseau, testFile);
    fprintf(stdout, "TEST 3: Veuillez vérifier le fichier testReseau.res\n");


    fclose(f);
    fclose(testFile);

    freeChaines(burma);
    libererReseau(burmaReseau);

    return 0;
}


/* --- --- --- --- --- --- --- --- */
/*       Gestion des voisins       */
/* --- --- --- --- --- --- --- --- */


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

    CellNoeud* newCellNoeud = nouveauCellNoeud(noeud_a_ajouter);
    if (!newCellNoeud){
        fprintf(stderr, "Erreur dans la creation d'une nouvelle cellule.\n");
        return -1;
    }

    newCellNoeud->suiv = noeud_ou_inserer->voisins;
    noeud_ou_inserer->voisins = newCellNoeud;

    return 0;
}

void libererVoisins(CellNoeud* cnd){

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

int printVoisins(CellNoeud* cn, FILE* f){
    if (!cn || !f){
        fprintf(stderr, "Erreur dans un des paramétres.\n");
        return -1;
    }

    CellNoeud* idx = cn;
    CellNoeud* voisins = NULL;

    while (idx != NULL){
        voisins = idx->nd->voisins;
        while (voisins != NULL){
            if ((voisins->nd->num) > (idx->nd->num)){
                if (fprintf(f, "l %d %d\n", idx->nd->num, voisins->nd->num) < 0){
                    fprintf(stderr, "Erreur dans le printage d'une liaison.\n");
                    return -1;
                }
            }
            voisins = voisins->suiv;
        }
        idx = idx->suiv;
    }


    // Faire une nouvelle ligne vide
    if (fprintf(f, "\n") < 0){
        fprintf(stderr, "Erreur lors de l'ajout d'un saut de ligne.\n");
        return -1;
    }


    return 0;
}


/* --- --- --- --- --- --- --- --- */
/*       ReconstitueReseau.c       */
/* --- --- --- --- --- --- --- --- */

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