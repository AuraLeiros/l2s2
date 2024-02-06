/* Aura Leirós García - 21218034 */
/* aura.leiros@etu.sorbonne-universite.fr */
/* biblioLC.c - TP3 & TP4 SDD */

#include <stdio.h>
#include "biblioLC.h"

Livre* creer_livre(int num, char* titre, char* auteur){

    /* Création et vérification de l'allocation mémoire d'un livre.*/
    Livre *newLivre = malloc(sizeof(Livre));
    assert(newLivre != NULL);

    /* Insertion des valeurs du nouveau livre */
    newLivre->num=num;
    newLivre->titre = strdup(titre);
    newLivre->auteur = strdup(auteur);
    newLivre->suiv = NULL;

    /* Si strdup retourne un erreur, alors réalise une déallocation mémoire et retourne le pointeur NULL */
    if (newLivre->titre == NULL || newLivre->auteur == NULL){
        liberer_livre(newLivre);
        return NULL;
    }

    return newLivre;
}

void liberer_livre(Livre* l){

    /* Libération de chaque pointeur puis tout le livre */
    free(l->titre);
    free(l->auteur);
    free(l);
}

Biblio* creer_biblio(){

    /* Allocation mémoire et vérification de l'allocation */
    Biblio* newBiblio = malloc(sizeof(Biblio));
    assert(newBiblio != NULL);
    return newBiblio;
}

void liberer_biblio(Biblio* b){
    Livre *temp;
    Livre *curr = b->livre;

    while(curr != NULL){
        temp = curr->suiv;
        liberer_livre(curr);
        curr = temp;
    }

    free(b);
}

void inserer_en_tete(Biblio b*, int num, char* titre, char* auteur){

    Livre *temp = creer_livre(num, titre, auteur);
    temp->suiv = b->livre;
    b->livre = temp;
}

