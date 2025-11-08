#include <stdlib.h>
#include <stdio.h>
#define MAX 10
typedef struct RingBuffer
{
    int buffer[MAX];
    int head;
    int queue;
} RingBuffer;

RingBuffer *init()
{
    RingBuffer *buffer = (RingBuffer *)malloc(sizeof(RingBuffer));
    if (!buffer)
    {
        printf("cant allocate memeroy to the buffer :( \n closing ....");
        exit(EXIT_FAILURE);
    }

    buffer->head = buffer->queue = 0;

    return buffer;
}
RingBuffer *RB_add(RingBuffer *b, int value)
{

    b->buffer[b->queue] = value;
    b->queue = (++b->queue) % MAX;
    printf(" %d has been added\n",value);
    return b;
}

int RB_remove(RingBuffer *b)
{
    if (b->head == b->queue)
    {
        printf("no element left to read !!");
        return 0;
    }

    int element = b->buffer[b->head];
    b->head = (++b->head) % MAX;
    printf(" %d is removed \n",element);
    return -1;
}



int main(void)
{
    RingBuffer *buffer = init();

    for (int i = 0; i < 5; i++)
    {
        buffer = RB_add(buffer, i);
    }

    while(RB_remove(buffer));

    printf("\nHello, World! \n");
    return 0;
}
