/* Aura Leirós García - 21218034 */
/* aura.leiros@etu.sorbonne-universite.fr */
/* entreeSortieLC.h - TP3 & TP4 SDD */

#ifndef ENTREESORTIELCH
#define ENTREESORTIELCH

#include "biblioLC.h"


/* Inserer n livres dans une bibliotèque depuis un fichier */
Biblio* charger_n_entrees_lc(char* nomfic, int n);

/* Stocket une bibliotheque au bon format */
void enregistrer_biblio_lc(Biblio* b, char* nomfic);

#endif

