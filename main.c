#include <stdlib.h>
#include <stdio.h>
#define MAX 10
typedef struct RingBuffer
{
    int buffer[MAX];
    int tail;// from here we remove/dequee
    int head;// here we addd more elements
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
int entail(RingBuffer *b, int value)
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
int detail(RingBuffer *b)
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

int main(void)
{
    RingBuffer *buffer = init();

    for (int i = 0; i < 5; i++)
    {
        entail(buffer, i);
    }

    detail(buffer);
    detail(buffer);
    detail(buffer);
    detail(buffer);

    printf("\nHello, World! \n");
    return 0;
}
