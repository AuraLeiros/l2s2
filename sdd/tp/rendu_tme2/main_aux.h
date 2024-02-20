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

/* LC - Prend les paramétres depuis le stdin et fais l'enregistrement */
void enregistrer_lc(Biblio* b);


/*-------------------------------*/
    /* Tests de performance */
/*-------------------------------*/



#endif