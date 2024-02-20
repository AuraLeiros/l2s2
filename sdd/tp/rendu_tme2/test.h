/* Aura Leirós García - 21218034 */
/* aura.leiros@etu.sorbonne-universite.fr */
/* test.h - TP3 & TP4 SDD */

#ifndef TEST_H
#define TEST_H



/*-------------------------------*/
 /* Jeux de tests de fonctions */
/*-------------------------------*/


/*-------------------------------*/
        /* biblioLC.c */
/*-------------------------------*/

void tous_tests_lc();

void creer_livre_lc_test();

void creer_biblio_lc_test();

void recherche_par_num_lc_test();

void recherche_par_titre_lc_test();

void recherche_par_auteur_lc_test();

void recherche_dupliques_lc_test();

void liberer_livre_lc_test();

void liberer_biblio_lc_test();

void inserer_en_tete_lc_test();

void fusion_biblio_lc_test();

void suppression_ouvrage_lc_test();


/*-------------------------------*/
         /* biblioH.h */
/*-------------------------------*/

void tous_tests_h();

/*-------------------------------*/
/* Éléments de hachage */
/*-------------------------------*/

void fonctionClef_test();
void fonctionHachage_test();

/*-------------------------------*/
/* Initialisation de structures */
/*-------------------------------*/

void creer_livre_h_test();
void creer_biblio_h_test();

/*-------------------------------*/
/* Recherche */
/*-------------------------------*/

void recherche_par_num_h_test();
void recherche_par_titre_h_test();
void recherche_par_auteur_h_test();
void recherche_dupliques_h_test();

/*-------------------------------*/
/* Manipulation de structures */
/*-------------------------------*/

void inserer_h_test();
void fusion_biblio_h_test();
void suppression_ouvrage_h_test();







#endif