#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "biblioLC.h"
#include "biblioH.h"
#include "entreeSortieLC.h"
#include "entreeSortieH.h"
#include "main_aux.h"

#define BUF_SIZE 256

int main(int argc, char** argv){

    if (argc != 3) {
        printf("Usage: %s txt_file number_lines\n", argv[0]);
        fprintf(stderr, "Erreur d'arguments\n");
        return EXIT_FAILURE;
    }

    Biblio* biblioLC = NULL;
    BiblioH* biblioHA = NULL;
    int mode = 0;

    do {
        menu_mode();
        mode = input_int();
        switch (mode) {
            case 0:
                printf("Fermeture du programme.\n");
                break;
            case 1: /* Listes chainées */
                menu_options();
                int optionLC = input_int();
                biblioLC = charger_n_entrees_lc(argv[1], atoi(argv[2]));
                if(!biblioLC){
                    fprintf(stderr, "Erreur à la lecture du fichier, fermeture du programme...");
                    return EXIT_FAILURE;
                }
                switch (optionLC) {
                    case 0:
                    {
                        printf("Retour au menu principal\n");
                        break;
                    }
                    case 1:
                    {
                        /* Afficher la bibliothèque */
                        afficher_biblio_lc(biblioLC);
                        break;
                    }
                    case 2:
                    {
                        /* Ajouter un ouvrage à la bibliothèque */
                        ajouter_aux_lc(biblioLC);
                        break;
                    }
                    case 3:
                    {
                        recherche_titre_aux_lc(biblioLC);
                        break;
                    }
                    case 4:
                    {
                        printf("Veuillez saisir le nom de l'auteur :\n");
                        char* buffer = input();
                        if(!buffer){
                            fprintf(stderr, "Erreur\n");
                            return EXIT_FAILURE;
                        }
                        Biblio* temp = recherche_par_auteur_lc(biblioLC, buffer);
                        afficher_biblio_lc(temp);
                        liberer_biblio_lc(temp);
                        free(buffer);
                        break;
                    }
                    case 5:
                    {
                        printf("Veuillez saisir le titre :\n");
                        char* buffer = input();
                        if(!buffer){
                            fprintf(stderr, "Erreur\n");
                            return EXIT_FAILURE;
                        }
                        Livre* temp = recherche_par_titre_lc(biblioLC, buffer);
                        afficher_livre_lc(temp);
                        liberer_livre_lc(temp);
                        free(buffer);   
                        break;    
                    }                
                    case 6:
                    {
                        Livre* curr = recherche_dupliques_lc(biblioLC);
                        Livre* temp = NULL;
                        while (curr != NULL){
                            afficher_livre_lc(curr);
                            temp = curr->suivant;
                            liberer_livre_lc(curr);
                            curr = temp;
                        }
                        break;
                    }
                    default:
                    {
                        printf("Option invalide.\n");
                        break;
                    }
                }
                break;
            case 2: /* Tables de hachage */
                menu_options();
                biblioHA = charger_n_entrees_h(argv[1], atoi(argv[2]));
                if (!biblioHA){
                    fprintf(stderr, "Erreur allocation !");
                    return EXIT_FAILURE;
                }
                int optionH = input_int();
                switch (optionH) {
                    case 0:
                    {   
                        printf("Retour au menu principale\n");
                        break;
                    }
                    case 1:
                     {   
                        afficher_biblio_h(biblioHA);
                        break;
                     }
                    case 2:
                    {
                
                        char* buffer = NULL;
                        char* auteur = NULL;
                        printf("Veuillez saisir le numéro d'enregistrement :\n");
                        int num = input_int();
                        printf("Veuillez saisir le titre : \n");
                        buffer = input();
                        if (!buffer){
                            fprintf(stderr, "Erreur");
                            return EXIT_FAILURE;
                        }
                        printf("Veuillez entrer l'auteur : \n");
                        auteur = input();
                        if (!auteur){
                            fprintf(stderr, "Erreur\n");
                            return EXIT_FAILURE;
                        }
                        inserer_h(biblioHA, num, buffer, auteur);
                        free(buffer);
                        free(auteur);
                        break;
                    }
                    case 3:
                    {
                        printf("Veuillez saisir le numéro d'enregistrement :\n");
                        int num = input_int();
                        LivreH* temp = recherche_par_num_h(biblioHA, num);
                        afficher_livre_h(temp);
                        liberer_livre_h(temp);
                        break;
                    }
                    case 4:
                    {
                        printf("Veuillez saisir le nom de l'auteur :\n");
                        char* buffer = input();
                        if(!buffer){
                            fprintf(stderr, "Erreur\n");
                            return EXIT_FAILURE;
                        }
                        BiblioH* temp = recherche_par_auteur_h(biblioHA, buffer);
                        afficher_biblio_h(temp);
                        liberer_biblio_h(temp);
                        free(buffer);
                        break;
                    }
                    case 5:
                    {
                        printf("Veuillez saisir le titre :\n");
                        char* buffer = input();
                        if(!buffer){
                            fprintf(stderr, "Erreur\n");
                            return EXIT_FAILURE;
                        }
                        LivreH* temp = recherche_par_titre_h(biblioHA, buffer);
                        afficher_livre_h(temp);
                        liberer_livre_h(temp);
                        free(buffer);   
                        break;  
                    }  
                    case 6:
                    {
                        LivreH* curr = recherche_dupliques_h(biblioHA);
                        LivreH* temp = NULL;
                        while (curr != NULL){
                            afficher_livre_h(curr);
                            temp = curr->suivant;
                            liberer_livre_h(curr);
                            curr = temp;
                        }
                        break;
                    }
                    default:
                    {
                        printf("Option invalide.\n");
                        break;
                    }
                }
                break;
            case 3:
                break;
            default:
                printf("Mode invalide. Veuillez choisir 1, 2 ou 3. 0 pour sortir\n");
        }
    } while (mode != 0);
    

    /* Ex 3.1 - Comparaison des temps de recherche */
    /*
    Biblio* biblioLCTest = NULL;
    BiblioH* biblioHTest = NULL;
    biblioLCTest = charger_n_entrees_lc(argv[1], 5000);
    biblioHTest = charger_n_entrees_h(argv[1], 5000);
    comparer_temps_recherche(biblioLCTest, biblioHTest, 4898, "CDMIOYZSKF", "ejspeaswhl");
    */
    


    return EXIT_SUCCESS;
}