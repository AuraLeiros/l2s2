#include "../include/Chaine.h"
#include "../include/Chaine_aux.h"
#include "../include/Reseau.h"
#include "../include/Reseau_aux.h"
#include "../include/Hachage.h"
#include "../include/Hachage_aux.h"
#include "../include/Test.h"


#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

static int testFile(int argc, char* argv);
static void usage(char* argv);
//static FILE* creerFichierResultat(char* nomFichier);

int main(int argc, char* argv[]){

    // Validation de que le fichier passé en paramètre existe.
    if (testFile(argc, argv[1]) == -1){
        usage(argv[0]);
        return -1;
    }

    // Géneration des chaines depuis du fichier passé en paramètre.
    Chaines* maChaine = genererChainesFile(argv[1]);
    if (!maChaine){
        fprintf(stderr, "Erreur dans la géneration des chaines.\n");
        return -1;
    }

    FILE* res = fopen("../output/res", "w");
    if (!res){
        freeChaines(maChaine);
        return -1;
    }

    // Pour una chaine classique.
    double chaineClassique = calculReconstitutionChaines(maChaine);

    // Pour un arbre.
    double chaineArbre = calculReconstitutionArbre(maChaine);

    if ((fprintf(res, "\nChaine Classique: %.8lf\n\nArbre Quaternaire: %.8lf\n\nTable de Hachage:", chaineClassique, chaineArbre)) < 2){
        fprintf(stderr, "Erreur dans l'ecriture des données au fichier.\n");
        freeChaines(maChaine);
        fclose(res);
        return -1;
    }

    double chaineHachage = 0.0;
    double idx = 0.10;

    while (idx <= 1){
        chaineHachage = calculReconstitutionHachage(maChaine, idx);
        if ((fprintf(res, "\n\nload: %.2lf  temps: %.8lf", idx, chaineHachage)) < 2){
            fprintf(stderr, "Erreur dans l'ecriture des données au fichier.\n");
            freeChaines(maChaine);
            fclose(res);
            return -1;
        }

        idx += 0.10;
    }
    
    // Commente car prend plusieurs minutes pour s'executer.
    //testGraphique();

    fclose(res);
    freeChaines(maChaine);    
    return 0;
}



static int testFile(int nbArgc, char* nom_file){
    
    if (nbArgc < 2) {
        fprintf(stderr, "Vous n'avez pas indique de fichier.\n");
        return -1;
    }
    
    if ((access(nom_file, F_OK) == -1)){
        fprintf(stderr, "Le fichier introduit n'existe pas.\n");
        return -1;
    }
    
    return 0;
}

static void usage(char* nomProgramme){
    printf("Usage: %s <chemin_fichier>\n\n", nomProgramme);
    return;
}

/*
static FILE* creerFichierResultat(char* nomFichier){
    char nom[512];
    strcpy(nom, nomFichier);
    strcat(nom, "_resultat_temps");

    FILE* newFile = fopen(nom, "w");
    if (!newFile){
        fprintf(stderr, "Erreur dans la création d'un nouveau fichier.\n");
        return NULL;
    }

    return newFile;
}
*/