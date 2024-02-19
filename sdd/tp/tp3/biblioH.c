/* Aura Leirós García - 21218034 */
/* aura.leiros@etu.sorbonne-universite.fr */
/* biblioH.c - TP3 & TP4 SDD */

#include <stdio.h>
#include <math.h>
#include "biblioH.h"

/* Ex 2.2 - Fonction pour générer une clé */
int fonctionClef(char* auteur){
    int res = 0;

    while(*auteur){
        res += (int)*auteur;
        auteur++;
    }

    return res;
}

/* Ex. 2.3 - Creation d'un livre */
LivreH* creer_livre_h(int num, char* titre, char* auteur){

    LivreH* newLivre = malloc(sizeof(LivreH));
    if (!newLivre){
        fprintf(stderr, "Erreur dans l'allocation mémoire\n");
        return NULL;
    }

    newLivre->clef = fonctionClef(auteur);
    newLivre->num = num;

    newLivre->titre = strdup(titre);
    if (!newLivre->titre){
        liberer_livre_h(newLivre);
        return NULL;
    }

    newLivre->auteur = strdup(auteur);
    if (!newLivre->auteur){
        liberer_livre_h(newLivre);
        return NULL;
    }
    newLivre->suivant = NULL;

    return newLivre;
}

/* Ex. 2.3 - Creation d'une bibliothèque */
BiblioH* creer_biblio_h(int m){

    BiblioH* newBiblio = malloc(sizeof(BiblioH));
    if (!newBiblio){
        fprintf(stderr, "Erreur dans l'allocation mémoire\n");
        return NULL;
    }

    newBiblio->nE = 0;
    newBiblio->m = m;
    newBiblio->T = NULL;

    return newBiblio;
}

/* Ex. 2.3 - Liberer une bibliothèque */
void liberer_livre_h(LivreH* l){

    if (!l){
        return;
    }

    if (l->titre != NULL){
        free(l->titre);
        l->titre = NULL;
    }
    
    if (l->auteur != NULL){
        free(l->auteur);
        l->auteur = NULL;
    }

    free(l);

    return;
}

/* Ex. 2.3 - Liberer une bibliothèque */
void liberer_biblio_h(BiblioH* b){

    if (!b){
        return;
    }

    if (b->T != NULL){
        for(int i = 0; i < b->m; i++){
            LivreH* curr = b->T[i];
            while(curr != NULL){
                LivreH* temp = curr->suivant;
                liberer_livre(curr);
                curr = temp;
            }
        }
        free(b->T);
        b->T = NULL;
    }

    free(b);

    return;
}



/* Ex. 2.4 - Définir la fonction de hachage */
int fonctionHachage(int cle, int m){
    double a = ((sqrt(5) - 1) / 2);
    double hash = m * ((cle * a) - floor(cle * a));
    return (int)floor(hash);
}

void inserer_h(BiblioH* b, int num, char* titre, char* auteur){
    if (!b){
        fprintf(stderr, "La bibliothéque envoyé est vide");
        return;
    }

    int idx = 0;

    /* Calculer la case dans le tableau */
    idx = fonctionHachage(fonctionClef(auteur), b->m);

    /* Insertion */
    LivreH* nouveauLivre = creer_livre_h(num, titre, auteur);
    if (!nouveauLivre){
        fprintf(stderr, "Erreur dans l'allocation mémoire");
    }
    nouveauLivre->suivant = b->T[idx];
    b->T[idx] = nouveauLivre;
    b->nE++;

    return;
}


/* Ex. 2.6 - Afficher un livre */
void afficher_livre_h(LivreH* l){
    if (!l){
        fprintf(stderr, "Le livre passé en paramétre est NULL\n");
        printf("Livre NULL, merci d'indiquer un autre livre\n");
        return;
    }
    printf("------------------\n");
    printf("Numéro d'enregistrement : %d\nTitre : %s\nAuteur : %s\nClé : %d\n", l->num, l->titre, l->auteur, l->clef);
    printf("------------------\n");
    return;
}

/* Ex. 2.6 - Afficher une bibliothèque*/
void afficher_biblio_h(BiblioH* b){
    if (!b){
        fprintf(stderr, "La bibliothèque passé en paramétre est NULL\n");
        printf("Bibliothèque NULL, merci d'indiquer une autre bibliothèque\n");
        return;
    }

    LivreH* curr = NULL;

    for (int x=0; x < b->m; x++){
        curr = b->T[x];
        while(curr != NULL){
            afficher_livre_h(curr);
            curr = curr->suivant;
        }
    }

    return;
}