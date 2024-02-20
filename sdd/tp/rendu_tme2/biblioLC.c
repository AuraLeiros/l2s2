#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "biblioLC.h"

/*-------------------------------*/
/* Initialisation de structures */
/*-------------------------------*/

/* Ex. 1.2 - Creation d'un livre */
Livre* creer_livre_lc(int num, char* titre, char* auteur){
    
    if(num < 0 || !titre || !auteur || titre[0] == '\0' || auteur[0] == '\0'){
        fprintf(stderr, "Un des paramètres n'est pas valide\n");
        return NULL;
    }

    Livre *newLivre = malloc(sizeof(Livre));
    if (!newLivre){
        fprintf(stderr, "Erreur dans l'allocation de la mémoire !\n");
        return NULL;
    }

    newLivre->num=num;

    newLivre->titre = strdup(titre);
    if (!newLivre->titre){
        liberer_livre_lc(newLivre);
        return NULL;
    }

    newLivre->auteur = strdup(auteur);
    if (!newLivre->auteur){
        liberer_livre_lc(newLivre);
        return NULL;
    }

    newLivre->suivant = NULL;

    return newLivre;
}

/* Ex. 1.2 - Creation d'une bibliothèque */
Biblio* creer_biblio_lc(){

    Biblio* newBiblio = malloc(sizeof(Biblio));
    if (!newBiblio){
        fprintf(stderr, "Erreur dans l'allocation mémoire de la bibliothèque !\n");
        return NULL;
    }

    newBiblio->l = NULL;

    return newBiblio;
}

/*-------------------------------*/
        /* Recherche */
/*-------------------------------*/

/* Ex. 1.6 - Rechercher un livre par son numéro */
Livre* recherche_par_num_lc(Biblio* b, int num){
    
    if(!b || (num < 0)){
        fprintf(stderr, "Un des paramètres n'est pas valide\n");
        return NULL;
    }

    Livre* curr = b->l;

    while(curr != NULL){
        if (curr->num == num){
            return curr;
        }
        curr = curr->suivant;
    }

    printf("Le livre n'a pas été trouvé dans la bibliothèque !\nVeuillez vérifier le numéro.\n");
    return NULL;
}

/* Ex. 1.6 - Rechercher un livre par son titre */
Livre* recherche_par_titre_lc(Biblio* b, char* titre){

    if (!b || !titre || titre[0] == '\0'){
        fprintf(stderr, "Un des paramètres n'est pas valide\n");
        return NULL;
    }

    Livre* curr = b->l;

    while(curr != NULL){
        if (strcmp(curr->titre, titre) == 0){
            return curr;
        }
        curr = curr->suivant;
    }

    printf("Le livre n'a pas été trouvé !\nVeuillez vérifier le titre.\n");
    return NULL;
}

/* Ex. 1.6 - Recherche de tous les livres d'un même auteur */
Biblio* recherche_par_auteur_lc(Biblio* b, char* auteur){

    if (!b){
        fprintf(stderr, "Un des paramètres n'est pas valide\n");
        return NULL;
    }

    Livre* curr = b->l;
    Biblio* biblioAuteur = creer_biblio_lc();

    while (curr != NULL){
        if (strcmp(curr->auteur, auteur) == 0){
            inserer_en_tete_lc(biblioAuteur, curr->num, curr->titre, curr->auteur);
        }
        curr = curr->suivant;
    }

    return biblioAuteur;
}

/* Ex. 1.6 - Recherche de ouvrages dupliqués. */
Livre* recherche_dupliques_lc(Biblio* b){

    if (!b){
        fprintf(stderr, "Un des paramètres n'est pas valide\n");
        return NULL;
    }

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
            inner_curr = inner_curr->suivant;
        }

        /* Ajouter au resultat si une ocurrence à été trouvé */
        if (occurrences > 0){
            if (!res){
                res = creer_livre_lc(curr->num, curr->titre, curr->auteur);
                res_aux = res;
            } else {
                res_aux->suivant = creer_livre_lc(curr->num, curr->titre, curr->auteur);
                res_aux = res_aux->suivant;
            }
        }
        curr = curr->suivant;
    }
    return res;
}


/*-------------------------------*/
    /* Libération de mémoire */
/*-------------------------------*/

/* Ex. 1.2 - Libération de la mémoire alloué à un livre */
void liberer_livre_lc(Livre* l){

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
    l = NULL;

    return;
}

/* Ex. 1.2 - Libèration de la mémoire alloué à une bibliothèque */
void liberer_biblio_lc(Biblio* b){

    if (!b){
        return;
    }

    Livre *temp;
    Livre *curr = b->l;

    while(curr != NULL){
        temp = curr->suivant;
        liberer_livre_lc(curr);
        curr = temp;
    }

    free(b);
}


/*-------------------------------*/
/* Manipulation de structures */
/*-------------------------------*/

void inserer_en_tete_lc(Biblio* b, int num, char* titre, char* auteur){

    if (!b || (num < 0) || !titre || !auteur || titre[0] == '\0' || auteur[0] == '\0'){
        fprintf(stderr, "Un des paramètres n'est pas valide\n");
        return;
    }

    Livre *temp = creer_livre_lc(num, titre, auteur);
    if (!temp){
        fprintf(stderr, "Erreur dans l'allocation mémoire !\n");
        return;
    }

    temp->suivant = b->l;
    b->l = temp;
}

/* Ex. 1.6 - Fusion de deux bibliothèques */
Biblio* fusion_biblio_lc(Biblio* b1, Biblio* b2){

    /* Préconditions */
    if (!b1 && !b2){
        fprintf(stderr, "Un des paramètres n'est pas valide");
        return NULL;
    } else if (!b1 && (b2 != NULL)){
        fprintf(stderr, "Un des paramètres n'est pas valide");
        return b2;
    } else if ((b1 != NULL) && (!b2)){
        fprintf(stderr, "Un des paramètres n'est pas valide");
        return b1;
    } else if (b1 == b2){
        fprintf(stderr, "Un des paramètres n'est pas valide");
        return b1;
    }

    /* Trouver le dernier livre de b1 */
    Livre* end_b1 = b1->l;
    while(end_b1->suivant != NULL){
        end_b1 = end_b1->suivant;
    }

    /* Ajout des livres a b1 et libération mémoire de b2 */
    end_b1->suivant = b2->l;
    b2->l = NULL;
    free(b2);

    return b1;
}

/* Ex. 1.6 - Supression d'un ouvrage */
Biblio* suppresion_ouvrage_lc(Biblio* b, int num, char* auteur, char* titre){

    if (!b || (num < 0) || !titre || !auteur || titre[0] == '\0' || auteur[0] == '\0'){
        fprintf(stderr, "Un des paramètres n'est pas valide\n");
        return NULL;
    }

    Livre* curr = b->l;
    Livre* prev = NULL;
    Livre* next;

    while(curr != NULL){
        next = curr->suivant;
        if ((curr->num == num) && (strcmp(curr->auteur, auteur) == 0) && (strcmp(curr->titre, titre) == 0)){
            if (prev == NULL){
                b->l = next;
            } else {
                prev->suivant = next;
            }
            liberer_livre_lc(curr);
        } else {
            prev = curr;
        }
        curr = next;
    }
    return b;
}


/*-------------------------------*/
        /* Affichage */
/*-------------------------------*/

/* Ex. 1.6 - Afficher un livre */
void afficher_livre_lc(Livre* l){
    if (!l){
        fprintf(stderr, "Un des paramètres n'est pas valide\n");
        return;
    }
    printf("\n\n");
    printf("══════════════════════════════════\n");
    printf("Numéro d'enregistrement : %d\nTitre : %s\nAuteur : %s\n", l->num, l->titre, l->auteur);
    printf("══════════════════════════════════\n");
    printf("\n\n");
}

/* Ex. 1.6 - Afficher une bibliotheque */
void afficher_biblio_lc(Biblio* b){
    
    if(!b){
        fprintf(stderr, "Un des paramètres n'est pas valide\n");
        return;
    }

    Livre* curr = b->l;

    while(curr != NULL){
        afficher_livre_lc(curr);
        curr = curr->suivant;
    }
}

