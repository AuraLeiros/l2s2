#ifndef __TEST_H__
#define __TEST_H__

#include "../include/common.h"

#include <stdio.h>

/* Calcul de la reconstitution d'un réseau depuis une chaîne */
double calculReconstitutionChaines(Chaines* C);

/* Calcul de la reconstituion d'un réseau avec une table de hachage */
double calculReconstitutionHachage(Chaines* C, double loadFactor);

/* Calcul de la reconstitution d'un arbre quaternaire */
double calculReconstitutionArbre(Chaines* c);

Chaines* generationAleatoire(int nbChaines, int nbPointsChaine, int xmax, int ymax);

CellPoint* creerListePoints(int nbPoints, int xmax, int ymax);

double randomDouble(double min, double max);

int testGraphique();

#endif