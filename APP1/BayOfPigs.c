#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include "client.h"


void move_backwards(char* txt,int fois,int index); //faire les etapes de crypteMove inversement ce quìl compose les modifictaion sur txt
char* transform_backwards(char* txt);//former le txt depuis le debut
char* ajoute_debut(char* txt,char c);//ajoute le character c au debut du txt

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
    envoyer_recevoir("load BayOfPigs", reponse);

    printf ("Fin d'envoi des messages.\n");
    printf ("Pour envoyer d'autres lignes, ajouter des appels à la fonction `envoyer`\n");
    envoyer_recevoir("aide", reponse);
    envoyer_recevoir("start",reponse_aide);
    //envoyer(transform_backwards(reponse_aide)); // on prend le mot de passe et on decyrpte avec crypteMove je fais en local
    envoyer_recevoir("Par otuam eriet",reponse); // version crypte du mot de passe 'Patria o muerte'
    envoyer(transform_backwards(reponse)); // pour que je comprends le message crypte
    deconnexion();
    printf ("Fin de la connection au serveur\n");
    return 0;
}

char* transform_backwards(char* enc){
    int fois;

    int len = strlen(enc);
    char* txt = (char*)malloc(len + 1); //creer une memoire dynamique
    txt[0] = '\0'; // Initialise la première valeur avec '\0'
    for(int i=0;i<len;i++){ 
        txt = ajoute_debut(txt,enc[len-i-1]);//on ne change pas enc et on commence du prendre l'element du fin jusqu'au debut//on ajoute -1 car on veut faire changement en  dernier element
        fois = (int)txt[0]%8; // pour avoid d'avoir une erruer de caractere utf-8 on ajoute (int)
        if (i==len){
            move_backwards(txt,1,0);
        }
        else{// donc on ne veut pas faire des changements donc fois =0
            if (fois!=0){//on n'utilise pas la fonction si fois est 0 car on n'a pas besoin de changement
                move_backwards(txt,fois,1); //index default=1 car on prend le derneier element et ajoute apres le premier element ce qu'on a pris son modulo
            }
        //printf("character:%c\n",enc[i]); //testes
        //printf("fois:%d\n",fois);
        //printf("enc :%s\n",enc);
        //printf("txt :%s\n",txt);
        }   
    }
    txt[len] = '\0';  //pour corriger les erreurs avec le dernier casse qui est vide
    return txt;
}

void move_backwards(char* txt,int fois,int index){ //prend le fois*dernier element et ajoute a partir du index donne en parametre
    int len = strlen(txt);
    char txt_temp[MAXREP]="";
    
    txt_temp[0]=txt[0];//laisse le premier element dans txt_temp
    //printf("index:%d\n",index);
    if(fois<len){ //on ne peut pas changer le txt si son longuer et plus petite que element%8 car il n'y a pas d'assez element
        int j=fois;
        for(int i=index;i<index+fois;i++){   //ajoute les chracter ce qui sont a la fin au debut du texte a partir du index donne
            txt_temp[i]=txt[len-j];  //Nous voulons obtenir les derniers caractères de gauche à droite et on ajoute le txt_temp c'edt pourquioi on a len-j-1 et on diminue j
            j--;
            //printf("txt_temp:%s\n",txt_temp);
        }

        int x=index;//commence avec le deuxieme element du txt
        //printf("txt:%s\n",txt);
        //printf("index_x:%d\n",x);
        for(int k=index+fois;k<len;k++){ // ajoute les elements manquants dans l'intervalle [index+1+fois,len-fois]
            txt_temp[k]=txt[x];
            x++;
            //printf("txt_temp2:%s\n",txt_temp);
        }
    
        for(int y=0;txt_temp[y];y++){   //faire egaler le text a txt_temp au lieu de strcpy car on obtient une erreur
            txt[y]=txt_temp[y];  
        }
        if(fois!=0){
            txt[strlen(txt)]='\0'; //pour corriger les erreurs avec le dernier casse qui est vide
        //printf("txt1:%s\n",txt);
        }
    }
}

char* ajoute_debut(char* txt, char c) {
    int len = strlen(txt);
    char* newChar = (char*)malloc(len + 2); // +2 pour le nouveau caractère et le caractère nul

    if (newChar != NULL) {
        newChar[0] = c;
        strcpy(newChar + 1, txt); // Copie le texte original à partir de la position 1
        newChar[len + 1] = '\0'; // Assurez-vous que la nouvelle chaîne est correctement terminée
        return newChar;
    } else {
        fprintf(stderr, "Erreur d'allocation de mémoire.\n"); // Faute dans la mémoire dynamique
        exit(1);
    }
}


