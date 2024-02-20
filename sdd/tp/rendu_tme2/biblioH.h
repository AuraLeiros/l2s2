/* Aura Leirós García - 21218034 */
/* aura.leiros@etu.sorbonne-universite.fr */
/* biblioH.h - TP3 & TP4 SDD */


#ifndef BIBLIOH_H
#define BIBLIOH_H


typedef struct livreh{
    int clef;
    int num;
    char* titre;
    char* auteur; 
    struct livreh* suivant;
} LivreH;

typedef struct table{
    int nE; // Nombre elem contenus dans la table de hachage
    int m; // Taille de la table de hachage
    LivreH** T; // Table de chainage avec resolutions des collisions par chainage
} BiblioH;



/*-------------------------------*/
   /* Declaration de fonctions */
/*-------------------------------*/


/*-------------------------------*/
    /* Éléments de hachage */
/*-------------------------------*/

/* Ex 2.2 - Générer une clé */
int fonctionClef(char* auteur);

/* Ex. 2.4 - Définir la fonction de hachage */
int fonctionHachage(int cle, int m);


/*-------------------------------*/
/* Initialisation de structures */
/*-------------------------------*/

/* Ex. 2.3 - Creation d'un livre */
LivreH* creer_livre_h(int num, char* titre, char* auteur);

/* Ex. 2.3 - Creation d'une bibliothèque */
BiblioH* creer_biblio_h(int m);


/*-------------------------------*/
        /* Recherche */
/*-------------------------------*/

/* Ex. 2.6 - Rechercher un livre par son numéro */
LivreH* recherche_par_num_h(BiblioH* b, int num);

/* Ex. 2.6 - Recherche un livre par son auteur */
LivreH* recherche_par_titre_h(BiblioH* b, char* titre);

/* Ex. 2.6 - Recherche de tous les livres d'un même auteur */
BiblioH* recherche_par_auteur_h(BiblioH* b, char* auteur);

/* Ex. 2.6 - Recherche de ouvrages dupliqués. */
LivreH* recherche_dupliques_h(BiblioH* b);


/*-------------------------------*/
  /* Manipulation de structures*/
/*-------------------------------*/

/* Ex. 2.5. - Ajout d'un nouveau livre à la bibliothèque */
void inserer_h(BiblioH* b,int num,char* titre,char* auteur);

/* Ex. 2.6 - Fusion de deux bibliothèques*/
BiblioH* fusion_biblio_h(BiblioH* b1, BiblioH* b2);

/* Ex. 2.6 - Supression d'un ouvrage */
BiblioH* supression_ouvrage_h(BiblioH* b, int num, char* auteur, char* titre);


/*-------------------------------*/
    /* Libération mémoire */
/*-------------------------------*/

/* Ex. 2.3 - Liberer une bibliothèque */
void liberer_livre_h(LivreH* l);

/* Ex. 2.3 - Liberer une bibliothèque */
void liberer_biblio_h(BiblioH* b);


/*-------------------------------*/
        /* Affichage */
/*-------------------------------*/

/* Ex. 2.6 - Afficher un livre */
void afficher_livre_h(LivreH* l);

/* Ex. 2.6 - Afficher une bibliothèque*/
void afficher_biblio_h(BiblioH* b);




#endif