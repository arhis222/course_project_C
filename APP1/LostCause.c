#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#define MAXREP 1000
//ARHAN UNAY

char* transform_message(char* input);//creer le txt selon l'input en utilisant les autres fonctions
int est_dans_seq(char* seq,char c);//controlle la seq si il contient le character c ou pas et il return son index si'il existe  sinon -1
void changer_seq(char* seq,int index,char c); //ajout le character c a la fin du seq si l'index est -1 (si c'est la premiere fois) si non deplace a la fin du seq



int main() {


    char txt[]="abcbcca";
    printf("%s",transform_message(txt));
}



char* transform_message(char* input){
    char c;
    int index;//on utilise pour les fonctions changer_seq pour comprendre il existe (dans ce cas avec son index) ou pas (-1) dans la fonction est_dans_seq
    int index2;//on utilise pour le seq2  dans l'algo
    int len = strlen(input); 
    char* txt = (char*)malloc(len + 1); //creer une memoire dynamique
    char seq[MAXREP]=""; //creer une memoire dynamique
    char seq2[MAXREP]=""; //contient associations des chaque character pour le seq donne
    for(int i=0;i<len;i++){ 
        c = input[i];
        index = est_dans_seq(seq,c);
        if(index==-1){ //char c n'est pas dans la seq (premier fois)
            changer_seq(seq2,index,c);//faire changer les associations
            changer_seq(seq,index,c); //faire le changemnent necessaire dans seq
            txt[i]=c;//ajoute a la fin du txt
        }
        else{ //char c est deja dans la seq
            if(index!=0){ //prendre l'element a index -1 (le caractere qui precede C)
                txt[i]=seq2[index-1];//il doit prendre dans seq2 selon algo car on asscoie chaque char avec son association
            }
            else{//si index est 0 ca veut dire premier element du seq donc on va prendre l'element a la fin du seq
                txt[i]=seq2[strlen(seq2)-1]; //prendre le dernier element du seq2
            }
            if(index!=0){ //prendre element precedent pour seq2
                index2=index-1;
            }
            else{
                index2=strlen(seq2)-1; //0 est premier element donc pour le element precedent on va prendre le dernier element comme index
            }
            changer_seq(seq2,index2,c);//faire le changemnent necessaire dans seq2
            changer_seq(seq,index,c); //faire le changemnent necessaire dans seq
        }
    }   
    txt[len] = '\0';  //pour corriger les erreurs avec le dernier casse qui est vide
    return txt;
}

void changer_seq(char* seq,int index,char c){
    int len = strlen(seq);
    char seq_temp[MAXREP]=""; //on va faire les changement dans une seq temporarire et a la fin on copy a seq actuel
    if(index==-1){ //char c n'existe pas encore dans seq donc ajout a la fin
        seq[len]=c;//ajoute une element c a la fin
    }
    else{
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
    
    seq[strlen(seq)]='\0'; //pour corriger les erreurs avec le dernier casse qui est vide}
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

