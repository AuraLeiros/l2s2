/* Aura Leirós García - 21218034 */
/* aura.leiros@etu.sorbonne-universite.fr */
/* biblioLC.h - TP3 & TP4 SDD */

typedef struct livre {
    int num;
    char *titre;
    char *auteur;
    struct livre *suiv;
} Livre;

typedef struct biblio {
    /* data */
    Livre *L;
} Biblio;

/* Creation d'un livre */
Livre* creer_livre(int num, char* titre, char* auteur);

/* Libèration de la mémoire alloué à un livre */
void liberer_livre(Livre* l);

/* Creation d'une bibliothèque */
Biblio* creer_biblio();

/* Libèration de la mémoire alloué à une bibliothèque */
void liberer_biblio(Biblio b*);

/* Ajout d'un nouveau livre en tête à la bibliothèque */
void inserer_en_tete(Biblio* b, int num, char* titre, char* auteur);

