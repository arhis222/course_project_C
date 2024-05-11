#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>



int main() {
    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr");

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer("login 12214305 UNAY");
    envoyer("load tutoriel");

    printf ("Fin d'envoi des messages.\n");
    printf ("Pour envoyer d'autres lignes, ajouter des appels à la fonction `envoyer`\n");
    envoyer("-aide");
    envoyer("start");
    envoyer("oui");
    envoyer("4");
    envoyer("blanc");
    envoyer("Pincemoi");
    envoyer("tutoriel");

    deconnexion();
    printf ("Fin de la connection au serveur\n");
    return 0;
}
