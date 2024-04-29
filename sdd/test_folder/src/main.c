#include "../include/Chaine.h"
#include "../include/Reseau.h"
#include "../include/Reseau_aux.h"
#include "../include/Hachage.h"
#include "../include/Hachage_aux.h"


#include <stdio.h>
#include <time.h>
#include <unistd.h>

static int testFile(int argc, char* argv);
static void usage(char* argv);
static Chaines* genererChainesFile(char* nom_fichier);
static double calculChaines;
static double calculHachage;

int main(int argc, char* argv[]){

    // Validation de que le fichier passé en paramètre est correct.
    testFile(argc, argv);

    // Géneration des chaines depuis du fichier passé en paramètre.
    Chaines* maChaine = genererChainesFile(argv[1]);
    if (!maChaine){
        fprintf(stderr, "Erreur dans la géneration des chaines.\n");
        return -1;
    }

    double calcChain = calculChaines(maChaine);
    double calcHachage = calculHachage(maChaine);

    printf("%lf %lf", calcChain, calcHachage);

    return 0;



    /*

    // Ouverture du fichier lecture
    FILE* fl = fopen(argv[1], "r");
    if (!fl){
        fprintf(stderr, "Erreur dans l'ouverture du fichier.\n");
        return -1;
    }

    FILE* fe = fopen("test.res", "w");
    if (!fe){
        fprintf(stderr, "Erreur dans l'ouverture du fichier.\n");
    }

    // Lecture d'une structure Chaines.
    Chaines* maChaine = lectureChaines(fl);

    // Écriture de une chaine.
    ecrireChaines(maChaine, fe);

    */


    

}

/*
int trouverFichier(char path_fichier){

    int execution = 0;
    while (execution != 0 || (execution != 1)){
        fprintf(stdout, "Veuillez écrire le chemin du fichier\n(ou le nom du fichier s'il est dans ce même répertoire)\n");
        fgetc
    }

}
*/

static int testFile(int argc, char* argv){
    int res;
    (argc != 2) ? usage(argv) : NULL;
    (access(argv[1], F_OK) != -1) ? (res = 0) : (res = -1);
    return res;
}


static void usage(char* argv){
    printf("Usage: %s <chemin_fichier>\n\n", argv[0]);
    return;
}


static Chaines* genererChainesFile(char* nom_fichier){

    FILE* f = fopen(nom_fichier, "r");
    if (!f){
        fprintf(stderr, "Erreur dans l'ouverture du fichier.\n");
        return NULL;
    }

    Chaines* maChaine = lectureChaines(f);
    if (!maChaine){
        fprintf(stderr, "Erreur dans la géneration des chaines.\n");
        return NULL;
    }

    fclose(f);
    
    return maChaine;
}   

static double calculChaines(Chaines* C){
    
    Reseau* R = nouveauReseau();
    if (!R){
        fprintf(stderr, "Erreur dans la création d'un nouveau réseau.\n");
        return -1;
    }

    clock_t debut, fin;
    double temps_utilise;

    debut = clock();
    R = reconstitueReseauListe(C);
    fin = clock();

    libererReseau(R);

    temps_utilise = ((double) (fin - debut)) / CLOCKS_PER_SEC;

    return temps_utilise;

}

static double calculHachage(Chaines* C){


    int points = comptePointsTotal(C);
    int taille = calcTaille(points, 0.70);

    Reseau* R = NULL;

    clock_t debut, fin;
    double temps_utilise;

    debut = clock();
    R = reconstitueReseauHachage(C, taille);
    fin = clock();

    temps_utilise = ((double) (fin - debut)) / CLOCKS_PER_SEC;

    return temps_utilise;

}