#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "table.h"
#include "arbres.h"


/*une fonction pour creer une cellule de matrice avec le characteristique et nom espece donne en argument*/
matrice_cell_t nouvel_cell_matrice(char* carac, char* esp) {
    matrice_cell_t cell; //nouvelle cell
    cell.caractere = strdup(carac); //mettre le characteristique dans la cell
    cell.espece = strdup(esp); //mettre l'espece dans la cell
    return cell;
}

/*Une fonction pour Libèrer la mémoire des cellules de la matrice*/
void liberer_matrice_cell(matrice_cell_t* cellules, int nombre_cell) {
    for (int i = 0; i < nombre_cell; i++) {
        free(cellules[i].caractere);
        free(cellules[i].espece);
    }
}

/* fonction de print pour tester le matrice*/
void print_matrice(matrice_cell_t* matrice[], int nombre_cell) {
    for (int i = 0; i < nombre_cell; i++) {
        printf("%s\t%s\n", matrice[i]->caractere, matrice[i]->espece);
    }
}


/*fonction pour creer une matrice selon le tableau.Il pose une nom du caracteristique et apres il pose les noms d'espece ayant cette caracteristique et les ajouter dans la matrice*/
matrice_cell_t* creer_matrice(int* len_matrice) {
    char caractere[MAX_NOM_CARACTERE];
    char espece[MAX_NOMBRE_ESPECE][MAX_NOM_ESPECE];
    int nombre_esp=0;
    int i = 0;
    *len_matrice = 0;
    // Création de la matrice
    matrice_cell_t* matrice = (matrice_cell_t*)malloc(nombre_esp * sizeof(matrice_cell_t));

    printf("Veuillez entrer un nom de caractere (- pour finir) : ");
    scanf("%s", caractere);

    while (caractere[0] != '-') { // on repete jusqu'on a - pour le caracter

        printf("Veuillez entrer le nombre d'espece ayant cette caractere: ");
        scanf("%d", &nombre_esp);

        printf("Veuillez entrer les noms d'especes ayant cette caractere (ecrire et press enter pour chacun et faire attention au nombre qu'on a declare avant):\n");
        
        // Continue tant que l'utilisateur n'entre pas '-' pour les especes
        
        while (i < nombre_esp) {
            scanf("%s", espece[i]);
            if (strcmp(espece[i], "-") == 0) {
                break;
            }
            matrice[i] = nouvel_cell_matrice(caractere, espece[i]);// remplir la matrice
            i++;
            (*len_matrice)++;
        }

        

        //on commence maintenant de remplir la matrice
        //for (int j = 0; j < i; ++j) {
            //matrice[j] = nouvel_cell_matrice(caractere, espece[j]);
        //}

        // Affichage de la matrice
        printf("\nMatrice :\n");
        print_matrice(&matrice, i);
 
        //liberer_matrice_cell(matrice, i); // Libeation de la mémoire

        printf("Veuillez entrer un nom de caractere (- pour finir) : ");
        scanf("%s", caractere);
    }
    
    printf("Veuillez entrer les noms d'especes qui n'a pas de caracteristique(ecrire et press enter pour chacun et - pour finir):\n");
    strcpy(caractere,"-"); //comme on n'a pas une caracteristique pours ces especes on a une cractere null(-) pour matrice
    while (strcmp(espece[i], "-") == 0) {
            scanf("%s", espece[i]);
            matrice[i] = nouvel_cell_matrice(caractere, espece[i]);// remplir la matrice
            i++;
            (*len_matrice)++;
        }

    


    return matrice;
}

//creer_esp_liste

/*retourner true si espece est dans la liste false si non*/
bool est_dans_la_liste_matrice(char* espece,char* liste[]){
    for(int i=0;liste[i];i++){
        if(strcmp(espece,liste[i])==0){
            return true;

        }
    }
    return false;
}

char** faire_list_esp(matrice_cell_t* matrice,int len_matrice,int* len_liste){
    char** list_esp = malloc(sizeof(char*)*1000);
    char* espece;
    int b=0;

    for(int a=0;a<len_matrice;a++){
        espece = matrice[a].espece;
        if(!est_dans_la_liste_matrice(espece,list_esp)){
            list_esp[b]=espece;
            b++;
        }
    }
    list_esp[b]=NULL;
    (*len_liste )= b;
    return list_esp;
}

max_valeur_list_car_t trouve_max_caracter(char* list_esp[],matrice_cell_t* matrice,int len_matrice){
    char* list_car[1000];
    char* caractere;
    int b=0;
    for(int a=0;a<len_matrice;a++){
        caractere = matrice[a].caractere;
        if(!est_dans_la_liste_matrice(caractere,list_car)){
            list_car[b]=caractere;
            b++;
        }
    }
    list_car[b]=NULL;

    int list_number[b];
    int j=0;
    for(int i = 0; list_esp[i]; i++){
        list_number[j]=0;
        for(int k = 0; k<len_matrice; k++){
            if(strcmp(matrice[k].espece,list_esp[k])==0)
            list_number[j]++;
        }
        j++;
    }
    
    int max_car_index =list_number[0];
    int max_car_index2 =list_number[0];
    for(int i = 0; list_car[i]; i++){
        if(list_number[i]>max_car_index){
            max_car_index2=max_car_index;
            max_car_index=list_number[i];
        }
        
    }
    max_valeur_list_car_t return_value ;
    return_value.max1 = strdup(list_car[max_car_index]);
    return_value.max2 = strdup(list_car[max_car_index2]);


    return return_value;
}

// Fonction pour ajouter un noeud à l'arbre
arbre rec_matrice_to_arbre(char* list_esp[],int len_liste,matrice_cell_t* matrice,int len_matrice){
    if(len_liste == 1){ // si la liste contient une seul element on ajoute direcetement comme il reste une espece
        noeud* racine = nouveau_noeud();
        racine->valeur =strdup(list_esp[0]);
        return racine;
    }

    
    max_valeur_list_car_t max_valeurs = trouve_max_caracter(list_esp,matrice,len_matrice);
    char* max_caracter1 = strdup(max_valeurs.max1);
    char* max_caracter2 = strdup(max_valeurs.max2);
    char* list1[len_liste];
    char* list2[len_liste];
    int i_list1=0;
    int i_list2=0;

    for(int i = 0; i < len_matrice; i++){
        matrice_cell_t current = matrice[i];
        if(strcmp(current.caractere,max_caracter2)==0){
            list1[i_list1]=current.espece;
            i_list1++;

        }
    }
    list1[i_list1]=NULL;

    for(int i = 0; list_esp[i]; i++){
        bool verifier_esp=false;
        for(int j=0; list1[j]; j++){
            if(strcmp(list1[j],list_esp[i])==0){
                verifier_esp=true;
                break;
            }
        }
        if (!verifier_esp){
            list2[i_list2]=list_esp[i];
            i_list2++;
        }

    }

    list2[i_list2]=NULL;
    
    noeud* racine = nouveau_noeud();
    racine->valeur=max_caracter1;

    racine->droit = rec_matrice_to_arbre(list1,i_list1,matrice,len_matrice);
    racine->gauche = rec_matrice_to_arbre(list2,i_list2,matrice,len_matrice);

    return racine;
}

/*

arbre matrice_to_arbre(arbre* racine, matrice_cell_t cell_data) {
    if ((*racine) == NULL ) { //on controlle si arbre est vide ou pas
      (*racine) = nouveau_noeud();  //creer une nouvelle noeud
    }
    racine = rec_matrice_to_arbre()

    
    // Comparer les caractères ou d'autres critères pour déterminer où ajouter le nouveau nœud
    
}
*/




