#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node *first, *rear;

void create(int x)
{
    struct Node *t = (struct Node *)malloc(sizeof(struct Node));
    t->data = x;
    t->next = NULL;
    first = rear = t;
}

void enqueue(int x)
{
    struct Node *t = (struct Node *)malloc(sizeof(struct Node));

    if (t == NULL)
    {
        printf("Queue is full");
    }
    else
    {
        t->data = x;
        t->next = NULL;
        rear->next = t;
        rear = t;
    }
}

int dequeue()
{
    int x = -1;
    struct Node *p;

    if (first == NULL)
    {
        printf("Queue is empty");
    }
    else
    {
        p = first;
        x = p->data;
        first = first->next;
        free(p);
    }
    return x;
}

void display()
{
    struct Node *p = first;

    while (p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
}

int main()
{

    create(5);

    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);

    display();

    printf("\nDeque %d\n", dequeue());
    printf("Deque %d\n", dequeue());

    display();
}