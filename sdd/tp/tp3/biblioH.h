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
  /* Manipulation de structures*/
/*-------------------------------*/

/* Ex. 2.3 - Creation d'un livre */
LivreH* creer_livre_h(int num, char* titre, char* auteur);


/* Ex. 2.3 - Creation d'une bibliothèque */
BiblioH* creer_biblio_h(int m);

/*Ex. 2.5. - Ajout d'un nouveau livre à la bibliothèque */
void inserer_h(BiblioH* b,int num,char* titre,char* auteur);


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