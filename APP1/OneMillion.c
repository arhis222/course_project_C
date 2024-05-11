#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>


void Pig(char* ENC,char *TXT){
    
    int longeur_enc = strlen(ENC);
    int longeur_txt, decale;

    for (int i = 0; i < longeur_enc; i++){
        longeur_txt = strlen(TXT);

        if (longeur_txt>0){
            memmove(TXT + 1, TXT, longeur_txt + 1);
            TXT[0] = ' '; 
        }
        longeur_txt = strlen(TXT);
        TXT[longeur_txt] = '\0';
        

        decale= ENC[longeur_enc-(i+1)]%8;

        if (longeur_txt > decale){
            
            
            memmove(&TXT[0], &TXT[1], longeur_txt - 1);

            TXT[longeur_txt - 1] = '\0';

            for (int k = 0; k < decale; k++){
                longeur_txt = strlen(TXT);
                if (longeur_txt > 0) {
                    memmove(TXT + 1, TXT, longeur_txt);

                    TXT[0] = TXT[longeur_txt];
                    TXT[longeur_txt] = '\0';

                }

            }
            memmove(TXT + 1, TXT, longeur_txt + 1);
            TXT[0] = ' ';
        }
        TXT[0] = ENC[longeur_enc - i-1];

    }
    
    TXT[0] = ENC[0];
    
}


int main() {
    char reponse[MAXREP];
    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(true);
    envoyer_recevoir("message à envoyer au serveur", reponse);
    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr");
    envoyer_recevoir("login 12214574 TURKMEN",reponse);
    envoyer_recevoir("load OneMillion", reponse);
  
    
    envoyer_recevoir("aide", reponse);
    char genel[10000*100+1];
    for (int i = 0; i < 999; i++){
        strcat(genel, reponse);
    }
    char mesaj[1000000];
    char cevap[101];
    envoyer_recevoir("start", reponse);
    strcat(genel, reponse);
    printf("genelin uzunluğu:%lu\n", strlen(genel));

    Pig(genel, mesaj);

    strncpy(cevap, mesaj, 100);
    cevap[100] = '\0';
    
    envoyer_recevoir(cevap, reponse);
}