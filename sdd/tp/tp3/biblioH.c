/* Aura Leirós García - 21218034 */
/* aura.leiros@etu.sorbonne-universite.fr */
/* biblioH.c - TP3 & TP4 SDD */

#include <stdio.h>
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
LivreH* creer_livre(int num, char* titre, char* auteur){

    LivreH* newLivre = malloc(sizeof(LivreH));
    if (!newLivre){
        fprintf(stderr, "Erreur dans l'allocation mémoire\n");
        return NULL;
    }

    newLivre->clef = fonctionClef(auteur);
    newLivre->num = num;

    newLivre->titre = strdup(titre);
    if (!newLivre->titre){
        liberer_livre(newLivre);
        return NULL;
    }

    newLivre->auteur = strdup(auteur);
    if (!newLivre->auteur){
        liberer_livre(newLivre);
        return NULL;
    }
    newLivre->suivant = NULL;

    return newLivre;
}

/* Ex. 2.3 - Creation d'une bibliothèque */
BiblioH* creer_biblio(int m){

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
void liberer_livre(LivreH* l){

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
void liberer_biblio(BiblioH* b){

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



