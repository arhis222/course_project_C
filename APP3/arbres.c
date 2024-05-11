#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "arbres.h"
#include "listes.h"

noeud* nouveau_noeud(void)
{
    noeud *n = (noeud*)malloc(sizeof(noeud));
    assert (n!=NULL);
    n->valeur = NULL;
    n->gauche = NULL;
    n->droit  = NULL;
    return n;
}


/* buffer pour lire les caractères des espèces sous forme de "mots" (words) */
#define MAX_WORD_SIZE 255
char buffer[MAX_WORD_SIZE+1];

/* Variable globale qui contient le prochain caractère à traiter */
static char next_char = ' ';

/* Supprime tous les espaces, tabulations, retour à la ligne */
#define GLOB(f) \
    while(isspace(next_char)) { \
        next_char = fgetc(f);\
    }


/* Fonction récursive qui lit un sous-arbre */
/* Appelée une fois à la racine (debut du fichier), puis récursivement
 * pour chaque nœud interne rencontré. */
arbre lire_arbre (FILE *f)
{
    arbre racine;

    GLOB(f); /* lit dans next_char le premier caractère non vide */

    if (next_char == '/') {
        next_char = ' '; /* on ne garde pas '/' en mémoire */
        return NULL;
    }

    if (next_char == ')') {
        return NULL;
    }

    if (next_char != '(') {
        fprintf(stderr, "Error while reading binary tree : '(' or ')' expected at position %ld\n", ftell(f));
        exit (1);
    }

    /* On remplit le buffer tant qu'on lit des caractères alphanumériques */
    char *p = buffer; /* début du buffer */
    next_char = ' '; GLOB(f);

    do {
        *p = next_char;       /* sauvegarde du char courant */
        next_char = fgetc(f);
        p++;
        assert (p < buffer + MAX_WORD_SIZE);
    } while (! isspace (next_char) && next_char != '(' && next_char != ')');
    /* on arrète si le char suivant est un espace ou une parenthèse */
    *p='\0'; /* on ferme la chaîne de caractères dans le buffer */

    racine = nouveau_noeud();
    racine->valeur = strdup(buffer); /* dupliquer le mot lu */

    GLOB(f);

    if (next_char == ')') {
        next_char = ' '; /* on est sur une feuille, on prépare la lecture du prochain nœud */
    }
    else {
        racine->gauche = lire_arbre (f); /* appel récursif pour le fils gauche */
        racine->droit  = lire_arbre (f); /* idem pour le droit */

        GLOB(f); /* lit jusqu'au ')' fermant */

        if (next_char != ')') {
            fprintf(stderr, "Error while reading binary tree: ')' expected\n");
            exit(1);
        }
        next_char = ' '; /* on ne garde pas la parenthèse en mémoire */
    }
    return racine;
}

void rec_visiter(noeud *racine, FILE *f){ //on affiche premierment arbre gauche apres arbre droite comme parcours en profondeur
    if(racine==NULL){
        return ; //pour sortir de la fonction a la fin
    }
    if(racine->gauche!=NULL){ //on commence avec le cas non comme dans la consigne
        fprintf(f,"%s -> %s [label = \"non\"]\n",racine->valeur, racine->gauche->valeur);
        rec_visiter(racine->gauche, f); // reappeler la fonction pour continuer
    }
    if(racine->droit!=NULL){ //le cas oui
        fprintf(f,"%s -> %s [label = \"oui\"]\n",racine->valeur, racine->droit->valeur);
        rec_visiter(racine->droit, f); // reappeler la fonction pour continuer
    }
}

int nombre_fils(arbre noeud){ //pour calculer le nombre de fils de la noeud donne (seulement 1 niveau)
    int nombre = 0;
    if(noeud==NULL){
        return 0;
    }
    if(noeud->droit!=NULL){
        nombre++;
    }
    if(noeud->gauche!=NULL){
        nombre++;
    }
    return nombre;
}

void affiche_arbre (noeud *racine,char nom_arbre[]) //on a ajoute une nom du fichier pour afficher l'arbre acte1b
{
    //printf ("<<<<< À faire: fonction affiche_arbre fichier " __FILE__ " >>>>>\n");
    /* à remplir */
    FILE *f;
    f=fopen(nom_arbre, "w");
    char nom[100];
    int k=0;
    while(nom_arbre[k]!='.'){//on prend le nom du arbre et on enleve la partie ".dot"
        nom[k]=nom_arbre[k];
        k++;
    }
    fprintf(f,"digraph %s {\n", nom); //selon le consigne que vous avez donne

    rec_visiter(racine, f); // on fait une parcours en profondeur 

    fprintf(f,"}\n");

    fclose(f);
}

/*return true si noeud est une feuille*/
bool est_feuille(noeud* n){
    return (n->droit == NULL && n->gauche ==NULL); // si arbre gauche et droite est vide il est feuille
}

/*faire controller  si les elements dans la sequence forme une sous arbre */
bool controlle_arbre_rec(arbre a, const cellule_t* seq, int* nombre_elem) {
    bool controlle_gauche; //pour controller arbre gauche
    bool controlle_droite; //pour controller arbre droite
    if (a == NULL) {
        return (*nombre_elem) == 0; // si arbre est fini on compare notre nombre d'elem avec 0 car on diminue cet nombre chaque fois qu'on a trouve une espece dans la seq
    }

    if(!est_feuille(a)) { // si ce n'esp pas une espece on continue a cherhcer a la noeud droite et a gauche
        controlle_droite = controlle_arbre_rec(a->droit, seq, nombre_elem); // comme une parcours prof
        controlle_gauche = controlle_arbre_rec(a->gauche, seq, nombre_elem);
        
        return (controlle_gauche && controlle_droite);
    }
    else{ //si c'est une espece on compare avec les especes dans la seq
        if (controlle_seq((cellule_t*)seq, a->valeur)) {
            (*nombre_elem)--; // si l'espece dans la seq on diminue le nombre d'element qu'on cherche
            return true;
        }
    } 
    
    return false;
}

/*verifier  que les espece dans la seq forme une sous arbre ou pas*/
bool est_sous_arbre(arbre a, const cellule_t* seq) {
    int nombre_elem = nombre_element_liste((cellule_t*)seq); //on prend le nombre d'espece qu'on cherche
    return controlle_arbre_rec(a, seq, &nombre_elem) && nombre_elem == 0; //on utilise la fonction recursuve en haut
}

/*ACTE V*/

void creer_par_table(FILE *f){
    
}