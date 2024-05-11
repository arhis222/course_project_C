#include <stdlib.h>
#include <stdio.h>

#define MAX_NOMBRE_ESPECE 100
#define MAX_NOM_ESPECE 20
#define MAX_NOM_CARACTERE 20

#include "arbres.h"

/*je pense que utiliser une matrice est plus approprié pour la table de correspondance*/
/*une cellule de matrice la nom du charateristique et la nom d'un espece qui a ce trait ("oui" dans la table)*/
struct matrice_cell {
    char* caractere; 
    char* espece;
};

struct max_valeur_list_car{
    char* max1;
    char* max2;
};

typedef struct matrice_cell matrice_cell_t;
typedef struct max_valeur_list_car max_valeur_list_car_t;

/*une fonction pour creer une cellule de matrice avec le characteristique et nom espece donne en argument*/
matrice_cell_t nouvel_cell_matrice(char* carac, char* esp);

/*fonction pour creer une matrice selon le tableau.Il pose une nom du caracteristique et apres il pose les noms d'espece ayant cette caracteristique et les ajouter dans la matrice*/
matrice_cell_t* creer_matrice(int* len_matrice);

/*Une fonction pour Libèrer la mémoire des cellules de la matrice*/
void liberer_matrice_cell(matrice_cell_t* cellules, int nombre_cell);

/* fonction de print pour tester le matrice*/
void print_matrice(matrice_cell_t* matrice[], int nombre_cell);


/*retourner true si espece est dans la liste false si non*/
bool est_dans_la_liste_matrice(char* espece,char* liste[]);

char** faire_list_esp(matrice_cell_t* matrice,int len_matrice,int* len_liste);

max_valeur_list_car_t trouve_max_caracter(char* list_esp[],matrice_cell_t* matrice,int len_matrice);

/*fonction pour creer une matrice selon le tableau.Il pose une nom du caracteristique et apres il pose les noms d'espece ayant cette caracteristique et les ajouter dans la matrice*/
arbre rec_matrice_to_arbre(char* list_esp[],int len_liste,matrice_cell_t* matrice,int len_matrice);


