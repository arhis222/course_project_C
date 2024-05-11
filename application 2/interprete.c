#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"
#include "curiosity.h"
#include "type_pile.h"
#include <stdint.h>

void stop(void) {
    char enter = '\0';
    printf("Appuyer sur entrée pour continuer...\n");
    while (enter != '\r' && enter != '\n') {
        enter = getchar();
    }
}

int interprete(sequence_t *seq, bool debug) {
    char commande;
    debug = true;

    printf("Programme:");
    afficher(seq);
    printf("\n");
    if (debug)
        stop();

    printf("\n>>>>>>>>>>> A Faire : interprete.c/interprete() <<<<<<<<<<<<<<<<\n");
    commande = seq->tete->command;
    cellule_t *cel = seq->tete; //
    cellule_t *cel_nouvel;// o(1) initialise cel_nouvel
    cellule_t *cel_nouvel2;// o(1) initialise cel_nouvel2
    int ret; // o(1) initialise ret
    int l1, l2, val;// o(1) initialise l1,l2,val
    PileEntiers p;// o(1) initialise p
    PileEntiers pz; //// o(1) initialise pz pour la commande 'z'
    //int nouvel_counter = 0;
    // liste1 ve liste2'yi tanımla
    char *liste1 = malloc(50); // Allocate memoire for liste1
    char *liste2 = malloc(50);// Allocate memoire for liste1

    creer_pile(&p);

    while (cel->suivant != NULL) {
        switch (commande) {
            case 'A':
                ret = avance();
                if (ret == VICTOIRE) {
                    free(liste1);// o(1)
                    free(liste2);// o(1)
                    remove_tous_elem_seq(seq);
                    //detruire_pile(p);
                    //detruire_pile(pz);
                    //detruire_seq(seq);
                    return VICTOIRE;
                }
                if (ret == RATE){
                    free(liste1);// o(1)
                    free(liste2);// o(1)
                    //detruireCellule(cel);
                    //detruireCellule(cel_nouvel);
                    //detruireCellule(cel_nouvel2);
                    //remove_tous_elem_seq(seq);
                    //detruire_seq(seq);
                    return RATE;
                }
                break;
            case 'G':
                gauche();
                break;
            case 'D':
                droite();
                break;
            case '+':
                l2 = depiler(&p);// o(1)je depile le sommet
                l1 = depiler(&p); // o(1)je depilee le sommet
                empiler(&p, l1 + l2);// o(1)je aditione le deux dernier sommet et j'empile a la pile
                break;
            case '-':
                l2 = depiler(&p);// o(1)je depile le sommet
                l1 = depiler(&p);// o(1)je depile le sommet
                empiler(&p, l1 - l2);// o(1)je soustrais le deux dernier sommet et j'empile a la pile
                break;
            case '*':
                l2 = depiler(&p);// o(1)je depile le sommet
                l1 = depiler(&p);// o(1)je depile le sommet
                empiler(&p, l1 * l2);// o(1)je multiplie le deux dernier sommet et j'empile a la pile
                break;
            case '0':
                empiler(&p, 0); // o(1) j'empile la valeur 0 a la pile
                break;
            case '1':
                empiler(&p, 1);// o(1) j'empile la valeur 1 a la pile
                break;
            case '2':
                empiler(&p, 2);// o(1) j'empile la valeur 2 a la pile
                break;
            case '3':
                empiler(&p, 3);// o(1) j'empile la valeur 3 a la pile
                break;
            case '4':
                empiler(&p, 4);// o(1) j'empile la valeur 4 a la pile
                break;
            case '5':
                empiler(&p, 5);// o(1) j'empile la valeur 5 a la pile
                break;
            case '6':
                empiler(&p, 6);// o(1) j'empile la valeur 6 a la pile
                break;
            case '7':
                empiler(&p, 7);// o(1) j'empile la valeur 7 a la pile
                break;
            case '8':
                empiler(&p, 8);// o(1) j'empile la valeur 8 a la pile
                break;
            case '9':
                empiler(&p, 9);// o(1) j'empile la valeur 9 a la pile
                break;
            case 'P':
                val = depiler(&p); //o(1) je depile la sommet pour pouvoir utiliser dans la fonction pose
                pose(val);
                break;
            case 'M':
                val = depiler(&p);//o(1) je depile la sommet pour pouvoir utiliser dans la fonction mesure
                l1 = mesure(val);
                empiler(&p, l1);// je empile la valeur que j'ai obtenu par la fonction mesure
                break;
            case '{': // si j'ai '{' je comprends qu'il y aura une groupe de commande 
                cel = cel->suivant;
                int nestedBraces = 1; // pour le cas ou on a une commande de groupe dans une commande de groupe
                char nestedCommand[30];
                int i = 0;

                while (nestedBraces > 0 && cel != NULL) { //on distinge les cas
                    if (cel->command == '{')
                        nestedBraces++;
                    else if (cel->command == '}')
                        nestedBraces--;

                    if (nestedBraces > 0) {
                        nestedCommand[i++] = cel->command;
                        cel = cel->suivant;
                    }
                }
                nestedCommand[i] = '\0';

                empiler_liste(&p, nestedCommand);
                break;
            case '?':
                strcpy(liste2, depiler_liste(&p));;//o(1) j'attrabue avec fonction depiler_liste
                strcpy(liste1, depiler_liste(&p));;//o(1) j'attrabue avec fonction depiler_liste
    
                val = depiler(&p);
                cel_nouvel = nouvelleCellule();
                cel_nouvel2 = nouvelleCellule();
                cel_nouvel2 = cel_nouvel;
                if (val == 0) {
                    
                    for (size_t i = 0; i < strlen(liste2); i++) {
                        cel_nouvel->command = liste2[i];
                        cel_nouvel->suivant = nouvelleCellule();
                        cel_nouvel = cel_nouvel->suivant;
                    }
                } 
                else {
                    
                    for (size_t i = 0; i < strlen(liste1); i++)
                    {
                        cel_nouvel->command = liste1[i];
                        cel_nouvel->suivant = nouvelleCellule();
                        cel_nouvel = cel_nouvel->suivant;
                    }
                }
                cel_nouvel->suivant = cel->suivant;
                cel->suivant = cel_nouvel2;
                break;
            case 'X':
                if (dernierType(&p) == 0) {//o(1) on regarde si premier sommet est une valeur
                    l1 = depiler(&p);//o(1) comme je sais que c'est une integer je prends sommet avec fonction depile
                    if (dernierType(&p) == 0) {// o(1)je regarde si deuxieme sommet est une integer
                        l2 = depiler(&p);//o(1)comme je sais que c'est integer j'atrabue la sommet avec depiler a l2
                        empiler(&p, l1);// o(1) j'empile les valeurs avec le sense inverse(ex:comme la sommet etatit liste 1 je l'empile premier fois pour que il soit en bas de l'autre valeur dans la pile)
                        empiler(&p, l2);//o(1)
                    } else {// comme ce n'est une valeur d'apres mon structure de pile c'est une liste
                        strcpy(liste2, depiler_liste(&p));//donc j'attrabue avec fonction depiler_liste
                        empiler(&p, l1);// o(1) j'empile les valeurs avec le sense inverse(ex:comme la sommet etatit liste 1 je l'empile premier fois pour que il soit en bas de l'autre valeur dans la pile)
                        empiler_liste(&p, liste2);//o(1) j'utilise empiler liste car je sait son type
                    }

                } else {// comme ce n'est une valeur d'apres mon structure de pile c'est une liste
                    strcpy(liste1, depiler_liste(&p));//donc j'attrabue avec fonction depiler_liste
                    if (dernierType(&p) == 0) {// je regarde si deuxieme sommet est une integer
                        l2 = depiler(&p);//o(1)comme je sais que c'est integer j'atrabue la sommet avec depiler a l2
                        empiler_liste(&p, liste1);// o(1) j'empile les valeurs avec le sense inverse(ex:comme la sommet etatit liste 1 je l'empile premier fois pour que il soit en bas de l'autre valeur dans la pile)
                        empiler(&p, l2);//o(1)
                    } else {// comme ce n'est une valeur d'apres mon structure de pile c'est une liste
                        strcpy(liste2, depiler_liste(&p));//donc j'attrabue avec fonction depiler_liste
                        empiler_liste(&p, liste1); // o(1) j'empile les valeurs avec le sense inverse(ex:comme la sommet etatit liste 1 je l'empile premier fois pour que il soit en bas de l'autre valeur dans la pile)
                        empiler_liste(&p, liste2);//o(1)
                    }
                }
                break;
            case '!':
                strcpy(liste1, depiler_liste(&p));//o(1) on atrbue cette valeur a la liste1
                cel_nouvel = nouvelleCellule();
                cel_nouvel2 = nouvelleCellule();
                cel_nouvel2 = cel_nouvel;// o(1)j'atrabue la cel_nouvel a cel_nouvel2 pour garder son position debut
                for (size_t i = 0; i < strlen(liste1); i++) {// o(n) pendant que i plus petite de la longeur de la liste je fait la suivant
                    cel_nouvel->command = liste1[i];//o(1) j'ajoute la commande qui se touve dans la liste[i] a la cel_nouvel->command 
                    cel_nouvel->suivant = nouvelleCellule();
                    cel_nouvel = cel_nouvel->suivant;//o(1) pour pouvoir ajouter les autre commande dans la boucle j'atribue la position de cel_nouvel->suivant a la cel_nouvel
                }
                cel_nouvel->suivant = cel->suivant;// o(1)j'atribue la position de cel_nouvel->suivant a la cel->suivant pour la reste
                cel->suivant = cel_nouvel2;// o(1)au debut j'avais cree cel_nouvel2 et j'avais attrabuer le cel_nouvel a ca pour  garder la position debut car je change la position de cel_nouvel dans la boucle
                break;
            case 'C': // comme c'est clone c'est assez de depiler la sommet et empiler deux fois le variable qu'on a depille
                if (dernierType(&p) == 0) //o(1) on regarde si somet est une valeur
                {
                    val = depiler(&p); // comme c'est une integer on utilise la fonction depiler depille la sommet qui est un integer et on atrabue a val
                    empiler(&p, val); //o(1)on empile cette valeur premier fois
                    empiler(&p, val); //o(1) on empile cette valeur deuxieme fois
                }
                else  // comme ce n'est une valeur d'apres mon structure de pile c'est une liste
                { 
                    strcpy(liste1, depiler_liste(&p));//o(1) on atrbue cette valeur a la liste1
                    empiler_liste(&p, liste1);//o(1)on empile cette liste premier fois
                    empiler_liste(&p, liste1);//o(1)on empile cette liste deuxieme fois
                }
                break;
            case 'B':
                val = depiler(&p); // o(1)je depile la somme qui  montre combien fois je vais entrer dans boucle
                strcpy(liste1, depiler_liste(&p)); //o(1) on atrbue cette valeur a la liste1
                if (val > 0) { // on regarde si la valeur est plus grande que 0
                    empiler_liste(&p, liste1);//o(1) on ajoute la liste en haute de la pile
                    val--;// o(1) on diminue la valeur
                    empiler(&p, val);//o(1) on ajoute la valeur en haute de la pile
                    cel_nouvel = nouvelleCellule();
                    cel_nouvel2 = nouvelleCellule();
                    cel_nouvel2 = cel_nouvel;// o(1)j'atrabue la cel_nouvel a cel_nouvel2 pour garder son position debut
                    for (size_t i = 0; i < strlen(liste1); i++) {// o(n) pendant que i plus petite de la longeur de la liste je fait la suivant
                        cel_nouvel->command = liste1[i]; //o(1) j'ajoute la commande qui se touve dans la liste[i] a la cel_nouvel->command 
                        cel_nouvel->suivant = nouvelleCellule();
                        cel_nouvel = cel_nouvel->suivant; //o(1) pour pouvoir ajouter les autre commande dans la boucle j'atribue la position de cel_nouvel->suivant a la cel_nouvel
                    }
                    cel_nouvel->command = 'B'; // o(1) j'ajoute la commande B a la cel_nouvel->commande pendant que val>0 avec la commande B ca va entrer dans la case B
                    cel_nouvel->suivant = cel->suivant;// o(1)j'atribue la position de cel_nouvel->suivant a la cel->suivant pour la reste
                    cel->suivant = cel_nouvel2;// o(1)au debut j'avais cree cel_nouvel2 et j'avais attrabuer le cel_nouvel a ca pour  garder la position debut car je change la position de cel_nouvel dans la boucle
                }
                break;
            case 'R': //o(n)
                l1 = depiler(&p); // on depile le valeur qui est x
                l2 = depiler(&p);// on depile le valeur qui est n

                while (l1 > 0) { //o(n)  pendant que n>0 je jais faire la fonction rotate (la fonction rotate se trouve dans pile.c) 
                    rotate(&p, l2);//o(1)
                    l1--; // o(1)je diminue le valeur n qui est l1 dans mon code
                }
                break;
            case 'I': // o(1)  Comme c'est ignore je dois deppiler le sommet est je fais rien c'est assez 
                if (dernierType(&p) == 0) { //on regarde si somet est une valeur
                    l2 = depiler(&p); // o(1)et on le depile 
                } else { // comme ce n'est une valeur d'apres mon structure de pile c'est une liste
                    strcpy(liste1, depiler_liste(&p)); // o(1)je depille le sommet qui est liste
                }
                break;
            case 'Z': //prendre le symetrique du pile par rapport a l'axe y
                creer_pile(&pz);
                mirroir(&p,&pz);
                p=pz; //change la pile actuel , il est desormais symetrique
                break;
            default:
                printf("Caractère inconnu: '%c'\n", commande);
    }

        

        cel = cel->suivant;
        seq->tete = cel;
        commande = cel->command;

        /* Affichage pour faciliter le debug */
        afficherCarte();
        printf("Programme:");
        afficher(seq);
        printf("\n");
        printf("pile :\n");
        print(&p);
        printf("\n");
        if (debug)
            stop();
    }

    /* Si on sort de la boucle sans arriver sur la cible,
    * c'est raté :-( */

   

    return CIBLERATEE;
}
