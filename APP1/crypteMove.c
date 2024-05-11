#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include "client.h"
#include <stdbool.h>


void move(char* txt,int fois,int index);
char* transform(char* txt);


int main() {
    char reponse[MAXREP];
    char reponse_aide[MAXREP]; // à placer au début de la fonction 'main' car
    // servira à stocker la réponse
    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr");

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer_recevoir("login 12214305 UNAY", reponse);
    envoyer_recevoir("load crypteMove", reponse);

    printf ("Fin d'envoi des messages.\n");
    printf ("Pour envoyer d'autres lignes, ajouter des appels à la fonction `envoyer`\n");
    envoyer_recevoir("aide", reponse_aide);
    envoyer_recevoir("start",reponse);
    envoyer(transform(reponse_aide));

    deconnexion();
    printf ("Fin de la connection au serveur\n");
    return 0;
}

char* transform(char* txt){  //on change le enc ici on utilise la fonction move pour ch
    int fois;
    int len = strlen(txt);
    char* enc = (char*)malloc(len + 1); //creer une memoire dynamique
    
    for(int i=0;i<len;i++){
        enc[i]=txt[0];    //on prend le premier element du txt chaque fois et on ajoute a enc
        fois = (int)enc[i]%8;  //prend le modulo du premier element // pour avoid d'avoir une erruer de caractere utf-8 on ajoute (int)
        
        if (fois==0){ //si ca reste 0 il ne prend pas d'element donc on change le valeur 0 a 1
            fois = 1; //cas de modulo =0 donc on prend seulemnt 1 element
            move(txt,fois,0);
        }
        
        else {
            move(txt,fois,1); //pour demarrer la fonction avec la caractere premier apres le remove
        }
        //printf("character:%c\n",enc[i]); //testes
        //printf("fois:%d\n",fois);
        //printf("enc :%s\n",enc);
        //printf("txt :%s\n",txt);

        

    }   
    enc[len] = '\0';  //pour corriger les erreurs avec le dernier casse
    return enc;
    
}

void move(char* txt,int fois,int index){ //on change le txt ici ce qui compris prend le debut et ajoute a la fin.
    int len = strlen(txt);
    char txt_temp[MAXREP]="";
    int j=0;
    //printf("index:%d\n",index);
    for(int i=index+fois;i<=len;i++){   //ajoute  character par character le texte apres le modulo du 8 sans ajoutant le debut
        txt_temp[j]=txt[i];
        j++;
        //printf("txt_temp:%s\n",txt_temp);
    }
    
    if (fois!=0){  //si fois =0 on n'ajoute rien a la fin
        int x=index;
        //printf("txt:%s\n",txt);
        //printf("index_x:%d\n",x);
        len = strlen(txt_temp);
        for(int k=len;k<len+fois;k++){ // ajoute le debut du pharase apres le texte
            
            txt_temp[k]=txt[x];
            x++;
            //printf("txt_temp2:%s\n",txt_temp);
        }
    }
    
    for(int y=0;txt_temp[y];y++){   //faire egaler le text a temp (comme strcpy)
        txt[y]=txt_temp[y];  
    }
    txt[strlen(txt)-1]='\0'; // Pour éviter que le dernier élément soit pressé deux fois
    //printf("txt1:%s\n",txt);
}

