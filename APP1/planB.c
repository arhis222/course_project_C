#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
//arhan unay
char* transform(char* lettrelue);

int main() {
    char reponse[MAXREP]; // à placer au début de la fonction 'main' car
                         // servira à stocker la réponse
    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr");

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer_recevoir("login 12214305 UNAY", reponse);
    envoyer_recevoir("load planB", reponse);

    printf ("Fin d'envoi des messages.\n");
    printf ("Pour envoyer d'autres lignes, ajouter des appels à la fonction `envoyer`\n");
    envoyer_recevoir("aide", reponse);
    envoyer("start");
    
    envoyer_recevoir(transform(reponse), reponse);
    
    



    deconnexion();
    printf ("Fin de la connection au serveur\n");
    return 0;
}

char* transform(char* lettrelue){
    char* texte = strdup("hasta la revolucion");
    int decalage=0;
    while(lettrelue[0]!='C' ){
        if (lettrelue[0] == 'Z'){
        lettrelue[0]='A';}

        else{
            lettrelue[0]++;}
        decalage++;

    }
    decalage = decalage%26;

    for(int i=0;texte[i];i++){
        if ('a'<=texte[i] && texte[i]<='z'){
                texte[i]=('a'+(texte[i]-'a'+decalage)%26);
        }
        else if ('A'<=texte[i] && texte[i] <='Z'){
                texte[i]=('A'+(texte[i]-'A'+decalage)%26);
        }

        else {
                    texte[i] = texte[i];
                }
        
    }
    return texte;
}
