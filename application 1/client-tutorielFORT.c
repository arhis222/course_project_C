#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

int main() {
    char reponse[MAXREP]; // à placer au début de la fonction 'main' car
                         // servira à stocker la réponse
    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr");

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer_recevoir("login 12214305 UNAY", reponse);
    envoyer_recevoir("load tutorielFORT", reponse);

    printf ("Fin d'envoi des messages.\n");
    printf ("Pour envoyer d'autres lignes, ajouter des appels à la fonction `envoyer`\n");
    envoyer_recevoir("depart", reponse);
    envoyer_recevoir("OK", reponse);
    envoyer_recevoir("OUI", reponse);
    
    for(int j = 0;j<6;j++){
        for (int i=0; reponse[i];i++){
            reponse[i]=toupper(reponse[i]);
        }
        envoyer_recevoir(reponse,reponse);
    }



    deconnexion();
    printf ("Fin de la connection au serveur\n");
    return 0;
}

