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

/*-------------------------------*/
        /* INPUTS - LC*/
/*-------------------------------*/


/* LC - Prend une entrée depuis le stdin et fais l'enregistrement */
void ajouter_aux_lc(Biblio* b){

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

/* LC - Prend un numéro d'enregistrement depuis le stdin et affiche les livres écris par ce nom */
void recherche_num_aux_lc(Biblio* b){

    int num = 0;
    Livre* temp = NULL;

    printf("Veuillez saisir le numéro d'enregistrement : ");
    input_int();
    printf("\n");

    temp = recherche_par_num_lc(b, num);
    if (!temp){
        fprintf(stderr, "Erreur dans le processus de trouver le livre");
        exit(EXIT_FAILURE);
    }

    afficher_livre_lc(temp);
    liberer_livre_lc(temp);

    return;
}

/* LC - Prend un nom d'auteur depuis le stdin et affiche les livres écris par ce nom */
void recherche_auteur_aux_lc(Biblio* b){

    char* buffer;
    Biblio* temp = NULL;

    printf("Veuillez saisir le nom de l'auteur : ");
    printf("\n");

    buffer = input();
    if(!buffer){
        fprintf(stderr, "Erreur\n");
        exit(EXIT_FAILURE);
    }

    temp = recherche_par_auteur_lc(b, buffer);
    afficher_biblio_lc(temp);
    liberer_biblio_lc(temp);
    free(buffer);
    
    return;
}

/* LC - Prend un titre depuis le stdin et l'affiche */
void recherche_titre_aux_lc(Biblio* b){

    char* buffer = NULL;
    Livre* temp = NULL;

    printf("Veuillez saisir le titre : ");
    printf("\n");

    buffer = input();
    if(!buffer){
        fprintf(stderr, "Erreur\n");
        exit(EXIT_FAILURE);
    }

    temp = recherche_par_titre_lc(b, buffer);
    afficher_livre_lc(temp);
    liberer_livre_lc(temp);
    free(buffer); 

    return; 
}

/* LC - Recherche des dupliques dans la bibliothèque et les affiche */
void recherche_dupliques_aux_lc(Biblio* b){

    Livre* curr = recherche_dupliques_lc(b);
    Livre* temp = NULL;

    while (curr != NULL){
        afficher_livre_lc(curr);
        temp = curr->suivant;
        liberer_livre_lc(curr);
        curr = temp;
    }

    return;

}


/*-------------------------------*/
        /* INPUTS - H*/
/*-------------------------------*/

/* H - Prend une entrée depuis le stdin et fais l'enregistrement */
void ajouter_aux_h(BiblioH* b){

    char* titre = NULL;
    char* auteur = NULL;
    int num = 0;

    printf("Veuillez saisir le numéro d'enregistrement : ");
    printf("\n");
    num = input_int();

    printf("Veuillez saisir le titre : ");
    printf("\n");
    titre = input();
    if (!titre){
        fprintf(stderr, "Erreur dans l'input\n");
        exit(EXIT_FAILURE);
    }                 
    
    printf("Veuillez entrer l'auteur : ");
    printf("\n");
    auteur = input();
    if (!auteur){
        fprintf(stderr, "Erreur\n");
        exit(EXIT_FAILURE);
    }

    inserer_h(b, num, titre, auteur);
    free(titre);
    free(auteur);

    return;
}

/* LC - Prend un numéro d'enregistrement depuis le stdin et affiche les livres écris par ce nom */
void recherche_num_aux_h(BiblioH* b){

    int num = 0;
    LivreH* temp = NULL;

    printf("Veuillez saisir le numéro d'enregistrement : ");
    printf("\n");
    num = input_int();

    temp = recherche_par_num_h(b, num);
    afficher_livre_h(temp);
    liberer_livre_h(temp);
    
    return;
}

/* LC - Prend un nom d'auteur depuis le stdin et affiche les livres écris par ce nom */
void recherche_auteur_aux_h(BiblioH* b){

    char* buffer = NULL;
    BiblioH* temp = NULL;

    printf("Veuillez saisir le nom de l'auteur : ");
    printf("\n");
    buffer = input();
    if(!buffer){
        fprintf(stderr, "Erreur\n");
        exit(EXIT_FAILURE);
    }

    temp = recherche_par_auteur_h(b, buffer);
    afficher_biblio_h(temp);
    liberer_biblio_h(temp);
    free(buffer);
    
    return;
}

/* LC - Prend un titre depuis le stdin et l'affiche */
void recherche_titre_aux_h(BiblioH* b){ 

    char* buffer = NULL;
    LivreH* temp = NULL;

    printf("Veuillez saisir le titre : ");
    printf("\n");

    buffer = input();
    if(!buffer){
        fprintf(stderr, "Erreur\n");
        exit(EXIT_FAILURE);
    }

    temp = recherche_par_titre_h(b, buffer);
    afficher_livre_h(temp);
    liberer_livre_h(temp);
    free(buffer);

    return;
}

/* LC - Recherche des dupliques dans la bibliothèque et les affiche */
void recherche_dupliques_aux_h(BiblioH* b){

    LivreH* curr = NULL;
    LivreH* temp = NULL;

    curr = recherche_dupliques_h(b);
    while (curr != NULL){
        afficher_livre_h(curr);
        temp = curr->suivant;
        liberer_livre_h(curr);
        curr = temp;
    }
}





/*-------------------------------*/
    /* Tests de performance */
/*-------------------------------*/

/* Comparaison des temps de recherche avec les 3 méthodes différents. */
void comparer_temps_recherche(Biblio* biblioLC, BiblioH* biblioH, int num, char* titre, char* auteur) {
    clock_t debut, fin;
    double temps_lc, temps_h;

    printf("\n");
    /* Numéro */
    debut = clock();
    recherche_par_num_lc(biblioLC, num);
    fin = clock();
    temps_lc = ((double) (fin - debut)) / CLOCKS_PER_SEC;

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
    printf("\n");
}


