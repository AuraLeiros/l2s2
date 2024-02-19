/* Aura Leirós García - 21218034 */
/* aura.leiros@etu.sorbonne-universite.fr */
/* entreeSortieH.h - TP3 & TP4 SDD */

#ifndef ENTREESORTIEH_H
#define ENTREESORTIEH_H

/* Inserer n livres dans une bibliotèque depuis un fichier */
BiblioH* charger_n_entrees(char* nomfic, int m, int n);

/* Stocket une bibliotheque au bon format */
void enregistrer_biblio(BiblioH* b, char* nomfic);


#endif