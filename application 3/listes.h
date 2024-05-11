#ifndef _LISTES_H
#define _LISTES_H

#include <stdbool.h>

typedef struct liste liste_t;
/* Type de liste à compléter selon votre besoin. */

typedef char* string;

struct cellule {
	string val;
	struct cellule* suivant;
};

typedef struct cellule cellule_t;

struct liste {
	cellule_t *tete;
};

typedef struct liste liste_t;

/* cree une nouvelle liste, initialement vide */
void init_liste_vide(liste_t* L);

/* libère toutes les cellules de la liste */
void liberer_liste(liste_t *L);

/* Ajouter une nouvelle cellule contenant c
 * en tête de la liste L.
 * Si l'ajout est réussi, le résultat est 0,
 * et 1 sinon (échec de l'ajout)
 */
int ajouter_tete(liste_t *L,const char* c);

void afficher (liste_t* seq);

/*retourne la longueur d'une sequence*/
int nombre_element_liste(cellule_t* seq);

/*retourner true si espece dans la seq false si non*/
bool controlle_seq(cellule_t* seq, char* nom_espece);



#endif /* _LISTES_H */


