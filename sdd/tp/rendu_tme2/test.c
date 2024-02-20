/* Aura Leirós García - 21218034 */
/* aura.leiros@etu.sorbonne-universite.fr */
/* test.c - TP3 & TP4 SDD */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "test.h"
#include "biblioLC.h"
#include "biblioH.h"
#include "entreeSortieLC.h"
#include "entreeSortieH.h"


/*-------------------------------------------------------------------*/

/*-------------------------------*/
        /* biblioLC.c */
/*-------------------------------*/


void tous_tests_lc(){

    printf("Tests des fonctions définies dans biblioLC.c... \n\n");

    creer_livre_lc_test();

    creer_biblio_lc_test();

    recherche_par_num_lc_test();

    recherche_par_titre_lc_test();

    recherche_par_auteur_lc_test();

    recherche_dupliques_lc_test();

    liberer_livre_lc_test();

    liberer_biblio_lc_test();

    inserer_en_tete_lc_test();

    fusion_biblio_lc_test();

    suppression_ouvrage_lc_test();

}

/*-------------------------------*/
/* Initialisation de structures */
/*-------------------------------*/

void creer_livre_lc_test(){

    /* TEST 1 : Paramétres valides */
    Livre* test1 = creer_livre_lc(2123, "desassossego", "pessoa");
    assert(test1 != NULL);
    liberer_livre_lc(test1);

    /* TEST 2; Paramétres invalides */
    //Livre* test2 = creer_livre_lc(-1223, "cousas", "castelao");
    //assert(!test2);

    printf("creer_livre_lc : OK\n");
}

void creer_biblio_lc_test() {
    /* TEST 1 */
    Biblio* test1 = creer_biblio_lc();
    assert(test1 != NULL);

    liberer_biblio_lc(test1);

    printf("creer_biblio_lc: OK\n");
    
    return;
}

/*-------------------------------*/
        /* Recherche */
/*-------------------------------*/

void recherche_par_num_lc_test() {

    Biblio* testBiblio = creer_biblio_lc();
    inserer_en_tete_lc(testBiblio, 9323, "DIXTIGSIE", "svey");

    /* TEST 1: Paramètres valides */
    Livre* test1 = recherche_par_num_lc(testBiblio, 9323);
    assert(test1 != NULL);
    
    /* TEST 2: Paramètres invalides */
    //Livre* test2 = recherche_par_num_lc(testBiblio, -123);
    //assert(!test2);

    liberer_biblio_lc(testBiblio);

    printf("recherche_par_num_lc: OK\n");
    
    return;
}

void recherche_par_titre_lc_test() {

    Biblio* testBiblio = creer_biblio_lc();
    inserer_en_tete_lc(testBiblio, 123, "DIXTIGSIE", "svey");

    /* TEST 1: Paramètres valides */
    Livre* test1 = recherche_par_titre_lc(testBiblio, "DIXTIGSIE");
    assert(test1 != NULL);  
    
    /* TEST 2: Paramètres invalides */ // Comentaire pour eviter le stderr, mais teste
    //Livre* test2 = recherche_par_titre_lc(testBiblio, "ESTATUTO_XURIDICO_DA_LINGUA_GALEGA");
    //assert(!test2);

    liberer_biblio_lc(testBiblio);

    printf("recherche_par_titre_lc: OK\n");
    
    return;
}

void recherche_par_auteur_lc_test() {
    /* TEST 1: Paramètres valides */
    Biblio* testBiblio = creer_biblio_lc();
    inserer_en_tete_lc(testBiblio, 123, "MENINAS", "svey");
    Biblio* test1 = recherche_par_auteur_lc(testBiblio, "svey");
    assert(test1 != NULL);
    liberer_biblio_lc(test1);
    
    /* TEST 2: Paramètres invalides */
    Biblio* test2 = recherche_par_auteur_lc(testBiblio, "PEÑARROJA_PAZ");
    assert(test2->l == NULL);

    printf("recherche_par_auteur_lc: OK\n");
    liberer_biblio_lc(test2);
    liberer_biblio_lc(testBiblio);
    
    return;
}

void recherche_dupliques_lc_test() {
    /* TEST 1: Paramètres valides */
    Biblio* testBiblio = creer_biblio_lc();
    inserer_en_tete_lc(testBiblio, 123, "LUSIADAS", "CAMOES");
    inserer_en_tete_lc(testBiblio, 321, "LUSIADAS", "CAMOES");

    Livre* test1 = recherche_dupliques_lc(testBiblio);
    assert(test1 != NULL);
    liberer_livre_lc(test1);
    liberer_biblio_lc(testBiblio);
    
    
    /* TEST 2: Paramètres invalides */
    Biblio* biblio_vide = creer_biblio_lc();
    Livre* test2 = recherche_dupliques_lc(biblio_vide);
    assert(!test2);
    liberer_biblio_lc(biblio_vide); 

    printf("recherche_dupliques_lc: OK\n");
    
    return;
}


/*-------------------------------*/
    /* Libération de mémoire */
/*-------------------------------*/

void liberer_livre_lc_test() {
    /* TEST 1: Paramètre valide avec titre et auteur */
    Livre* test1 = creer_livre_lc(1123, "LUSIADAS", "CAMOES");
    assert(test1 != NULL && test1->titre != NULL && test1->auteur != NULL);
    liberer_livre_lc(test1);
    
    /* TEST 2: Paramètre valide avec titre NULL */ // Teste mais commenté pour eviter le stderr
    /*Livre* test2 = creer_livre_lc(1124, NULL, "CAMOES");
    assert(!test2);*/
    
    /* TEST 3: Paramètre valide avec auteur NULL */ // Teste mais commenté pour eviter le stderr
    /*Livre* test3 = creer_livre_lc(1125, "LUSIADAS", NULL);
    assert(!test3);*/
    
    printf("liberer_livre_lc: OK\n");
    return;
}

void liberer_biblio_lc_test() {

    /* TEST 1: Bibliothèque valide avec plusieurs livres */
    Biblio* biblio1 = creer_biblio_lc();
    inserer_en_tete_lc(biblio1, 1123, "LUSIADAS", "LUIS_DE_CAMOES");
    inserer_en_tete_lc(biblio1, 1124, "MAIS_ALÁ", "VARIOS");
    assert(biblio1 != NULL && biblio1->l != NULL);
    liberer_biblio_lc(biblio1);
    
    /* TEST 2: Bibliothèque valide avec un seul livre */
    Biblio* biblio2 = creer_biblio_lc();
    inserer_en_tete_lc(biblio2, 1125, "DON QUIJOTE", "MIGUEL_DE_CERVANTES");
    assert(biblio2 != NULL && biblio2->l != NULL);
    liberer_biblio_lc(biblio2);
    
    /* TEST 3: Bibliothèque valide sans livres */
    Biblio* biblio3 = creer_biblio_lc();
    assert(biblio3 != NULL && biblio3->l == NULL);
    liberer_biblio_lc(biblio3);
    
    printf("liberer_biblio_lc: OK\n");
    return;
}


/*-------------------------------*/
/* Manipulation de structures */
/*-------------------------------*/

void inserer_en_tete_lc_test() {

    /* TEST 1: Inserer dans une bibliothèque valide avec des paramètres valides */
    Biblio* biblio1 = creer_biblio_lc();
    inserer_en_tete_lc(biblio1, 1123, "LUSIADAS", "CAMOES");
    assert(biblio1 != NULL);
    liberer_biblio_lc(biblio1);

    /* TEST 2: Inserer avec un numéro négatif */ // Teste et OK mais commente pour eviter les stderr
    /*Biblio* biblio2 = creer_biblio_lc();
    inserer_en_tete_lc(biblio2, -1, "RAYUELA", "CORTAZAR");
    assert(biblio2 != NULL && biblio2->l == NULL);
    liberer_biblio_lc(biblio2);
    */
    /* TEST 3: Inserer avec un titre NULL */
    /*Biblio* biblio3 = creer_biblio_lc();
    inserer_en_tete_lc(biblio3, 1124, NULL, "CAMOES");
    assert(biblio3 != NULL && biblio3->l == NULL);
    liberer_biblio_lc(biblio3);
    */
    printf("inserer_en_tete_lc: OK\n");
    return;
}

void fusion_biblio_lc_test() {
    Biblio* b1 = creer_biblio_lc();
    Biblio* b2 = creer_biblio_lc();
    
    inserer_en_tete_lc(b1, 1, "LUSIADAS", "CAMOES");
    inserer_en_tete_lc(b2, 2, "ETRANGER", "CAMUS");

    Biblio* merged = fusion_biblio_lc(b1, b2);
    assert(merged == b1);
    assert(merged->l != NULL && merged->l->suivant != NULL);

    Biblio* b3 = creer_biblio_lc();
    inserer_en_tete_lc(b3, 3, "Book3", "Author3");
    merged = fusion_biblio_lc(NULL, b3);
    assert(merged == b3);

    liberer_biblio_lc(b1);
    liberer_biblio_lc(b3);

    printf("fusion_biblio_lc : OK\n");
    return;
}

void suppression_ouvrage_lc_test() {

    Biblio* b = creer_biblio_lc();

    inserer_en_tete_lc(b, 1, "MARINA", "RUIZ_ZAFON");
    inserer_en_tete_lc(b, 2, "PETIT_PRINCE", "ST_EXUPERY");
    inserer_en_tete_lc(b, 3, "SEMPRE_EN_GALIZA", "Title3");

    b = suppression_ouvrage_lc(b, 2, "ST_EXUPERY", "PETIT_PRINCE");
    Livre* curr = b->l;
    while (curr != NULL) {
        assert(!(curr->num == 2 && strcmp(curr->auteur, "ST_EXUPERY") == 0 && strcmp(curr->titre, "PETIT_PRINCE") == 0));
        curr = curr->suivant;
    }

    Biblio* result = suppression_ouvrage_lc(b, 4, "Author4", "Title4");
    assert(result == b);

    liberer_biblio_lc(b);

    printf("suppression_ouvrage_lc: OK\n");
}

/*--------------------------------------------------------------------*/

/*-------------------------------*/
        /* biblioH.h */
/*-------------------------------*/

void tous_tests_h(){

    printf("\nTous les tests pour les tables de hachage...\n\n");

    fonctionClef_test();
    fonctionHachage_test();
    creer_livre_h_test();
    creer_biblio_h_test();
    recherche_par_num_h_test();
    recherche_par_titre_h_test();
    recherche_par_auteur_h_test();
    recherche_dupliques_h_test();
    inserer_h_test();
    fusion_biblio_h_test();
    suppression_ouvrage_h_test();
}

/*-------------------------------*/
    /* Éléments de hachage */
/*-------------------------------*/

void fonctionClef_test(){

    int test1 = fonctionClef("Castelao");
    assert(test1 == 812);

    printf("fonctionClef : OK\n");
    return; 
}

void fonctionHachage_test(){
    
    int test1 = fonctionHachage(12, 44);
    assert(test1 == 18);
    printf("fonctionHachage : OK\n");
    return;
}


/*-------------------------------*/
/* Initialisation de structures */
/*-------------------------------*/

void creer_livre_h_test(){

    LivreH* test1 = creer_livre_h(1, "LA_NUEVE", "MAIRIE_DE_PARIS");
    assert(test1 != NULL);
    liberer_livre_h(test1);
    /*
    Teste et fonctionnel, commente pour eviter les stderr
    LivreH* test2 = creer_livre_h(-1, "EL_NOMBRE_DEL_VIENTO", "Rothfuss");
    assert(test2 == NULL);

    LivreH* test3 = creer_livre_h(2, NULL, "VILLARES");
    assert(test3 == NULL);

    LivreH* test4 = creer_livre_h(3, "1984", "");
    assert(test4 == NULL);
    */
    printf("creer_livre_h : OK\n");
    return;
}

void creer_biblio_h_test(){
    /* TEST 1 */
    BiblioH* test1 = creer_biblio_h(99);
    assert(test1 != NULL);

    liberer_biblio_h(test1);

    printf("creer_biblio_h: OK\n");
    
    return;
}


/*-------------------------------*/
        /* Recherche */
/*-------------------------------*/

void recherche_par_num_h_test(){

    BiblioH* testBiblio = creer_biblio_h(100);
    inserer_h(testBiblio, 123, "DIXTIGSIE", "svey");
    inserer_h(testBiblio, 942, "MEDITERRANEA", "festa");

    /* TEST 1: Paramètres valides */
    LivreH* test1 = recherche_par_num_h(testBiblio, 123);
    assert(test1 != NULL);
    
    /* TEST 2: Paramètres invalides */
    /* Teste et OK, commente pour les stderr
    LivreH* test2 = recherche_par_num_h(testBiblio, -123);
    assert(!test2);
    */
    liberer_biblio_h(testBiblio);

    printf("recherche_par_num_h: OK\n");
    
    return;
}

void recherche_par_titre_h_test(){
    
    BiblioH* testBiblio = creer_biblio_h(100);
    inserer_h(testBiblio, 123, "DIXTIGSIE", "svey");

    /* TEST 1: Paramètres valides */
    LivreH* test1 = recherche_par_titre_h(testBiblio, "DIXTIGSIE");
    assert(test1 != NULL);
    
    /* TEST 2: Paramètres invalides */
    /*TESTE ET OK, COMMENTE POUR EVITER LE STDERR
    LivreH* test2 = recherche_par_titre_h(testBiblio, "ESTATUTO_XURIDICO_DA_LINGUA_GALEGA");
    assert(!test2);
    */
    liberer_biblio_h(testBiblio);

    printf("recherche_par_titre_h: OK\n");
    
    return;
}

void recherche_par_auteur_h_test(){

    BiblioH* testBiblio = creer_biblio_h(100);
    inserer_h(testBiblio, 123, "MENINAS", "svey");

    /* TEST 1: Paramètres valides */
    BiblioH* test1 = recherche_par_auteur_h(testBiblio, "svey");
    assert(test1 != NULL);
    liberer_biblio_h(test1);
    
    /* TEST 2: Paramètres invalides */
    /*
    Teste OK - Commente pour le stderr
    BiblioH* test2 = recherche_par_auteur_h(testBiblio, "PEÑARROJA_PAZ");
    assert(!test2);

    liberer_biblio_h(test2);
    */
    liberer_biblio_h(testBiblio);

    printf("recherche_par_auteur_h: OK\n");
    
    return;
}

void recherche_dupliques_h_test(){
    /* TEST 1: Paramètres valides */
    BiblioH* testBiblio = creer_biblio_h(100);
    inserer_h(testBiblio, 123, "LUSIADAS", "CAMOES");
    inserer_h(testBiblio, 321, "LUSIADAS", "CAMOES");

    LivreH* test1 = recherche_dupliques_h(testBiblio);
    assert(test1 != NULL);
    liberer_livre_h(test1);
    liberer_biblio_h(testBiblio);
    
    
    /* TEST 2: Paramètres invalides */
    /* Teste et OK et commente pour eviter les stderr
    BiblioH* biblio_vide = creer_biblio_h(100);
    LivreH* test2 = recherche_dupliques_h(biblio_vide);
    assert(!test2);
    liberer_biblio_h(biblio_vide); 
    */
    printf("recherche_dupliques_h: OK\n");
    
    return;
}


/*-------------------------------*/
  /* Manipulation de structures*/
/*-------------------------------*/

void inserer_h_test(){
    /* TEST 1: Inserer dans une bibliothèque valide avec des paramètres valides */
    BiblioH* biblio1 = creer_biblio_h(100);
    inserer_h(biblio1, 1123, "LUSIADAS", "CAMOES");
    assert(biblio1 != NULL);
    liberer_biblio_h(biblio1);

    // Le code commente est teste et OK, commente pour eviter le stderr
    
    /* TEST 2: Inserer avec un numéro négatif */
    /*
    BiblioH* biblio2 = creer_biblio_h(100);
    inserer_h(biblio2, -1, "RAYUELA", "CORTAZAR");
    assert(biblio2 != NULL && biblio2->nE == 0);
    liberer_biblio_h(biblio2);
    */
    /* TEST 3: Inserer avec un titre NULL */
    /*
    BiblioH* biblio3 = creer_biblio_h(100);
    inserer_h(biblio3, 1124, NULL, "CAMOES");
    assert(biblio3 != NULL && biblio3->nE == 0);
    liberer_biblio_h(biblio3);
    */

    printf("inserer_h : OK\n");
    return;
}

void fusion_biblio_h_test(){
    BiblioH* b1 = creer_biblio_h(100);
    BiblioH* b2 = creer_biblio_h(100);

    inserer_h(b1, 1, "LUSIADAS", "CAMOES");
    inserer_h(b2, 2, "ETRANGER", "CAMUS");

    BiblioH* merged = fusion_biblio_h(b1, b2);
    assert(merged == b1);
    assert(merged->T != NULL);

    BiblioH* b3 = creer_biblio_h(100);
    inserer_h(b3, 3, "Book3", "Author3");
    merged = fusion_biblio_h(NULL, b3);
    assert(merged == b3);

    liberer_biblio_h(b1);
    liberer_biblio_h(b3);

    printf("fusion_biblio_h : OK\n");
    return;
}

void suppression_ouvrage_h_test(){

    BiblioH* maBiblio = creer_biblio_h(100);
    inserer_h(maBiblio, 52, "COUSAS", "Castelao");
    inserer_h(maBiblio, 86, "CANTARES_GALEGOS", "Rosalia");
    inserer_h(maBiblio, 123, "SEMPRE_EN_GALIZA", "Castelao");
    
    assert(maBiblio->nE == 3);

    BiblioH* res = suppression_ouvrage_h(maBiblio, 52, "Castelao", "COUSAS");
    assert(res != NULL);
    assert(res->nE == 2);

    res = NULL;
    liberer_biblio_h(maBiblio);

    printf("suppression_ouvrage_h : OK\n");
    return;
}

