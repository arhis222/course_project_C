#ifndef ARBRES_H
#define ARBRES_H

#include <stdbool.h>
#include "listes.h"

/* Structure d'un noeud d'arbre */
struct noeud_s;
typedef struct noeud_s noeud;

/* Un arbre binaire est défini comme une référence vers le noeud racine de l'arbre.
 * Un arbre binaire vide est représenté par une référence NULL.
 * Un arbre binaire est une structure de données récursive.
 * Si il n'est pas vide, ses fils sont des arbres.
 */
typedef noeud* arbre;

struct noeud_s {
    char* valeur;
    arbre gauche;
    arbre droit;
};


/* Crée un nouveau nœud et initialise ses champs à null */
noeud* nouveau_noeud (void);

/* Construit un arbre depuis le fichier ouvert f.
 * Fonction récursive (s'appelle elle-même pour la lecture des fils
 * gauche et droit).
 */
arbre lire_arbre (FILE *f);

void rec_visiter(arbre, FILE *f);

int nombre_fils(arbre); //pour calculer le nombre de fils de la noeud donne


/* Fonction d'affichage, à remplir */
void affiche_arbre(arbre,char nom_fichier[]);

/*return true si noeud est une feuille*/
bool est_feuille(noeud* n);

/*faire controller  si les elements dans la sequence forme une sous arbre */
bool controlle_arbre(arbre a, cellule_t* seq, int* size_seq);

/*verifier  que les espece dans la seq forme une sous arbre ou pas*/
bool est_sous_arbre(arbre a, const cellule_t* seq);

/*creer l'arbre selon la table de correspondance*/
void creer_par_table(FILE *f);

/* Macros pour de l'affichage uniquement si DEBUG est != 0 */
extern int DEBUG;

#define debug(fmt, ...) \
            do { if (DEBUG) fprintf(stderr, fmt, ##__VA_ARGS__); } while (0)

#endif
