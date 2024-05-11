#ifndef _FILES_H
#define _FILES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "arbres.h"

#define TAILLE_MAX 100

struct cell_file {
	arbre val;
	struct cell_file* suivant;
};

typedef struct cell_file cell_file_t;

struct seq_file {
	cell_file_t *tete;
	cell_file_t *queue;
};

typedef struct seq_file file_attente;

/* Constructeurs */

/* Créer une fille vide */
void creer_file(file_attente *f);

/*detruire une file attente ca vet dire tout les cellules*/
void detruire_file(file_attente *f);

/* Retourne vrai ssi f est vide */
bool est_vide(file_attente *f);

/* Opérations de modification */

/* Emfiler un arbre  */
/* Précondition : taille(f) < TAILLE_MAX */
void emfiler(file_attente *f, arbre );

/* Supprimer et renvoyer dernier element du file */
/* Précondition : f non vide */
arbre defiler(file_attente *f);

#endif