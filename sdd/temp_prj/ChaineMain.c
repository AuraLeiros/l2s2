#include "Chaine.h"

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]){

    if (argc != 2){
        fprintf(stderr, "Erreur dans les paramètres.\n");
        printf("Usage: %s <fichier_a_lire>\n", argv[0]);
        return -1;
    }

    FILE* testWrite = fopen("test.cha", "w");
    if (!testWrite){
        fprintf(stderr, "Erreur lors de la création du fichier à écrire.\n");
        return -1;
    }

    FILE* testLecture = fopen(argv[1], "r");
    if (!testLecture){
        fprintf(stderr, "Erreur lors de l'ouverture du fichier à lire.\n");
    }
    
    Chaines* maChaine = lectureChaines(testLecture);
    if (!maChaine){
        fprintf(stderr, "Erreur lors de la conversion du fichier vers la structure.\n");
        return -1;
    }

    ecrireChaines(maChaine, testWrite);

    // Test de l'affichage d'un SVG
    afficheChainesSVG(maChaine, "testSVG");

    double test1;
    test1 = longueurChaine(maChaine->chaines);

    printf("%lf", test1);

    fclose(testLecture);
    fclose(testWrite);
    freeChaines(maChaine);

    return 0;
}

