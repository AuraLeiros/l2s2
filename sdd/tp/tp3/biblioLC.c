/* Aura Leirós García - 21218034 */
/* aura.leiros@etu.sorbonne-universite.fr */
/* biblioLC.c - TP3 & TP4 SDD */

#include <stdio.h>
#include "biblioLC.h"

/* Ex. 1.2 - Creation d'un livre */
Livre* creer_livre(int num, char* titre, char* auteur){

    Livre *newLivre = malloc(sizeof(Livre));
    if (!newLivre){
        fprintf(stderr, "Erreur dans l'allocation de la mémoire !\n");
        return NULL;
    }

    newLivre->num=num;

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
    newLivre->suiv = NULL;

    return newLivre;
}

/* Ex. 1.2 - Libération de la mémoire alloué à un livre */
void liberer_livre(Livre* l){

    if (!l){
        return;
    }
    
    free(l->titre);
    free(l->auteur);
    free(l);
}

/* Ex. 1.2 - Creation d'une bibliothèque */
Biblio* creer_biblio(){

    Biblio* newBiblio = malloc(sizeof(Biblio));
    if (!newBiblio){
        fprintf(stderr, "Erreur dans l'allocation mémoire de la bibliothèque !\n");
        return NULL;
    }

    newBiblio->l = NULL;

    return newBiblio;
}

/* Ex. 1.2 - Libèration de la mémoire alloué à une bibliothèque */
void liberer_biblio(Biblio* b){

    if (!b){
        return;
    }

    Livre *temp;
    Livre *curr = b->l;

    while(curr != NULL){
        temp = curr->suiv;
        liberer_livre(curr);
        curr = temp;
    }

    free(b);
}

/* Ex. 1.2 - Ajout d'un nouveau livre dans tête de la bibliothèque */
void inserer_en_tete(Biblio* b, int num, char* titre, char* auteur){

    Livre *temp = creer_livre(num, titre, auteur);

    if (!temp){
        fprintf(stderr, "Erreur dans l'allocation mémoire !\n");
        return;
    }

    temp->suiv = b->l;
    b->l = temp;
}

/* Ex. 1.6 - Afficher un livre */
void afficher_livre(Livre* l){
    if (!l != NULL){
        fprintf(stderr, "Le pointeur donné est NULL !\n");
        return;
    }
    printf("------------------\n");
    printf("Numéro d'enregistrement : %d\nTitre : %s\nAuteur : %s\n", l->num, l->titre, l->auteur);
    printf("------------------\n");
}

/* Ex. 1.6 - Afficher une bibliotheque */
void afficher_biblio(Biblio* b){

    Livre* curr = b->l;

    while(curr != NULL){
        afficher_livre(curr);
        curr = curr->suiv;
    }
}

/* Ex. 1.6 - Rechercher un livre par son numéro */
Livre* recherche_livre_num(Biblio* b, int num){

    Livre* curr = b->l;

    while(curr != NULL){
        if (curr->num == num){
            return curr;
        }
        curr = curr->suiv;
    }

    printf("Le livre n'a pas été trouvé dans la bibliothèque !\nVeuillez vérifier le numéro.");
    return NULL;
}

/* Ex. 1.6 - Rechercher un livre par son titre */
Livre* recherche_par_titre(Biblio* b, char* titre){

    Livre* curr = b->l;

    while(curr != NULL){
        if (strcmp(curr->titre, titre) == 0){
            return curr;
        }
        curr = curr->suiv;
    }

    printf("Le livre n'a pas été trouvé !\nVeuillez vérifier le titre.");
    return NULL;
}

/* Ex. 1.6 - Recherche de tous les livres d'un même auteur */
Biblio* recherche_par_auteur(Biblio* b, char* auteur){

    Livre* curr = b->l;
    Livre* next;
    Biblio* biblioAuteur = creer_biblio();

    while (curr != NULL){
        if (strcmp(curr->auteur, auteur) == 0){
            inserer_en_tete(biblioAuteur, curr->num, curr->titre, curr->auteur);
        }
        curr = curr->suiv;
    }

    return biblioAuteur;
}

/* Ex. 1.6 - Supression d'un ouvrage */
Biblio* suppresion_ouvrage(Biblio* b, int num, char* auteur, char* titre){

    Livre* curr = b->l;
    Livre* prev = NULL;
    Livre* next;

    while(curr != NULL){
        next = curr->suiv;
        if ((curr->num == num) && (strcmp(curr->auteur, auteur) == 0) && (strcmp(curr->titre, titre) == 0)){
            if (prev == NULL){
                b->l = next;
            } else {
                prev->suiv = next;
            }
            liberer_livre(curr);
        } else {
            prev = curr;
        }
        curr = next;
    }
    return b;
}

/* Ex. 1.6 - Fusion de deux bibliothèques */
Biblio* fusion_biblio(Biblio* b1, Biblio* b2){

    /* Préconditions */
    if (!b1 && !b2){
        printf("Les deux bibliothèques passées en paramètres sont nulles !");
        return NULL;
    } else if (!b1 && (b2 != NULL)){
        return b2;
    } else if ((b1 != NULL) && (!b2)){
        return b1;
    } else if (b1 == b2){
        return b1;
    }

    /* Trouver le dernier livre de b1 */
    Livre* end_b1 = b1->l;
    while(end_b1->suiv != NULL){
        end_b1 = end_b1->suiv;
    }

    /* Ajout des livres a b1 et libération mémoire de b2 */
    end_b1->suiv = b2->l;
    b2->l = NULL;
    free(b2);

    return b1;
}

Livre* recherche_dupliques(Biblio* b){

    Livre* res = NULL;
    Livre* res_aux = NULL;
    Livre* curr = b->l;
    Livre* inner_curr = NULL;
    int occurrences;

    while (curr != NULL){

        inner_curr = b->l;
        occurrences = 0;

        /* Itération sur la liste pour regarder si le livre actuel a un deuxième exemplaire dans la liste */
        while (inner_curr != NULL){
            if ((strcmp(curr->titre, inner_curr->titre) == 0) && (strcmp(curr->auteur, inner_curr->auteur) == 0) && (curr->num != inner_curr->num)){
                occurrences++;
                break;
            }
            inner_curr = inner_curr->suiv;
        }

        /* Ajouter au resultat si une ocurrence à été trouvé */
        if (occurrences > 0){
            if (!res){
                res = creer_livre(curr->num, curr->titre, curr->auteur);
                res_aux = res;
            } else {
                res_aux->suiv = creer_livre(curr->num, curr->titre, curr->auteur);
                res_aux = res_aux->suiv;
            }
        }
        curr = curr->suiv;
    }
    return res;
}