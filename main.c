#include <stdlib.h>
#include <stdio.h>

#define MAX 10

// =================================================================================
// Probleme 1 : File implementee avec un tableau circulaire
// =================================================================================

typedef struct FileCirculaire
{
    int buffer[MAX];
    int queue; // La queue, d'ou on defile
    int tete;  // La tete, ou on enfile
    int taille;
} FileCirculaire;

FileCirculaire *initialiser_file()
{
    FileCirculaire *file = (FileCirculaire *)malloc(sizeof(FileCirculaire));
    if (!file)
    {
        printf("Impossible d'allouer de la memoire pour la file :(\nFermeture....\n");
        exit(EXIT_FAILURE);
    }
    file->queue = file->tete = file->taille = 0;
    return file;
}

int enfiler(FileCirculaire *f, int valeur)
{
    if (!f)
    {
        printf("La file n'est pas initialisee.\n");
        return 0;
    }
    if (f->taille == MAX)
    {
        printf("La file est pleine :(\n");
        return 0;
    }

    f->buffer[f->tete] = valeur;
    f->tete = (f->tete + 1) % MAX;
    f->taille++;
    printf("L'element %d a ete ajoute a la file.\n", valeur);
    return 1;
}

int defiler(FileCirculaire *f)
{
    if (!f)
    {
        printf("La file n'est pas initialisee.\n");
        exit(EXIT_FAILURE);
    }
    if (f->taille == 0)
    {
        printf("La file est vide :(\n");
        return -1; // Retourner une valeur d'erreur
    }

    int element = f->buffer[f->queue];
    f->queue = (f->queue + 1) % MAX;
    f->taille--;
    printf("L'element %d a ete retire de la file.\n", element);
    return element;
}

void afficher_file(FileCirculaire *f)
{
    if (!f)
    {
        printf("File non initialisee.\n");
        return;
    }
    if (f->taille == 0)
    {
        printf("La file est vide.\n");
        return;
    }
    printf("elements de la file : ");
    for (int i = 0; i < f->taille; i++)
    {
        int index = (f->queue + i) % MAX;
        printf("%d ", f->buffer[index]);
    }
    printf("\n");
}

// =================================================================================
// Probleme 2 : Deux piles dans un seul tableau
// =================================================================================

typedef struct DoublePile
{
    int tab[MAX];
    int sommet_g; // Sommet de la pile gauche
    int sommet_d; // Sommet de la pile droite
} DoublePile;

DoublePile *initialiser_dp()
{
    DoublePile *pile = (DoublePile *)malloc(sizeof(DoublePile));
    if (!pile)
    {
        printf("Allocation memoire impossible pour la double pile.\n");
        exit(EXIT_FAILURE);
    }
    pile->sommet_g = -1;
    pile->sommet_d = MAX;
    return pile;
}

int est_vide_d(DoublePile pile)
{
    return pile.sommet_d == MAX;
}

int est_vide_g(DoublePile pile)
{
    return pile.sommet_g == -1;
}

int est_pleine(DoublePile p)
{
    return p.sommet_g + 1 == p.sommet_d;
}

int empiler_d(DoublePile *pile, int valeur)
{
    if (est_pleine(*pile))
    {
        printf("\nLa double pile est pleine !\n");
        return 0;
    }
    pile->tab[--pile->sommet_d] = valeur;
    return 1;
}

int empiler_g(DoublePile *pile, int valeur)
{
    if (est_pleine(*pile))
    {
        printf("\nLa double pile est pleine !\n");
        return 0;
    }
    pile->tab[++pile->sommet_g] = valeur;
    return 1;
}

int depiler_d(DoublePile *pile)
{
    if (est_vide_d(*pile))
    {
        printf("La pile droite est vide !!\n");
        return -1; // Erreur
    }
    int element = pile->tab[pile->sommet_d++];
    return element;
}

int depiler_g(DoublePile *pile)
{
    if (est_vide_g(*pile))
    {
        printf("La pile gauche est vide !!\n");
        return -1; // Erreur
    }
    int element = pile->tab[pile->sommet_g--];
    return element;
}

void afficher_pile_gauche(DoublePile *p)
{

    if (est_vide_g(*p))
    {
        printf("la pile gauche est vide\n");
        return;
    }
    if (!est_vide_d(*p))
    {
        printf("\n you need the second stack to be empty \n");
        return;
    }

    printf("Elements de la pile gauche : ");

    while (!est_vide_g(*p))
    {
        int val = depiler_g(p);
        printf("%d ", val);
        empiler_d(p, val);
    }
    printf("\n");

    while (!est_vide_d(*p))
    {
        int val = depiler_d(p);
        empiler_g(p, val);
    }
}

// =================================================================================
// Probleme 3 : Liste implementee avec un tableau circulaire
// =================================================================================

typedef struct {
    int Tab[MAX];
    int tete;      // Index du premier element
    int nombre;    // Nombre d'elements dans la liste
} Liste;

// Creer une liste
Liste* Creer_Liste() {
    Liste* l = (Liste*)malloc(sizeof(Liste));
    if (!l) {
        printf("Erreur d'allocation memoire\n");
        exit(-1);
    }
    return l;
}

// Initialiser la liste
int Init_Liste(Liste* l) {
    if (!l) {
        printf("Liste n'existe pas\n");
        return((int)0);
    }
    l->tete = 0;
    l->nombre = 0;
    return((int)1);
}

// Verifier si la liste est vide
int Est_Vide_Liste(Liste l) {
    return((int)(l.nombre == 0));
}

// Verifier si la liste est pleine
int Est_Pleine_Liste(Liste l) {
    return((int)(l.nombre == MAX));
}

// Taille de la liste
int Taille_Liste(Liste l) {
    return((int)l.nombre);
}

// Inserer à la position i
int Inserer_Liste(Liste* l, int i, int valeur) {
    if (!l) {
        printf("Liste n'existe pas\n");
        return((int)0);
    }

    if (i < 0 || i > l->nombre) {
        printf("Position invalide\n");
        return((int)0);
    }

    if (Est_Pleine_Liste(*l)) {
        printf("Liste pleine\n");
        return((int)0);
    }

    // Cas 1: Insertion en tete
    if (i == 0) {
        l->tete = (l->tete - 1 + MAX) % MAX;
        l->Tab[l->tete] = valeur;
        l->nombre++;
        return((int)1);
    }

    // Cas 2: Insertion en queue
    if (i == l->nombre) {
        int pos = (l->tete + l->nombre) % MAX;
        l->Tab[pos] = valeur;
        l->nombre++;
        return((int)1);
    }

    // Cas 3: Insertion au milieu - decaler vers la droite
    int j;
    for (j = l->nombre - 1; j >= i; j--) {
        int pos_actuelle = (l->tete + j) % MAX;
        int pos_suivante = (l->tete + j + 1) % MAX;
        l->Tab[pos_suivante] = l->Tab[pos_actuelle];
    }

    int pos = (l->tete + i) % MAX;
    l->Tab[pos] = valeur;
    l->nombre++;
    return((int)1);
}

// Supprimer à la position i
int Supprimer_Liste(Liste* l, int i) {
    if (!l) {
        printf("Liste n'existe pas\n");
        return((int)0);
    }

    if (Est_Vide_Liste(*l)) {
        printf("Liste vide\n");
        return((int)0);
    }

    if (i < 0 || i >= l->nombre) {
        printf("Position invalide\n");
        return((int)0);
    }

    // Cas 1: Suppression en tete
    if (i == 0) {
        l->tete = (l->tete + 1) % MAX;
        l->nombre--;
        return((int)1);
    }

    // Cas 2: Suppression ailleurs - decaler vers la gauche
    int j;
    for (j = i; j < l->nombre - 1; j++) {
        int pos_actuelle = (l->tete + j) % MAX;
        int pos_suivante = (l->tete + j + 1) % MAX;
        l->Tab[pos_actuelle] = l->Tab[pos_suivante];
    }

    l->nombre--;
    return((int)1);
}

// Afficher la liste
void Afficher_Liste(Liste l) {
    if (Est_Vide_Liste(l)) {
        printf("Liste vide\n");
        return;
    }

    printf("\nContenu de la liste:\n");
    printf("[ ");

    int i;
    for (i = 0; i < l.nombre; i++) {
        int pos = (l.tete + i) % MAX;
        printf("%d ", l.Tab[pos]);
    }

    printf("]\n");
    printf("Tete=%d, Nombre=%d\n", l.tete, l.nombre);
}


// =================================================================================
// Demonstrations
// =================================================================================

void demonstration_file_circulaire()
{
    printf("\n--- Demonstration de la File Circulaire ---\n");
    FileCirculaire *file = initialiser_file();
    enfiler(file, 10);
    enfiler(file, 20);
    enfiler(file, 30);
    enfiler(file, 40);
    enfiler(file, 50);
    afficher_file(file);
    defiler(file);
    defiler(file);
    defiler(file);
    afficher_file(file);
    free(file);
    printf("--- Fin de la Demonstration ---\n");
}

void demonstration_double_pile()
{
    printf("\n--- Demonstration de la Double Pile ---\n");
    DoublePile *pile = initialiser_dp();

    //considrons que la pile gauche est la pile principale et la droite est vide/temporaire
    printf("\n*** Empiler des elements : 1,2,3,10\n");
    empiler_g(pile, 1);
    empiler_g(pile, 2);
    empiler_g(pile, 3);
    empiler_g(pile, 10);

    afficher_pile_gauche(pile);
    printf("\n*** Depiler des elements ***\n");
    depiler_g(pile);
    depiler_g(pile);
    afficher_pile_gauche(pile);

    free(pile);

    printf("--- Fin de la Demonstration ---\n");
}

void demonstration_liste_circulaire()
{
    printf("\n--- Demonstration de la Liste Circulaire ---\n");
    Liste* l = Creer_Liste();
    Init_Liste(l);

    printf("\n*** Insertion de 10, 20, 30 en queue ***\n");
    Inserer_Liste(l, 0, 10);
    Inserer_Liste(l, 1, 20);
    Inserer_Liste(l, 2, 30);
    Afficher_Liste(*l);

    printf("\n*** Insertion de 5 en tete (pos 0) ***\n");
    Inserer_Liste(l, 0, 5);
    Afficher_Liste(*l);

    printf("\n*** Insertion de 25 au milieu (pos 2) ***\n");
    Inserer_Liste(l, 2, 25);
    Afficher_Liste(*l);

    printf("\n*** Suppression en tete (pos 0) ***\n");
    Supprimer_Liste(l, 0);
    Afficher_Liste(*l);

    printf("\n*** Suppression au milieu (pos 1) ***\n");
    Supprimer_Liste(l, 1);
    Afficher_Liste(*l);

    free(l);
    printf("--- Fin de la Demonstration ---\n");
}

int main(void)
{
    demonstration_file_circulaire();
    demonstration_double_pile();
    demonstration_liste_circulaire();
    return 0;
}
