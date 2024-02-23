#include <stdio.h>
#include <stdlib.h>

// DOES NOT FOLLOW FIFO

struct Node
{
    int data;
    struct Node *next;
};

struct Node *front, *rear;

void create(int x)
{
    struct Node *t = (struct Node *)malloc(sizeof(struct Node));
    t->data = x;
    t->next = NULL;
    front = rear = t;
}

// If 1 is passed, enqueue from front
void enqueue(int x, int fr)
{
    struct Node *t = (struct Node *)malloc(sizeof(struct Node));
    t->data = x;

    if (fr == 1)
    {
        t->next = front;
        front = t;
    }
    else
    {
        t->next = NULL;
        rear->next = t;
        rear = t;
    }
}

// If 1 is passed, deqeue from rear
int dequeue(int re)
{
    int x = -1;
    struct Node *p;

    if (front && rear)
    {
        if (re == 0)
        {
            p = front;
            x = p->data;
            front = front->next;
            free(p);
        }
        else
        {
            p = front;

            // Find element before rear
            while (p->next != rear)
            {
                p = p->next;
            }
            x = rear->data;
            rear = p;
            free(p->next);
            rear->next = NULL;
        }
    }
    else
    {
        printf("Queue is empty\n");
    }

    return x;
}

void display()
{
    struct Node *p = front;

    while (p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
}

int main()
{
    create(10);
    enqueue(20, 0);
    enqueue(30, 0);
    enqueue(40, 0);
    enqueue(50, 0);
    enqueue(5, 1);
    enqueue(7, 1);

    display();

    printf("\n%d dequeued", dequeue(0));
    printf("\n%d dequeued", dequeue(0));
    printf("\n%d dequeued\n", dequeue(1));

    display();
}