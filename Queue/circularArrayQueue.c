#include <stdio.h>
#include <stdlib.h>

// Best way to implement queue using array is make it circular so
// enqueue and dequeue are O(1)
struct CircularQueue
{
    int size;
    int front;
    int rear;
    int *Q;
};

void create(struct CircularQueue *queue, int size)
{
    queue->size = size;
    queue->front = 0;
    queue->rear = 0;
    queue->Q = (int *)malloc(queue->size * sizeof(int));
}

void enqueue(struct CircularQueue *queue, int x)
{
    // Check if next position is front
    if ((queue->rear + 1) % queue->size == queue->front)
    {
        printf("Queue is full!\n");
    }
    else
    {
        // Get next open position in queue and insert
        queue->rear = (queue->rear + 1) % queue->size;
        queue->Q[queue->rear] = x;
    }
}

int dequeue(struct CircularQueue *queue)
{
    int x = -1;
    if (queue->front == queue->rear)
    {
        printf("Queue is empty\n");
    }
    else
    {
        queue->front = (queue->front + 1) % queue->size;
        x = queue->Q[queue->front];
    }
    return x;
}

void display(struct CircularQueue queue)
{
    int i = queue.front + 1;

    do
    {
        printf("%d ", queue.Q[i]);
        i = (i + 1) % queue.size;
    } while (i != ((queue.rear + 1) % queue.size));
    printf("\n");
}

int main()
{
    struct CircularQueue queue;

    create(&queue, 6);

    enqueue(&queue, 1);
    enqueue(&queue, 2);
    enqueue(&queue, 3);
    enqueue(&queue, 4);
    enqueue(&queue, 5);
    enqueue(&queue, 6);
    dequeue(&queue);
    dequeue(&queue);
    enqueue(&queue, 1);
    enqueue(&queue, 2);

    display(queue);
}