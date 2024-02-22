#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "biblioLC.h"
#include "biblioH.h"
#include "entreeSortieLC.h"
#include "entreeSortieH.h"
#include "main_aux.h"
#include "test.h"

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
                printf("\n -- Sortie du programme -- \n");
                break;
            case 1: /* Listes chainées */
                menu_options();
                int optionLC = input_int();
                biblioLC = charger_n_entrees_lc(argv[1], atoi(argv[2]));
                if(!biblioLC){
                    fprintf(stderr, "Erreur à la lecture du fichier, fermeture du programme...\n");
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
                        recherche_num_aux_lc(biblioLC);
                        break;
                    }
                    case 4:
                    {
                        recherche_auteur_aux_lc(biblioLC);
                        break;
                    }
                    case 5:
                    {
                        recherche_titre_aux_lc(biblioLC);
                        break;    
                    }                
                    case 6:
                    {
                        recherche_dupliques_aux_lc(biblioLC);
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
                    fprintf(stderr, "Erreur allocation !\n");
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
                        ajouter_aux_h(biblioHA);
                        break;
                    }
                    case 3:
                    {
                        recherche_num_aux_h(biblioHA);
                        break;
                    }
                    case 4:
                    {
                        recherche_auteur_aux_h(biblioHA);
                        break;
                    }
                    case 5:
                    {
                        recherche_titre_aux_h(biblioHA);
                        break;  
                    }  
                    case 6:
                    {
                        recherche_dupliques_aux_h(biblioHA);
                        break;
                    }
                    default:
                    {
                        printf("Option invalide.\n");
                        break;
                    }
                }
                break;
            case 3: /* Tests */
                tous_tests_lc();
                tous_tests_h();
                break;
            case 4: /* Calcul temps de recherche */
                printf("Q 3.1.\n");
                Biblio* test31_lc = charger_n_entrees_lc(argv[1], 50000);
                BiblioH* test31_h = charger_n_entrees_h(argv[1], 50000);
                comparer_temps_recherche(test31_lc, test31_h, 21900, "EOKVISJYVWSMH", "hysmharwcdjg");
                comparer_temps_recherche(test31_lc, test31_h, 35147, "FMFR", "enphhnoryie");
                comparer_temps_recherche(test31_lc, test31_h, 60234, "COUSAS", "Castelao");
                comparer_temps_recherche(test31_lc, test31_h, 79245, "NasOrillasDoSar", "Rosalia");
                printf("FIN Q.3.1\n");
                printf("Temps avec 500 entrées\n");
                Biblio* biblioLC_i = charger_n_entrees_lc(argv[1], 500);
                BiblioH* biblioH_i = charger_n_entrees_h(argv[1], 500);
                comparer_temps_recherche(biblioLC_i, biblioH_i, 324, "ATYTRILLK", "tpvlofyaetzw");
                printf("N'existe pas!\n");
                comparer_temps_recherche(biblioLC_i, biblioH_i, 765, "COUSAS", "castelao");
                printf("\n");
                printf("Temps avec 5000 entrées\n");
                Biblio* biblioLC_ii = charger_n_entrees_lc(argv[1], 5000);
                BiblioH* biblioH_ii = charger_n_entrees_h(argv[1], 5000);
                comparer_temps_recherche(biblioLC_ii, biblioH_ii, 3712, "CCSMCPTYKBVMN", "eqlscmbg");
                printf("N'existe pas!\n");
                comparer_temps_recherche(biblioLC_ii, biblioH_ii, 7987, "COUSAS", "castelao");
                printf("\n");
                printf("Temps avec 50,000 entrées\n");
                Biblio* biblioLC_iii = charger_n_entrees_lc(argv[1], 50000);
                BiblioH* biblioH_iii = charger_n_entrees_h(argv[1], 50000);
                comparer_temps_recherche(biblioLC_iii, biblioH_iii, 45307, "AUIRZIUHRMFLK", "szqsqzenitwg");
                printf("N'existe pas!\n");
                comparer_temps_recherche(biblioLC_iii, biblioH_iii, 98754, "AURA", "CarlosFuentes");
                printf("\n");
                printf("Temps avec 99,999 entrées\n");
                Biblio* biblioLC_iv = charger_n_entrees_lc(argv[1], 99999);
                BiblioH* biblioH_iv = charger_n_entrees_h(argv[1], 99999);
                comparer_temps_recherche(biblioLC_iv, biblioH_iv, 91713, "GJITPD", "ihsl");
                printf("N'existe pas!\n");
                comparer_temps_recherche(biblioLC_iii, biblioH_iii, 110000, "PEDRO_PARAMO", "RULFO");
                printf("\n");
                break;
            default:
                printf("\nMode invalide. Veuillez choisir 1, 2 ou 3. 0 pour sortir\n");
        }
    } while (mode != 0);
    
    return EXIT_SUCCESS;
}