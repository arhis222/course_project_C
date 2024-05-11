#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "listes.h"

/* fichier à compléter au besoin */

void init_liste_vide(liste_t* L) {
    //printf ("<<<<< À faire: fonction init_liste_vide fichier " __FILE__ "\n >>>>>");
    /* a completer */
    if(L==NULL){ //on controlle d'abord si il est intiialise avant ou pas
    
        L = (liste_t*)malloc(sizeof(liste_t));
    }
    L->tete = NULL;
}


void liberer_liste(liste_t* L) {
    //printf("<<<<< À faire: fonction liberer_liste fichier " __FILE__ "\n >>>>>");

    // Pointer vers le début de la liste
    cellule_t* courant = L->tete;

    while (courant != NULL) {
        cellule_t* suivant = courant->suivant;  // Sauvegarder le pointeur vers le prochain élément
        free(courant->val);  // Libérer la mémoire allouée pour la valeur 
        free(courant);  // Libérer la mémoire allouée pour la cellule
        courant = suivant;  // Déplacer le pointeur courant vers le prochain élément
    }

    L->tete = NULL;

    //free(L);
}


int ajouter_tete(liste_t* L, const char* c) { /* retourne 0 si OK, 1 sinon  */
   /* a completer */
    cellule_t *tmp = L->tete;
    L->tete = (cellule_t *)malloc(sizeof(cellule_t));
    if (L->tete == NULL) {
        //fprintf(stderr, "Erreur d'allocation mémoire\n"); //si necessaire on peut afficher une message d'erreur
        return 1; 
    }
    L->tete->val = strdup(c);
    L->tete->suivant = tmp;
    return 0; // Return 0 for success
}

void afficher (liste_t* seq){
    assert (seq); /* Le pointeur doit être valide */ //on break le code si faux
    /* À compléter */
    cellule_t *cel=seq->tete;
    while (cel != NULL) {
        printf(" %s ", cel->val);
        cel = cel->suivant;
    }
    //detruireCellule(cel); // si on ne l'utilise pas  apres la fonction afficher on doit liberer la memoire
}

//retourne la longueur d'une sequence
int nombre_element_liste(cellule_t* seq){
    int longueur = 0;
    cellule_t *current = seq;

    //jusqu'a la fin du seq
    while (current != NULL) {
        longueur++;
        current = current->suivant;
    }

    return longueur;
}

//retourner true si espece dans la seq false si non
bool controlle_seq(cellule_t* seq, char* nom_espece){ 
    while (seq != NULL) { //controlle jusqu'a fin
        if (strcmp(seq->val, nom_espece) == 0) {
            return true;
        }
        seq = seq->suivant;
    }
    return false;
}
