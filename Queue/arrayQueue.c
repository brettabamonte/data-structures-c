#include <stdio.h>
#include <stdlib.h>

// Drawbacks of this Queue
// CAN'T REUSE QUEUE SPACE:
//        Moving front pointer reduces space of queue because we aren't resetting the pointer.
// EVERY LOCATION CAN ONLY BE USED ONCE
// SOLUTIONS:
//   1. Reset pointers once queue becomes empty (front == rear)

struct Queue
{
    int size;
    int front;
    int rear;
    int *Q;
};

void create(struct Queue *q, int size)
{
    q->size = size;
    q->front = q->rear = -1;
    q->Q = (int *)malloc(q->size * sizeof(int));
}

void enqueue(struct Queue *queue, int x)
{
    if (queue->rear == queue->size - 1)
    {
        printf("Queue is full\n");
    }
    else
    {
        queue->rear++;
        queue->Q[queue->rear] = x;
    }
}

int dequeue(struct Queue *queue)
{
    int x = -1;
    if (queue->front == queue->rear)
        printf("Queue is Empty\n");
    else
    {
        queue->front++;
        x = queue->Q[queue->front];
    }
    return x;
}

void display(struct Queue queue)
{
    for (int i = queue.front + 1; i <= queue.rear; i++)
    {
        printf("%d ", queue.Q[i]);
    }
    printf("\n");
}

int main()
{
    struct Queue q;
    create(&q, 5);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);

    display(q);

    dequeue(&q);
    dequeue(&q);

    display(q);
}