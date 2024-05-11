#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "type_pile.h"



/* Constructeurs */

/* Créer une pile vide */
void creer_pile(PileEntiers *p){//o(n)
    p->n = 0;//o(1) 

}

/* Opérations d'accès */
int dernierType(const PileEntiers *p) { // o(1) 
  return p->dernierType[p->n-1]; // o(1) renvoie la type d'ernier element
}

/* Retourne vrai ssi p est vide */
int est_vide(PileEntiers *p){ //o(1) renvoie si pile est donc je vontrole p->
    return (p->n == 0); //o(1)
}


/* p doit être non vide */
int sommet(PileEntiers *p){ //o(1)  Renvoie l'entier en haut de la pile 
    return (p->tab[p->n - 1].entier); //o(1)
}

char* sommet_liste(PileEntiers *p){//o(1) renvoie liste qui se trouve au sommet de la pile
    return (p->tab[p->n - 1].liste);// o(1)
}
/* Renvoie le nombre d'éléments dans la pile */
int taille(PileEntiers *p){// o(1) 
    return p->n;//o(1)
}

/* Afficher les éléments de la pile */   // sirasiyla bakilirken if else condition u eklenemek zorunda tab->liste ler de sorun verebilir 

void print(PileEntiers *p) {// o(n) pour afficher la contenu de la pile
for (int i = 0; i < p->n; i++) {// o(n)
    if (p->dernierType[i] == 0) {// o(1) je controle si c'est une liste 
      printf("%d\n", p->tab[i].entier);// o(1) si  alors j'utilise p->tab[i].entier
    }
    else if (p->dernierType[i] == 1) {// o(1) je controle si c'est une liste 
      printf("%s\n", p->tab[i].liste);// o(1) si  alors j'utilise p->tab[i].liste
    }
}
}
/* Opérations de modification */

/* Vider la pile p */
void vider(PileEntiers *p){//o(1) pour  vider la pile
    p->n = 0; // c'est assez de montrer que la taile de tab est 0

}

/* Empiler un entier x */
/* Précondition : taille(p) < TAILLE_MAX */
void empiler(PileEntiers *p, int x){
    if (p->n < TAILLE_MAX) {
        p->tab[p->n].entier = x; //o(1)
        p->dernierType[p->n] = 0; // o(1)ON a a ajoute une integer donc on mise a jour le type de dernier element 0 signifie integer
        p->n++;// o(1)j'augmente le n car il montre la taille de p et comme j'ai ajoute une integer.
        printf("%d ajoute en pile ",x); // pour debug
    } else {// si plus grande que taille max alors erreur
        printf( "Error: .\n"); // en cas d'erreur
    }
    
}
void empiler_liste(PileEntiers *p, const char* liste) { // o(1)une fonction pour ajouter une liste 
  if (p->n < TAILLE_MAX) {
    p->tab[p->n].liste = strdup(liste); // o(1)Utilise p->tab[p->n].liste au lieu de p->tab[p->n]->liste 
    p->dernierType[p->n] = 1;// o(1)ON a a ajoute une liste donc on mise a jour le type de dernier element 1 signifie la liste
    p->n++;  //o(1) j'augmente le n car il montre la taille de p et comme j'ai ajoute une liste.
  } else { // si plus grande que taille max alors erreur
    printf("ajoute en pile !\n");// o(1) en cas d'erreur
  }
}



/* Supprimer et renvoyer l'entier en haut de la pile */
/* Précondition : p non vide */
int depiler(PileEntiers *p){//o(1)
    if (est_vide(p)==0){// je controle si pile est vide
        p->dernierType[p->n - 1] = (p->tab[p->n - 1].liste != NULL) ? 1 : 0;  // o(1)change le type de dernier element
        int sommet1 = sommet(p);
        p->n = p->n-1;// o(1) comme j'ai depille je diminue la valeur de n
        return sommet1;
    }else{
        printf("pile est vide!!\n");
        p->dernierType[0] = -1; // si il y a pas element donc il n ' a pas son type aussi
        return 1;
    }
}
/* Supprimer et renvoyer liste en haut de la pile */
/* Précondition : p non vide */
char* depiler_liste(PileEntiers *p){//o(1)
    if (est_vide(p)==0){// je controle si pile est vide
        p->dernierType[p->n - 1] = (p->tab[p->n - 1].liste != NULL) ? 1 : 0;  // change le type de dernier element
        char* sommet1 = sommet_liste(p);// 
        p->n--;// o(1) comme j'ai depille je diminue la valeur de n
        return sommet1;
    }else{// donc il n 'y a pas une liste a depiler
        printf("pile est vide!!\n");
        p->dernierType[0] = -1; // si il y a pas element donc il n ' a pas son type aussi
        return NULL;
    }
}
/* Rotate the top n elements of the stack to the left by x positions */

void rotate(PileEntiers *p, int n) {// o(n) pour la case 'R' 
    if (n <= 0 || n > p->n) { // o(1) si y a erreur
        printf("Hata: Geçersiz rotate değeri.\n");
        return;
    }


    p->tab[p->n] = p->tab[p->n - n];//o(1)
      for (int i = p->n - n; i < p->n ;i++){// o(n)
        p->tab[i] = p->tab[i + 1]; // o(1)
    }
    for (int i = p->n - n; i < p->n ;i++){//o(n)
        p->dernierType[i] = p->dernierType[i + 1];//o(1)
    }
}


void mirroir(PileEntiers *p,PileEntiers *pz){// o(n)pour case Z je prend l'inverse miroire d'une pile 
    pz->n=p->n; // o(1)faire egaler les taille
    int n=p->n; //o(1) prendre la taille du pile
    int j=0;
    for(int i=n-1;i>=0;i--){ //o(n)ajoute tous les elements de gauche a droite au pile nouveau
        pz->tab[j] = p->tab[i];
        pz->dernierType[j] = p->dernierType[i];// o(1) j'atribue le type de i de p a i de pz
        j++;
    }
    p = pz;// o(1)j'atribue pz a p
}

//void detruire_pile(PileEntiers *p){} //pour liberer l'espace stocke par pile (specifiquement les groupe des commandes)//pour liberer l'espace stocke par pile (specifiquement les groupe des commandes)
