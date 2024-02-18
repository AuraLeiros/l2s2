/* Aura Leirós García - 21218034 */
/* aura.leiros@etu.sorbonne-universite.fr */
/* biblioLC.h - TP3 & TP4 SDD */

#ifndef BIBLIOLC_H
#define BIBLIOLC_H


typedef struct livre {
    int num;
    char *titre;
    char *auteur;
    struct livre *suiv;
} Livre;

typedef struct biblio {
    /* data */
    Livre *l;
} Biblio;


/*-------------------------------*/
   /* Declaration de fonctions */
/*-------------------------------*/


/*-------------------------------*/
/* Initialisation de structures */
/*-------------------------------*/

/* Ex. 1.2 - Creation d'un livre */
Livre* creer_livre(int num, char* titre, char* auteur);

/* Ex. 1.2 - Creation d'une bibliothèque */
Biblio* creer_biblio();


/*-------------------------------*/
/* Recherche */
/*-------------------------------*/

/* Ex. 1.6 - Rechercher un livre par son numéro */
Livre* recherche_par_num(Biblio* b, int num);

/* Ex. 1.6 - Recherche d'un ouvrage par son titre */
Livre* recherche_par_titre(Livre* l, char* titre);

/* Ex. 1.6 - Recherche de tous les livres d'un même auteur */
Biblio* recherche_par_auteur(Biblio* b, char* auteur);

/* Ex. 1.6 - Recherche de ouvrages dupliqués. */
Livre* recherche_dupliques(Biblio* b);


/*-------------------------------*/
/* Libération de mémoire */
/*-------------------------------*/

/* Ex. 1.2 - Libération de la mémoire alloué à un livre */
void liberer_livre(Livre* l);

/* Ex. 1.2 - Libèration de la mémoire alloué à une bibliothèque */
void liberer_biblio(Biblio* b);

/*-------------------------------*/
/* Manipulation de structures */
/*-------------------------------*/

/* Ex. 1.2 - Ajout d'un nouveau livre dans tête de la bibliothèque */
void inserer_en_tete(Biblio* b, int num, char* titre, char* auteur);

/* Ex. 1.6 - Fusion de deux bibliothèques */
Biblio* fusion_biblio(Biblio* b1, Biblio* b2);

/* Ex. 1.6 - Supression d'un ouvrage */
Biblio* supression_ouvrage(Biblio* b, int num, char* auteur, char* titre);


/*-------------------------------*/
/* Affichage */
/*-------------------------------*/

/* Ex. 1.6 - Afficher un livre*/
void afficher_livre(Livre* l);

/* Ex. 1.6 - Afficher une bibliotheque */
void afficher_biblio(Biblio* b);

#endif
