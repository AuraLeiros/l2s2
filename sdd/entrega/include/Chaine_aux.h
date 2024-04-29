#ifndef __CHAINE_AUX_H__
#define __CHAINE_AUX_H__

#include <stdio.h>

/* Fonctions auxiliaires */

/* Forward declarations */
typedef struct cellChaine CellChaine;
typedef struct cellPoint CellPoint;

/*----------------------------------*/
/*-  Auxiliaires à lectureChaines  -*/
/*----------------------------------*/

// Lecture du nombre de chaines et du gamma
int lectureNombre(FILE *f, int* nbChain, int* gamma);

// Lecture de chaque chaîne.
CellChaine* lectureLigne(FILE* f);


/*----------------------------------*/
/*--  Auxiliaires à ecrireChaines  -*/
/*----------------------------------*/

// Calcul et insertion des deux premiers éléments de chaque chaîne.
int insertDonneesChaine(FILE* f, CellChaine* cc);

// Inclusion d'une paire de coordonnées dans le fichier selon son type.
int printageCoordones(FILE* f, CellPoint* cp);

/*----------------------------------*/
/*--     Gestion des Chaines       -*/
/*----------------------------------*/

Chaines* genererChainesFile(char* route_fichier);

CellPoint* nouveauCellPoint(double x, double y);

void libererCellPoint(CellPoint* cp);

Chaines* nouvelleChaines(int nbChaines);

CellChaine* nouveauCellChaine(int num);

#endif

