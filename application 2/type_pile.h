#define TAILLE_MAX 1000

typedef struct {
  int n;
  union {
    int entier;
    char* liste;
  } tab[TAILLE_MAX];
  int dernierType[TAILLE_MAX];
} PileEntiers;

/* Constructeurs */

/* Créer une pile vide */
void creer_pile(PileEntiers *p);

/* Opérations d'accès */
int dernierType(const PileEntiers *p);  // type de la dernier element qui se trouve au pile

/* Retourne vrai ssi p est vide */
int est_vide(PileEntiers *p);

/* Renvoie l'entier en haut de la pile */
/* p doit être non vide */
int sommet(PileEntiers *p);
char* sommet_liste(PileEntiers *p);

/* Renvoie le nombre d'éléments dans la pile */
int taille(PileEntiers *p);

/* Afficher les éléments de la pile */
void print(PileEntiers *p);

/* Opérations de modification */

/* Vider la pile p */
void vider(PileEntiers *p);

/* Empiler un entier x */
/* Précondition : taille(p) < TAILLE_MAX */
void empiler(PileEntiers *p, int x);
void empiler_liste(PileEntiers *p, const char* liste); //ekledim
/* Supprimer et renvoyer l'entier en haut de la pile */
/* Précondition : p non vide */
int depiler(PileEntiers *p);
char* depiler_liste(PileEntiers *p);
void rotate(PileEntiers *p, int n);
void mirroir(PileEntiers *p,PileEntiers *p1);
//void detruire_pile(PileEntiers *p);//pour liberer l'espace stocke par pile (specifiquement les groupe des commandes)
// void rotate_liste(PileEntiers *p, int n, int x);