/* Aura Leirós García - 21218034 */
/* aura.leiros@etu.sorbonne-universite.fr */
/* biblioH.c - TP3 & TP4 SDD */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "biblioH.h"

/*-------------------------------*/
   /* Declaration de fonctions */
/*-------------------------------*/


/*-------------------------------*/
    /* Éléments de hachage */
/*-------------------------------*/

/* Ex 2.2 - Fonction pour générer une clé */
int fonctionClef(char* auteur){
    if (!auteur || auteur[0] == '\0'){
        fprintf(stderr, "Erreur dans les paramétres\n");
        return EXIT_FAILURE;
    }

    int res = 0;

    while(*auteur){
        res += (int)*auteur;
        auteur++;
    }

    return res;
}

/* Ex. 2.4 - Définir la fonction de hachage */
int fonctionHachage(int cle, int m){
    if((cle < 0) || (m < 1)){
        fprintf(stderr, "Erreur dans les paramétres\n");
        return EXIT_FAILURE;
    }

    double a = ((sqrt(5) - 1) / 2);
    double hash = m * ((cle * a) - floor(cle * a));
    return (int)floor(hash);
}

/*-------------------------------*/
/* Initialisation de structures */
/*-------------------------------*/

/* Ex. 2.3 - Creation d'un livre */
LivreH* creer_livre_h(int num, char* titre, char* auteur){
    if((num < 0) || !titre || !auteur || titre[0] == '\0' || auteur[0] == '\0'){
        fprintf(stderr, "Erreur dans les paramétres\n");
        return NULL;
    }

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
    if (m < 1){
        fprintf(stderr, "Erreur\n");
        return NULL;
    }

    BiblioH* newBiblio = malloc(sizeof(BiblioH));
    if (!newBiblio){
        fprintf(stderr, "Erreur dans l'allocation mémoire\n");
        return NULL;
    }

    newBiblio->nE = 0;
    newBiblio->m = m;
    newBiblio->T = calloc(m, sizeof(LivreH*));
    if(!newBiblio->T){
        fprintf(stderr, "Erreur dans l'allocation memoire\n");
        return NULL;
    }

    return newBiblio;
}


/*-------------------------------*/
        /* Recherche */
/*-------------------------------*/

LivreH* recherche_par_num_h(BiblioH* b, int num){
    if (!b || num < 0){
        fprintf(stderr, "Erreur dans les paramétres\n");
        return NULL;
    }

    LivreH* curr = NULL;

    for(int x=0; x < b->m; x++){
        curr = b->T[x];
        while(curr != NULL){
            if(curr->num == num){
                return curr;
            }
            curr = curr->suivant;
        }
    }
    return NULL;
}


LivreH* recherche_par_titre_h(BiblioH* b, char* titre){
    if (!b || !titre || titre[0] == '\0'){
        fprintf(stderr, "Erreur dans les paramétres\n");
        return NULL;
    }

    LivreH* curr = NULL;

    for(int x=0; x < b->m; x++){
        curr = b->T[x];
        while(curr != NULL){
            if(strcmp(curr->titre, titre) == 0){
                return curr;
            }
            curr = curr->suivant;
        }
    }
    return NULL;
}

/* Ex. 2.6 - Recherche de tous les livres d'un même auteur */
BiblioH* recherche_par_auteur_h(BiblioH* b, char* auteur){
    if (!b || !auteur || auteur[0] == '\0' || b->nE == 0){
        fprintf(stderr, "Erreur dans les paramétres\n");
        return NULL;
    }

    LivreH* curr = NULL;

    int m = floor(b->m / 10);
    BiblioH* newBiblio = creer_biblio_h(m);
    if (!newBiblio){
        fprintf(stderr, "Erreur dans l'allocation mémoire\n");
        return NULL;
    }
   

    for(int x=0; x < b->m; x++){
        curr = b->T[x];
        while (curr != NULL){
            if(strcmp(curr->auteur, auteur) == 0){
                inserer_h(newBiblio, curr->num, curr->titre, curr->auteur);
            }
            curr = curr->suivant;
        }
    }

    if(newBiblio->nE > 0){
        return newBiblio;
    } else {
        liberer_biblio_h(newBiblio);
        return NULL;
    }
}

/* Ex. 2.6 - Recherche de ouvrages dupliqués. */
LivreH* recherche_dupliques_h(BiblioH* b){
    if(!b || (b->nE < 0)){
        fprintf(stderr, "Erreur dans les paramétres\n");
        return NULL;
    }

    LivreH* res = NULL;
    LivreH* res_aux = NULL;


    for(int x=0; x < b->m; x++){
        LivreH* curr_out = b->T[x];
        while (curr_out != NULL){
            for (int y=0; y < b->m; y++){
                LivreH* curr_in = b->T[y];
                while(curr_in != NULL){
                    if ((strcmp(curr_out->auteur, curr_in->auteur) == 0) && (strcmp(curr_out->titre, curr_in->titre) == 0) && (curr_out->num != curr_in->num)){
                        if (!res){
                            res = creer_livre_h(curr_out->num, curr_out->titre, curr_out->auteur);
                            res_aux = res;
                        } else {
                            res->suivant = creer_livre_h(curr_out->num, curr_out->titre, curr_out->auteur);
                            res = res->suivant;
                        }
                        break;
                    }
                    curr_in = curr_in->suivant;
                }
            }
            curr_out = curr_out->suivant;
        }
    }

    return res_aux;
}


/*-------------------------------*/
  /* Manipulation de structures*/
/*-------------------------------*/

/*Ex. 2.5. - Ajout d'un nouveau livre à la bibliothèque */
void inserer_h(BiblioH* b, int num, char* titre, char* auteur){
    if (!b || (b->nE < 0) || (num < 0) || !titre || !auteur || titre[0] == '\0' || auteur[0] == '\0'){
        fprintf(stderr, "Erreur dans les paramétres\n");
        return;
    }

    int idx = 0;

    /* Calculer la case dans le tableau */
    idx = fonctionHachage(fonctionClef(auteur), b->m);
    if(idx < 0 || idx >= b->m){
        fprintf(stderr, "erreur, hors borne");
        return;
    }

    /* Insertion */
    LivreH* nouveauLivre = creer_livre_h(num, titre, auteur);
    if (nouveauLivre != NULL){
        nouveauLivre->suivant = b->T[idx];
        b->T[idx] = nouveauLivre;
        b->nE++;
    }
    return;
}

/* Ex. 2.6 - Fusion de deux bibliothèques*/
BiblioH* fusion_biblio_h(BiblioH* b1, BiblioH* b2){
    /* Préconditions */
    if (!b1 && !b2){
        fprintf(stderr, "Erreur dans les paramétres\n");
        return NULL;
    } else if (!b1 && (b2 != NULL)){
        //fprintf(stderr, "Erreur dans les paramétres\n");
        return b2;
    } else if ((b1 != NULL) && (!b2)){
        //fprintf(stderr, "Erreur dans les paramétres\n");
        return b1;
    } else if (b1 == b2){
        //fprintf(stderr, "Erreur dans les paramétres\n");
        return b1;
    }

    LivreH* curr = NULL;

    for (int x=0; x < b2->m; x++){
        curr = b2->T[x];
        while(curr != NULL){
            inserer_h(b1, curr->num, curr->titre, curr->auteur);
            curr = curr->suivant;
        }
    }
    liberer_biblio_h(b2);
    return b1;
}

/* Ex. 2.6 - suppression d'un ouvrage */
BiblioH* suppression_ouvrage_h(BiblioH* b, int num, char* auteur, char* titre){
    if (!b || (b->nE < 0) || (num < 0) || !titre || !auteur || titre[0] == '\0' || auteur[0] == '\0'){
        fprintf(stderr, "Erreur dans les paramétres\n");
        return NULL;
    }

    LivreH* curr = NULL;
    LivreH* before = NULL;

    for(int x=0; x < b->m; x++){
        curr = b->T[x];
        before = NULL;
        while(curr != NULL){
            if ((strcmp(curr->auteur, auteur) == 0) && (strcmp(curr->titre, titre) == 0) && (curr->num == num)){
                LivreH* temp = curr;
                if (!before){
                    b->T[x] = curr->suivant;
                } else {
                    before->suivant = curr->suivant;
                }
                curr = curr->suivant; 
                liberer_livre_h(temp);
                b->nE--;
                return b;
            } else {
                before = curr;
                curr = curr->suivant;
            }

        }
    }
    return b;
}


/*-------------------------------*/
    /* Libération mémoire */
/*-------------------------------*/

/* Ex. 2.3 - Liberer une bibliothèque */
void liberer_livre_h(LivreH* l){
    if (!l){
        fprintf(stderr, "Erreur dans les paramétres\n");
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
        fprintf(stderr, "Erreur dans les paramétres\n");
        return;
    }

    if (b->T != NULL){
        for(int i = 0; i < b->m; i++){
            LivreH* curr = b->T[i];
            while(curr != NULL){
                LivreH* temp = curr->suivant;
                liberer_livre_h(curr);
                curr = temp;
            }
        }
        free(b->T);
        b->T = NULL;
    }

    free(b);

    return;
}

/*-------------------------------*/
        /* Affichage */
/*-------------------------------*/

/* Ex. 2.6 - Afficher un livre */
void afficher_livre_h(LivreH* l){
    if (!l){
        fprintf(stderr, "Erreur dans les paramétres\n");
        printf("Livre NULL, veuillez indiquer un autre livre\n");
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
        fprintf(stderr, "Erreur dans les paramétres\n");
        printf("Bibliothèque NULL, veuillez indiquer une autre bibliothèque\n");
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
}

