#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "main_aux.h"
#define BUF_SIZE 256


/*-------------------------------*/
            /* MENUS */
/*-------------------------------*/


/* Affiche le menu principale */
void menu_mode() {
    printf("\n\n");
    printf("╔══════════════════════════ MENU ═══════════════════════════╗\n\n");
    printf("║           Bonjour! (FR)            Benvido! (GL)          ║\n\n");
    printf("║                                                           ║\n");
    printf("║       BibLog - Logiciel de gestion de bibliothèques       ║\n\n");
    printf("║                                                           ║\n");
    printf("║ -- OPTIONS :                                              ║\n\n");
    printf("║ -- 0 : Sortie du programme                                ║\n\n");
    printf("║ -- 1 : Listes Chainées                                    ║\n\n");
    printf("║ -- 2 : Tables de Hachage                                  ║\n\n");
    printf("║ -- 3 : Mode de Test                                       ║\n\n");
    printf("║ Tapez le numéro de l'option que vous voulez choisir :     ║\n\n");
    printf("╚═══════════════════════════════════════════════════════════╝\n");
    printf("\n\n");
}

/* Affiche le sub-menu principale */
void menu_options() {
    printf("\n\n");
    printf("╔══════════════════════════ MENU ═══════════════════════════╗\n\n");
    printf("║ OPTIONS :                                                 ║\n\n");
    printf("║ 0 - Retourner au menu principal                           ║\n");
    printf("║ 1 - Affichage de la bibliothèque                          ║\n");
    printf("║ 2 - Insérer un ouvrage                                    ║\n");
    printf("║ 3 - Recherche par numéro d'enregistrement                 ║\n");
    printf("║ 4 - Recherche par auteur                                  ║\n");
    printf("║ 5 - Recherche par titre                                   ║\n");
    printf("║ 6 - Recherche des ouvrages avec plusieurs exemplaires     ║\n");
    printf("║ Tapez le numéro de l'option que vous voulez choisir :     ║\n\n");
    printf("╚═══════════════════════════════════════════════════════════╝");
    printf("\n\n");
}



/*-------------------------------*/
            /* INPUTS */
/*-------------------------------*/

/* Prend un string depuis stdin et retourne un pointeur bien formaté */
char* input(){
    char* buffer = malloc(3 * BUF_SIZE);
    if (!buffer){
        fprintf(stderr, "Erreur dans l'allocation mémoire\n");
        return NULL;
    }

    fflush(stdout);
    
    if (!fgets(buffer, (3 * BUF_SIZE), stdin)){
        fprintf(stderr, "Erreur dans la lecture\n");
        free(buffer);
        return NULL;
    }

    int len = strlen(buffer);
    if ((len > 0) && (buffer[(len - 1)] == '\n')){
        buffer[(len-1)] = '\0';
    }
    
    return buffer;
}

/* Prend un int depuis stdin et retourne un pointeur bien formaté */
int input_int(){
    int res = 0;
    char* buffer = NULL;
    
    buffer = input();
    if (!buffer){
        fprintf(stderr, "Erreur de lecture\n");
        return EXIT_FAILURE;
    }

    res = atoi(buffer);
    free(buffer);

    return res;
}

void enregistrer_lc(Biblio* b){

    char* titre = NULL;
    char* auteur = NULL;
    int num = 0;

    printf("Veuillez saisir le numéro d'enregistrement : ");
    input_int();
    printf("\n");

    printf("Veuillez saisir le titre : ");
    titre = input();
    if (!titre){
        fprintf(stderr, "Erreur lors de l'obtention du nom de l'auteur\n");
        exit(EXIT_FAILURE);
    }
    printf("\n");

    printf("Veuillez saisir le nom de l'auteur : ");
    auteur = input();
    if (!auteur){
        fprintf(stderr, "Erreur lors de l'obtention du nom de l'auteur\n");
        exit(EXIT_FAILURE);
    }
    printf("\n");

    inserer_en_tete_lc(b, num, titre, auteur);
    
    free(titre);
    free(auteur);
}







/*-------------------------------*/
    /* Tests de performance */
/*-------------------------------*/

/* Comparaison des temps de recherche d'une œuvre avec les 3 méthodes différentes. */
void comparer_temps_recherche(Biblio* biblioLC, BiblioH* biblioH, int num, char* titre, char* auteur) {
    clock_t debut, fin;
    double temps_lc, temps_h;

    /* Numéro */
    debut = clock();
    recherche_par_num_lc(biblioLC, num);
    fin = clock();
    temps_lc = ((double) (fin - debut));

    debut = clock();
    recherche_par_num_h(biblioH, num);
    fin = clock();
    temps_h = ((double) (fin - debut)) / CLOCKS_PER_SEC;

    printf("Temps de recherche par numéro - Liste chaînée: %f, Table de hachage: %f\n", temps_lc, temps_h);

    /* Titre */
    debut = clock();
    recherche_par_titre_lc(biblioLC, titre);
    fin = clock();
    temps_lc = ((double) (fin - debut)) / CLOCKS_PER_SEC;

    debut = clock();
    recherche_par_titre_h(biblioH, titre);
    fin = clock();
    temps_h = ((double) (fin - debut)) / CLOCKS_PER_SEC;

    printf("Temps de recherche par titre - Liste chaînée: %f, Table de hachage: %f\n", temps_lc, temps_h);

    /* Auteur */
    debut = clock();
    recherche_par_auteur_lc(biblioLC, auteur);
    fin = clock();
    temps_lc = ((double) (fin - debut)) / CLOCKS_PER_SEC;

    debut = clock();
    recherche_par_auteur_h(biblioH, auteur);
    fin = clock();
    temps_h = ((double) (fin - debut)) / CLOCKS_PER_SEC;

    printf("Temps de recherche par auteur - Liste chaînée: %f, Table de hachage: %f\n", temps_lc, temps_h);
}