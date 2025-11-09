#include <stdlib.h>
#include <stdio.h>
#define MAX 10
typedef struct RingBuffer
{
    int buffer[MAX];
    int tail; // from here we remove/dequee
    int head; // here we addd more elements
    int size;
} RingBuffer;

RingBuffer *init()
{
    RingBuffer *buffer = (RingBuffer *)malloc(sizeof(RingBuffer));
    if (!buffer)
    {
        printf("cant allocate memeroy to the buffer :( \n closing ....");
        exit(EXIT_FAILURE);
    }

    buffer->tail = buffer->head = buffer->size = 0;

    return buffer;
}
int enqueue(RingBuffer *b, int value)
{
    if (!b)
    {
        printf("buffer not initialised");
        return 0;
    }
    if (b->size == MAX)
    {
        printf("buffer is full :( ");
        return 0;
    }

    b->buffer[b->head] = value;
    b->head = (++b->head) % MAX;
    b->size++;
    printf(" %d has been added\n", value);
    return 1;
}
// returns the removed element
int dequeue(RingBuffer *b)
{
    if (!b)
    {
        printf("tails is undefind");
        exit(EXIT_FAILURE);
    }

    if (b->size == 0)
    {
        printf("head is empty :( ");
        return 0;
    }

    int element = b->buffer[b->tail];
    b->tail = (++b->tail) % MAX;
    b->size--;
    printf(" %d is removed \n", element);
    return element;
}

void afficher(RingBuffer *b)
{
    if (!b)
    {
        printf("Buffer not initialized\n");
        return;
    }
    if (b->size == 0)
    {
        printf("Buffer is empty\n");
        return;
    }
    printf("Buffer elements : ");
    for (int i = 0; i < b->size; i++)
    {
        int ind = (b->tail + i) % MAX;
        printf("%d ", b->buffer[ind]);
    }
    printf("\n");
}

typedef struct pile_double
{
    int tab[MAX];
    int tete_g; // tete gauche
    int tete_d; // tete droit
} pile_double;

pile_double *init_pd()
{
    pile_double *pile = (pile_double *)malloc(sizeof(pile_double));
    pile->tete_g = -1;
    pile->tete_d = MAX;
    return pile;
}

int est_vide_d(pile_double pile)
{
    return (int)(pile.tete_d == MAX);
}

int est_vide_g(pile_double pile)
{
    return (int)(pile.tete_g == -1);
}

int est_Plain(pile_double p)
{
    return p.tete_g + 1 == p.tete_d;
}

int push_d(pile_double *pile, int valeur)
{
    if (est_Plain(*pile))
    {
        printf("\nla pile est plain ! \n");
        return 0;
    }

    pile->tab[--pile->tete_d] = valeur;
    return 1;
}

int push_g(pile_double *pile, int valeur)
{
    if (est_Plain(*pile))
    {
        printf("\nla pile est plain ! \n");
        return 0;
    }

    pile->tab[++pile->tete_g] = valeur;
    return 1;
}

int pop_d(pile_double *pile)
{
    if (est_vide_d(*pile))
    {
        printf("la pile droite est vide !!");
        return 0;
    }

    int element;
    element = pile->tab[pile->tete_d++];
    return element;
}

int pop_g(pile_double *pile)
{
    if (est_vide_g(*pile))
    {
        printf("la pile droite est vide !!");
        return 0;
    }

    int element;
    element = pile->tab[pile->tete_g--];
    return element;
}
int main(void)
{

    pile_double *pile = init_pd();

    for (int i = 32; i < 36; i++)
    {
        push_g(pile, i);
    }
    for (int i = 4; i < 8; i++)
    {
        push_d(pile, i);
    }

    pop_d(pile);
    pop_d(pile);

    pop_g(pile);

    push_d(pile, 89);
    push_d(pile, 89);
    push_d(pile, 89);

    push_g(pile, 12);
    push_g(pile, 12);
    push_g(pile, 12);
    push_g(pile, 12);

    // RingBuffer *buffer = init();

    // afficher(buffer);
    // for (int i = 0; i < 5; i++)
    // {
    //     enqueue(buffer, i);
    // }
    // dequeue(buffer);
    // dequeue(buffer);
    // dequeue(buffer);
    // dequeue(buffer);
    // afficher(buffer);

    // printf("\nHello, World! \n");
    return 0;
}
