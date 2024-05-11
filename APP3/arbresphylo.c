#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "arbres.h"
#include "listes.h"
#include "arbresphylo.h"


/*ACTE I*/
void analyse_arbre (arbre racine, int* nb_esp, int* nb_carac)
{  
   //printf ("<<<<< À faire: fonction analyse_arbre fichier " __FILE__ "\n >>>>>");
   
   static int counter_carac=0; //on utilise les variables static pour ne pas initialiser a chaque appel
   static int counter_esp=0;

   if(racine!=NULL){
      
      if (racine->gauche==NULL && racine->droit==NULL ){
         counter_esp++;
      }
      if(racine->gauche!=NULL){
         analyse_arbre(racine->gauche,nb_esp,nb_carac);
      }
      if(racine->droit!=NULL){
         analyse_arbre(racine->droit,nb_esp,nb_carac);
      }
      if(racine->gauche!=NULL || racine->droit!=NULL){
         counter_carac++;
      }
   }
     
   *nb_esp=counter_esp;
   *nb_carac=counter_carac;
   
}

/*Si on veut implementer 2 autres fonctions supplementaires pour acte1 et les utilisent dans l'arbre*/
/*int nombre_espece(arbre racine){
   if(racine==NULL){
      return 0;
   }
   else if(racine->droit==NULL && racine->gauche==NULL){
      return 1;
   }
   else{
      return nombre_espece(racine->gauche) + nombre_espece(racine->droit);
   }
}

int nombre_carac(arbre racine){
   if(racine==NULL){
      return 0;
   }
   else if(racine->droit==NULL && racine->gauche==NULL){
      return 0;
   }
   else{
      return 1+nombre_carac(racine->gauche) + nombre_carac(racine->droit);
   }
}

void analyse_arbre(arbre racine, int* nb_esp, int* nb_carac)
{
   *nb_esp = nombre_espece(racine);
   *nb_carac = nombre_carac(racine);
}
*/






/* ACTE II */
/* Recherche l'espece dans l'arbre. Modifie la liste passée en paramètre pour y mettre les
 * caractéristiques. Retourne 0 si l'espèce a été retrouvée, 1 sinon.
 */
int rechercher_espece(arbre racine, char *espece, liste_t *seq){
   //printf ("<<<<< À faire: fonction rechercher_espece " __FILE__ "\n >>>>>");

   if (racine == NULL) { //on controlle d'abord si arbre est vide ou on atteint la fin
        return 1;
   }
   if (strcmp(racine->valeur, espece) == 0) { // comparer les chaînes de caractères avec strcmp si il est egale au nom du espece
      return 0;
   }

   if (rechercher_espece(racine->gauche, espece, seq) == 0) { // recherche dans le sous-arbre gauche
      //ajouter_tete(seq, racine->valeur);
      return 0;
   }

   if (rechercher_espece(racine->droit, espece, seq) == 0) { // recherche dans le sous-arbre droit
      ajouter_tete(seq, racine->valeur); //ajouter la seq si il est dans l'arbre droite ca veut dire caracteristique oui
      return 0; 
   }

   return 1; // si l'espèce n'est pas trouvée dans cet arbre
}


/* ACTE III */
/* Doit renvoyer 0 si l'espece a bien ete ajoutee, 1 sinon, et ecrire un 
 * message d'erreur.
 */
int ajouter_espece (arbre* a, char *espece, cellule_t* seq) {
   if ((*a) == NULL ) { //on controlle si arbre est vide ou pas
      (*a) = nouveau_noeud();  //creer une nouvelle noeud
      //(*a)->valeur = strdup(espece); 
      if(seq==NULL){ //si seq est vide
         (*a)->valeur=strdup(espece); //on ajoute directement l'Espece
         return 0; 
      }
      else{ //si non
         (*a)->valeur=strdup(seq->val); //on ajoute les caracteristiques 
         return ajouter_espece(&(*a)->droit,espece,seq->suivant);
      }
   }  
   else if(((*a)->droit == NULL && (*a)->gauche ==NULL)){ // si arbre est une feuille
      if(seq==NULL){ //si seq est vide on a 2 possibilite si espece est cette feuille ou un autre espece est cette feuille
         if (strcmp(espece,(*a)->valeur)!=0){// on controlle si espece est cette feuille ou pas
            printf("Ne peut ajouter <%s>: possède les mêmes caractères que <%s>.\n", espece, (*a)->valeur);
            return 1;
         }
         else{ // cette espece deja present dans l'arbre
            printf("Ne peut pas ajouter <%s>: car espece deja present dans l'arbre", espece);
            return 1;
         }
      }
      else{
         noeud* fille = nouveau_noeud();//on cree une nouveau noeud pour deplacer l'espece qui se trouve en haut(feuille) à la nouvelle arbre se qu'on va creer avec le caracteristiques premier dans la seq.
         fille->valeur = strdup((*a)->valeur);
         (*a)->valeur = strdup(seq->val); //on ajoute le caracterisqiues
         (*a)->gauche = fille; // on lie l'Espece present a arbre gauche comme il n'a pas ce caracteristiques
         return ajouter_espece(&(*a)->droit,espece,seq->suivant);
      }
   }
   else{ //les autres possibilites (arbres qui contient des caracteristiques)
      if(seq==NULL){ //si seq est vide  donc on n'a pas cette caracteristiques associe a l'espece
         return ajouter_espece(&(*a)->gauche,espece,seq); 
      }
      else{
         if(strcmp((*a)->valeur, seq->val)!=0){ //on controlle si l'Espece possede le caracteristique du sequence
            ajouter_espece(&(*a)->gauche,espece,seq);//on n'a pas cette caracteristique
         }
         else{
            return ajouter_espece(&(*a)->droit,espece,seq->suivant); //on a cette caracteristique

         }
      }
   }
   return 0;
}

/* Doit afficher la liste des caractéristiques niveau par niveau, de gauche
 * à droite, dans le fichier fout.
 * Appeler la fonction avec fout=stdin pour afficher sur la sortie standard.
 */
void afficher_par_niveau (arbre racine, FILE* fout) {
   //printf ("<<<<< À faire: fonction afficher_par_niveau fichier " __FILE__ "\n >>>>>");
   if(racine==NULL)return;

   file_attente file;
   arbre noeud;
   /*les 3 lignes sont pour sauter le niveau suivante*/
   int pas = 0; //pour afficher niveau par niveau on doit controller si on atteint son nombre de fils lorsqu'on affiche
   int nombre_de_fils = 0;  //pour afficher niveau par niveau on doit controller si on atteint son nombre de fils lorsqu'on affiche
   int nombre_de_fils_suiv = 0; 

   creer_file(&file);
   emfiler(&file, racine);
   while(!est_vide(&file)) {
      noeud = defiler(&file);
      
      if(noeud->droit != NULL  || noeud->gauche !=NULL){ // si il n'est pas une feuilleil est une caracteristique
         fprintf(fout,"%s ",noeud->valeur);
         nombre_de_fils_suiv += nombre_fils(noeud);//on calcule le nombre de fils
         //printf("%s ", noeud->valeur); //pour afficher en terminal
      }
      
      pas++; //car on a deja passe une noeud
      
      if(pas>=nombre_de_fils){   //on controlle si on atteint le nombre de fils pour sauter autre niveau
         fprintf(fout,"\n");
         nombre_de_fils = nombre_de_fils_suiv;
         nombre_de_fils_suiv = 0; //on reset les valeurs
         pas = 0; //on reset les valeurs
         //printf("\n");  //pour afficher en terminal

      }

      /* parcourir en largeur */
      if(noeud->gauche!=NULL) { //comme dans la parcours en largeur on regarde d'abord le gauche
         emfiler(&file, noeud->gauche); //ajouter a la fin du fille attente
      }

      if(noeud->droit!=NULL){ //apres la droite
        emfiler(&file, noeud->droit); //ajouter a la fin du fille attente
      }
   }

   detruire_file(&file);//liberer l'Espace memoire du file
}


/*Acte IV*/

// on considère qu'il n'est pas possible
// d'insérer une caractéristique à un arbre vide, ni d'insérer une caractéristique
// qui n'est possédée par aucune espèce déjà présente dans l'arbre (pour ce
// cas-là, ajout_espece fait l'affaire). Ceci permet d'éviter d'avoir à ajouter
// des noeuds caractéristique sans enfant qui seraient confondues avec des
// espèces/feuilles.

int ajouter_carac(arbre* a, char* carac, cellule_t* seq) {
   int nombre_elem = nombre_element_liste(seq);
   if (nombre_elem <= 0 || *a == NULL) { // si arbre est null  ou seq est vide on ne peut pas ajouter
      printf("Ne peut ajouter <%s>: ne forme pas un sous-arbre ou l'arbre est NULL.\n", carac);
      return 0;
   }

   if (est_sous_arbre(*a, seq)) { //si les especes forment une sous arbre dans la noeud qu'on est on peut ajouter la caracter
      noeud* nouveau_noeudd = nouveau_noeud(); // on a besoin une nouvelle noueud pour ajouter la caracter
      nouveau_noeudd->valeur = carac;
      nouveau_noeudd->droit = *a; //comme le caractere est oui on met le fleche a droite (a l'arbre precedent)
      *a = nouveau_noeudd; //on change maintenant l'arbre actuel
      return 1;
   }
   //si les especes ne forme pas encore une ss arbre dans la noeud actuel on continue a chercher dans les autres noeud
   if (!est_feuille(*a) && (ajouter_carac(&((*a)->gauche), carac, seq) || ajouter_carac(&((*a)->droit), carac, seq))) {
      return 1;
   }
   //les autres cas (si non)
   //printf("Ne peut ajouter <%s>: ne forme pas un sous-arbre.\n", carac);
   return 0;
   
}


