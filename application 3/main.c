#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listes.h"
#include "arbres.h"
#include "arbresphylo.h"
#include "table.h"

int DEBUG = 0;

int main(int argc, char* argv[])
{
    char *fichier = NULL;

    if (argc < 2) {
        fprintf (stderr, "Usage:  %s [-d] <fichier>\n", argv[0]);
        fprintf (stderr, "\n");
        fprintf (stderr, "Options:\n");
        fprintf (stderr, "\t-d\tmode debug\n");
        exit(1);
    }
    int arg=1;

    while (arg < argc) {
        if (!strncmp(argv[arg], "-d", 2)) {
            DEBUG = 1;
            arg++;
            continue;
        }
        if (argv[arg][0] == '-') {
            fprintf (stderr, "Option inconnue : '%s'\n", argv[arg]);
            exit(1);
        }
        if (fichier == NULL) {
            fichier = argv[arg];
            arg++;
            continue;
        }
        else {
            fprintf (stderr, "Trop de fichiers sur la ligne de commande : '%s'\n", argv[arg]);
            exit(1);
        }
    }

    debug ("Ouverture de %s\n", fichier);
    FILE* f = fopen (fichier, "r");
    if (!f) {
        fprintf (stderr, "Erreur à l'ouverture du fichier `%s'\n", fichier);
        perror (fichier);
        exit(1);
    }

    arbre mon_arbre = lire_arbre (f);
    affiche_arbre (mon_arbre,"arbre_avant.dot");//pour l'acte 1b

    int nombre_especes; /* Ne pas initialiser ici, c'est analyse_arbre */
    int nombre_caract;  /* qui doit s'en charger */

    /*Cette 2 ligne pour le bonus ents*/
    //FILE* ftest = fopen("ents", "w");
	//afficher_par_niveau(mon_arbre, ftest);

    analyse_arbre (mon_arbre, &nombre_especes, &nombre_caract);

    printf ("Nombre d'especes de l'arbre: %d\n", nombre_especes);
    printf ("Nombre de caractéristiques de l'arbre: %d\n", nombre_caract);

    affiche_arbre(mon_arbre, "arbre_apres.dot");//pour l'acte 1b
    
    //cette partie pour tester acte5
    /*
    int len_matrice;
    int len_liste;
    arbre arbre1;
    
    matrice_cell_t* matrice = creer_matrice(&len_matrice);
    char** list_esp = faire_list_esp(matrice,len_matrice,&len_liste);
    arbre1 = rec_matrice_to_arbre(list_esp,len_liste,matrice,len_matrice);
    */
    return 0;
}


