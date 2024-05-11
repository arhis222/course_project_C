#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include "client.h"


void detransform_message(char* input);//creer le txt selon l'input en utilisant les autres fonctions
int est_dans_seq(char* seq,char c);//controlle la seq si il contient le character c ou pas et il return son index si'il existe  sinon -1
void changer_seq(char* seq,int index,char c); //ajout le character c a la fin du seq si l'index est -1 (si c'est la premiere fois) si non deplace a la fin du seq mais on faire ca avec l'element apres le C dans seq


int main() {
    char reponse[MAXREP];
    char mot_de_passe[MAXREP]; //Pour prendre le mot de passe d'apres le reponse
     // à placer au début de la fonction 'main' car
    // servira à stocker la réponse
    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr");

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer_recevoir("login 12214305 UNAY", reponse);
    envoyer_recevoir("load Northwoods", reponse);

    printf ("Fin d'envoi des messages.\n");
    printf ("Pour envoyer d'autres lignes, ajouter des appels à la fonction `envoyer`\n");
    envoyer_recevoir("start",reponse);
    envoyer_recevoir("hasta la victoria siempre",reponse); // le mot de passe a la fin du crypteSeq
    detransform_message(reponse); //on decrypte la reponse actuel
    int j = 0;//pour mettre les valeurs a j commencant par debut
    for(int i=(int)(strlen(reponse)-29);i<(int)(strlen(reponse)-9);i++){ //c'est le intervalle qui correspond la place du mot du passe dans le reponse
        mot_de_passe[j] = reponse[i];
        j++;
    }
    envoyer_recevoir(mot_de_passe,reponse); // pour que je comprends le message crypte
    //detransform_message(reponse2); //on decrypte la reponse actuel
    char reponse2[]="Therh wiliebrlnoeNwebtntioENgTNy-FbuT";//version crypte de mot de pas avec crypteSeq 
    envoyer_recevoir(reponse2,reponse);//envoyer le mot de passe
    envoyer("yes");//surpris pour sera sur qu'on a reussi le exo
    deconnexion();
    printf ("Fin de la connection au serveur\n");
    return 0;
}

void detransform_message(char* input){
    char c;
    int index;//on utilise pour les fonctions changer_seq pour comprendre il existe (dans ce cas avec son index) ou pas (-1) dans la fonction est_dans_seq
    int len = strlen(input);
    char txt[MAXREP]="";
    //char* txt = (char*)malloc(len + 1); //creer une memoire dynamique car (on retorune ca)
    char seq [MAXREP]=""; //initialise
    //txt[0] = '\0'; // Initialisez la première valeur avec '\0'
    //seq[0]= '\0'; // Initialisez la première valeur avec premier c du input
    for(int i=0;i<len;i++){ 
        c = input[i];
        index = est_dans_seq(seq,c);
        if(index==-1){ //char c n'est pas dans la seq (premier fois)
            changer_seq(seq,index,c); //faire le changemnent necessaire dans seq
            txt[i]=c;//ajoute a la fin du txt
        }
        else{ //char c est deja dans la seq
            if(index==(int)(strlen(seq)-1)){
                txt[i]=seq[0];//si index est la dernier element donc on va prendre le premier element(apres le fin du list on retorune a index 0)   txt[i]=seq[0];
            }
            else{
                txt[i]=seq[index+1]; //prendre l'element apres l'index (le caractere apres le C)  txt[i]=seq[index+1];
            }
            changer_seq(seq,index,c); //faire le changemnent necessaire dans seq
        }
    } 
    txt[len] = '\0';  //pour corriger les erreurs avec le dernier casse qui est vide
    strcpy(input,txt);//tarnsfere le contenu du txt vers input

}

void changer_seq(char* seq,int index,char c){
    int len = strlen(seq);
    char seq_temp[MAXREP]=""; //on va faire les changement dans une seq temporarire et a la fin on copy a seq actuel
    if(index==-1){ //char c n'existe pas encore dans seq donc ajout a la fin
        seq[len]=c;//ajoute une element c a la fin
    }
    else{
    if(index== (int)(strlen(seq) - 1)){  //si index est la dernier element donc on va prendre le premier element(apres le fin du list on retorune a index 0) 
        index=0;
    }
    else{
        index=index+1; //prendre l'element apres l'index (le caractere apres le C)
    }
    //on veut prendre l'element apres le c dans seq pour faire l'inverse du crypteSeq dans mon algo
    
    for(int i=0;i<index;i++){  //Addition normale jusqu'à ce que l'index donné soit atteint
        seq_temp[i]=seq[i];  //Nous voulons obtenir les derniers caractères de gauche à droite et on ajoute le txt_temp c'edt pourquioi on a len-j-1 et on diminue j
    }
    for(int j=index;j<len-1;j++){ //ajouter les elements manquant apres l'index
        seq_temp[j]=seq[j+1]; //passer l'element a index donne
    }        
    seq_temp[strlen(seq_temp)] = seq[index];  //ajoute l'element a index a la fin
    }

    for(int y=0;seq_temp[y];y++){   //faire egaler le seq a seq_temp au lieu de strcpy car on obtient une erreur
        seq[y]=seq_temp[y];  
    }
    
    //seq[strlen(seq)]='\0'; //pour corriger les erreurs avec le dernier casse qui est vide}
}


int est_dans_seq(char* seq,char c){
    int len = strlen(seq);
    for(int i=0;i<len;i++){  //controlle si char c existe ou pas.si oui return son index
        if(c==seq[i]){
            return i;
        }
    }
    return -1;  //si non -1
}
