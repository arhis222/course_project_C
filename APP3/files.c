#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "files.h"
#include "arbres.h"



/* Constructeurs */

/* Créer une fille vide */
void creer_file(file_attente *f){
    if(f==NULL){
        f = (file_attente*)(sizeof(file_attente));
    }
    f->tete=NULL;
    f->queue=NULL;
}


/*detruire une file attente ca vet dire tout les cellules*/
void detruire_file(file_attente *f){
    if(f==NULL){
        return;
    }
    // Pointer vers le début de la liste
    cell_file_t* courant = f->tete;

    while (courant != NULL) {
        cell_file_t* suivant = courant->suivant;  // Sauvegarder le pointeur vers le prochain élément
        free(courant->val);  // Libérer la mémoire allouée pour la valeur 
        free(courant);  // Libérer la mémoire allouée pour la cellule
        courant = suivant;  // Déplacer le pointeur courant vers le prochain élément
    }

    f->tete = NULL;
    f->queue =NULL;

    //free(L);
}

/* Retourne vrai ssi f est vide */
bool est_vide(file_attente *f){
    return f->tete == NULL;
}   



/* Emfiler un arbre  */
/* Précondition : taille(f) < TAILLE_MAX */
void emfiler(file_attente *f, arbre a){ //ajoute en fin du fille attente

    cell_file_t* nouvel_cell=NULL; //on initialise une nouvelle cellule pour ajouter a file attente
    nouvel_cell=(cell_file_t*)malloc(sizeof(cell_file_t));

    nouvel_cell->val = a;
    nouvel_cell->suivant = NULL;

    if(f->tete==NULL){ //if f tete est vide
        f->tete=nouvel_cell; //ajoute la cellule au debut et en fin du fille attente
        f->queue=nouvel_cell;
    }
    //si non
    else{
        f->queue->suivant=nouvel_cell;
        f->queue=nouvel_cell;
    }
}

/* Supprimer et renvoyer dernier element du file */
/* Précondition : f non vide */
arbre defiler(file_attente *f){
    assert (f);
    cell_file_t* cell = f->tete;
    if(cell!=NULL){
        f->tete = cell->suivant;
    }
    return cell->val;
}

