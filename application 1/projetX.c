#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

char transform(char character);

int main() {
    char reponse[MAXREP]; // à placer au début de la fonction 'main' car
                         // servira à stocker la réponse
    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr");

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer_recevoir("login 12214305 UNAY", reponse);
    envoyer_recevoir("load projetX", reponse);

    printf ("Fin d'envoi des messages.\n");
    printf ("Pour envoyer d'autres lignes, ajouter des appels à la fonction `envoyer`\n");
    envoyer_recevoir("help", reponse);
    envoyer_recevoir("start", reponse);
    envoyer_recevoir("veni vidi vici", reponse);

    deconnexion();
    printf ("Fin de la connection au serveur\n");
    return 0;
}

char transform (char lettreLue)
        {
            char lettreSuivante5;
            
            //completer ici le calcul de la lettre suivante (3 rang plus loin)
            if (('a'<=lettreLue) && (lettreLue<='e')){
                lettreSuivante5=lettreLue+21;}
            else if (('e'<=lettreLue) && (lettreLue<='z')){
                lettreSuivante5=lettreLue-5;}
            else if ('A'<=lettreLue && lettreLue <= 'E'){
                lettreSuivante5=lettreLue+21;}
            else if ('F'<=lettreLue && lettreLue<='Z'){
                lettreSuivante5=lettreLue-5
                ;}
            else {
                lettreSuivante5 = lettreLue;
            }
            return lettreSuivante5;
        }
        