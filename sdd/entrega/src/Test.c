#include "../include/Test.h"
#include "../include/Chaine.h"
#include "../include/Chaine_aux.h"
#include "../include/Reseau.h"
#include "../include/Reseau_aux.h"
#include "../include/ArbreQuat.h"
#include "../include/Hachage.h"
#include "../include/Hachage_aux.h"


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>




double calculReconstitutionChaines(Chaines* C){

    clock_t debut, fin;
    double temps_utilise;

    debut = clock();
    Reseau* R = reconstitueReseauListe(C);
    fin = clock();

    libererReseau(R);

    temps_utilise = ((double) (fin - debut)) / CLOCKS_PER_SEC;


    return temps_utilise;
}

double calculReconstitutionHachage(Chaines* C, double loadFactor){

    int points = comptePointsTotal(C);
    int taille = calcTaille(points, loadFactor);

    clock_t debut, fin;
    double temps_utilise;

    debut = clock();
    Reseau* R = reconstitueReseauHachage(C, taille);
    fin = clock();

    temps_utilise = ((double) (fin - debut)) / CLOCKS_PER_SEC;

    libererReseau(R);

    return temps_utilise;
}


double calculReconstitutionArbre(Chaines* C){
    if (!C){
        fprintf(stderr, "Erreur avec la structure chaine passée en paramètre.\n");
        return -1;
    }

    clock_t debut, fin;
    double temps_utilise;

    debut = clock();
    Reseau* R = reconstitueReseauArbre(C);
    fin = clock();

    temps_utilise = ((double) (fin - debut)) / CLOCKS_PER_SEC;

    libererReseau(R);

    return temps_utilise;
}

double randomDouble(double min, double max) {
    return (double)rand() / RAND_MAX * (max - min) + min;
}

CellPoint* creerListePoints(int nbPoints, int xmax, int ymax) {
    if (nbPoints <= 0) {
        return NULL;
    }

    double x = (randomDouble(0, xmax));
    double y = (randomDouble(0, ymax));

    CellPoint* tete = nouveauCellPoint(x, y);
    if (!tete) {
        fprintf(stderr, "Erreur dans l'allocation d'une liste de points");
        return NULL;
    }

    CellPoint* actuel = tete;

    for (int i = 1; i < nbPoints; i++) {

        x = (randomDouble(0, xmax));
        y = (randomDouble(0, ymax));

        CellPoint* newCellPoint = nouveauCellPoint(x, y);

        if (!newCellPoint) {
            libererCellPoint(tete);
        }

        actuel->suiv = newCellPoint;
        actuel = newCellPoint;
    }

    return tete;
}

Chaines* generationAleatoire(int nbChaines, int nbPointsChaine, int xmax, int ymax) {

    // Activer la géneration de nombres.
    srand(time(NULL));

    Chaines* C = nouvelleChaines(nbChaines);
    if (!C) {
        fprintf(stderr, "Erreur dans la création d'une nouvelle structure chaines.\n");
        return NULL;
    }


    CellChaine* tete = NULL;
    CellChaine* actuel = NULL;
    CellChaine* newCC = NULL;

    for (int x = 1; x <= nbChaines; x++) {
        newCC = nouveauCellChaine(x);
        if (!newCC) {
            freeChaines(C);
            return NULL;
        }

        newCC->points = creerListePoints(nbPointsChaine, xmax, ymax);
        if (!newCC->points) {
            freeChaines(C);
            return NULL;
        }

        if (!tete) {
            tete = newCC;
            actuel = newCC;
        } else {
            actuel->suiv = newCC;
            actuel = newCC;
        }
    }

    C->chaines = tete;

    return C;
}


int testGraphique(){ 

    int nbPointsChaine = 100;
    int xmax = 5000;
    int ymax = 5000;

    Chaines* C = NULL;

    FILE* liste = fopen("RES1.txt", "w");
    if (!liste){
        fprintf(stderr, "Erreur dans la création du fichier pour la liste chainée.\n");
        return -1;
    }

    FILE* hachage = fopen("graphique_table", "w");
    if (!hachage){
        fprintf(stderr, "Erreur dans la création du fichier pour la table de hachage.\n");
        return -1;
    }

    FILE* arbre = fopen("graphique_arbre", "w");
    if (!arbre){
        fprintf(stderr, "Erreur dans la création du fichier pour la liste chainée.\n");
        return -1;
    }

    fprintf(liste, "LISTE\n\nnbChaines    TEMPS");
    fprintf(hachage, "HACHAGE\n\nnbChaines  LOAD   TEMPS");
    fprintf(arbre, "ARBRE");

    int nbChaines = 500;
    double data = 0.0;
    double load = 0.10;

    while (nbChaines <= 2000){

        C = generationAleatoire(nbChaines, nbPointsChaine, xmax, ymax);

        data = calculReconstitutionChaines(C);
        if (fprintf(liste, "\n%d    %.3lf", nbChaines, data) < 1){
            fprintf(stderr, "Erreur dans le printage.\n");
            return -1;
        }

        data = calculReconstitutionArbre(C);
        if(fprintf(arbre, "\n%d     %.3lf", nbChaines, data ) < 1){
            fprintf(stderr, "Erreur dans le printage.\n");
            return -1;
        }

        while (load <= 1){
            data = calculReconstitutionHachage(C, load);
            fprintf(hachage, "\nnbChain: %d     LOAD: %.2lf     VALUE: %.4lf", nbChaines, load, data);
            load += 0.10;
        }

        load = 0.10;

        freeChaines(C);
        nbChaines += 500;

    }

    fclose(liste);
    fclose(hachage);
    fclose(arbre);

    return 0;
}