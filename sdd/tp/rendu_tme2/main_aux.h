#ifndef MAINAUX
#define MAINAUX

#include "biblioLC.h"
#include "biblioH.h"

/*-------------------------------*/
            /* MENUS */
/*-------------------------------*/


/* Affiche le menu principale */
void menu_mode();

/* Affiche le sub-menu d'options */
void menu_options();


/*-------------------------------*/
            /* INPUTS */
/*-------------------------------*/

/* Prend un string en paramètre et retourne un pointeur bien formaté */
char* input();

/* Prend un int depuis stdin et retourne un pointeur bien formaté */
int input_int();


/*-------------------------------*/
        /* INPUTS - LC*/
/*-------------------------------*/

/* LC - Prend une entrée depuis le stdin et fais l'enregistrement */
void ajouter_aux_lc(Biblio* b);

/* LC - Prend un numéro d'enregistrement depuis le stdin et affiche les livres écris par ce nom */
void recherche_num_aux_lc(Biblio* b);

/* LC - Prend un nom d'auteur depuis le stdin et affiche les livres écris par ce nom */
void recherche_auteur_aux_lc(Biblio* b);

/* LC - Prend un titre depuis le stdin et l'affiche */
void recherche_titre_aux_lc(Biblio* b);

/* LC - Recherche des dupliques dans la bibliothèque et les affiche */
void recherche_dupliques_aux_lc(Biblio* b);


/*-------------------------------*/
        /* INPUTS - H*/
/*-------------------------------*/

/* H - Prend une entrée depuis le stdin et fais l'enregistrement */
void ajouter_aux_h(BiblioH* b);

/* LC - Prend un numéro d'enregistrement depuis le stdin et affiche les livres écris par ce nom */
void recherche_num_aux_h(BiblioH* b);

/* LC - Prend un nom d'auteur depuis le stdin et affiche les livres écris par ce nom */
void recherche_auteur_aux_h(BiblioH* b);

/* LC - Prend un titre depuis le stdin et l'affiche */
void recherche_titre_aux_h(BiblioH* b);

/* LC - Recherche des dupliques dans la bibliothèque et les affiche */
void recherche_dupliques_aux_h(BiblioH* b);


/*-------------------------------*/
    /* Tests de performance */
/*-------------------------------*/

void comparer_temps_recherche(Biblio* biblioLC, BiblioH* biblioH, int num, char* titre, char* auteur);


#endif