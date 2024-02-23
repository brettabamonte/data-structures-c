#include <stdio.h>
#include <stdlib.h>

struct StackNode
{
    int data;
    struct StackNode *next;
};

struct StackNode *s1 = NULL;
struct StackNode *s1Top = NULL;
struct StackNode *s2 = NULL;
struct StackNode *s2Top = NULL;

// STACK IMPLEMENTATION

void createStack(int x)
{
    struct StackNode *t = (struct StackNode *)malloc(sizeof(struct StackNode));
    t->data = x;
    t->next = NULL;
    s1 = s1Top = t;
}

void push(struct StackNode **head, struct StackNode **stackTop, int x)
{
    struct StackNode *t = (struct StackNode *)malloc(sizeof(struct StackNode));
    t->data = x;
    t->next = NULL;

    if (*stackTop == NULL || *head == NULL)
    {
        (*stackTop) = (*head) = t;
    }
    else
    {
        (*stackTop)->next = t;
        (*stackTop) = t;
    }
}

int pop(struct StackNode **stack, struct StackNode **stackTop)
{
    int x = -1;

    if (*stack == NULL)
    {
        printf("Queue is empty\n");
    }
    else
    {
        // Get copy of bottom of stack
        struct StackNode *p = *stack;

        // Check if there is just 1 element in stack
        if (p == *stackTop)
        {
            x = p->data;
            free(p);
            *stack = NULL;
            *stackTop = NULL;
        }
        else
        {
            // Find node before top
            while (p->next != *stackTop)
            {
                p = p->next;
            }
            x = (*stackTop)->data;
            *stackTop = p;
            free(p->next);
            p->next = NULL;
        }
    }

    return x;
}

int isStackEmpty(struct StackNode **stack)
{
    return *stack == NULL ? 1 : 0;
}

void displayStack(struct StackNode *stack)
{
    struct StackNode *p = stack;

    while (p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
}

// Recursive function that prints stack from top to bottom using head recursion
void printStackTopToBottom(struct StackNode *r, struct StackNode *p)
{
    // We've reached bottom of stack
    if (p == NULL)
    {
        return;
    }

    printStackTopToBottom(p, p->next);

    printf("%d ", p->data);
}

void createQueue(int x)
{
    createStack(x);
}

// Queue Implementation
void enqueue(int x)
{
    if (isStackEmpty(&s2))
    {
        push(&s1, &s1Top, x);
    }
    else
    {
        while (s2Top)
        {
            push(&s1, &s1Top, pop(&s2, &s2Top));
        }
        push(&s1, &s1Top, x);
    }
}

int dequeue()
{
    int x = -1;

    // Check if stack 2 is empty
    if (isStackEmpty(&s2))
    {
        // Check if stack 1 is empty
        if (isStackEmpty(&s1))
        {
            // Queue is empty!
            printf("Queue is empty!\n");
        }
        else
        {
            // Copy elements from stack 1 to stack 2
            while (s1Top)
            {
                printf("\nPopping\n");
                push(&s2, &s2Top, pop(&s1, &s1Top));
            }

            // Pop top element from stack 2
            x = pop(&s2, &s2Top);
        }
    }
    else
    {
        x = pop(&s2, &s2Top);
    }

    return x;
}

void displayQueue()
{
    // Check if stack 2 is empty
    if (isStackEmpty(&s2))
    {
        // Check if stack 1 is empty.
        if (isStackEmpty(&s1))
        {
            // No elements in queue
            printf("Queue is empty!\n");
        }
        // Get reference to bottom of stack 1
        struct StackNode *p = s1;

        // Iterate through each element in stack 1 bottom up
        while (p)
        {
            printf("%d ", p->data);
            p = p->next;
        }
    }
    else
    {

        if (isStackEmpty(&s1))
        {
            printStackTopToBottom(NULL, s2);
        }
        else
        {
            // Get reference to bottom of stack 1
            struct StackNode *p = s1;

            // Iterate through each element in stack 1 bottom up
            while (p)
            {
                printf("%d ", p->data);
                p = p->next;
            }

            // Now we need to traverse stack 2 from top to bottom
            // We will use a trailing pointer
            printStackTopToBottom(NULL, s2);
        }
    }
}

int main()
{
    // createStack(10);
    // push(&s1Top, 20);
    // push(&s1Top, 30);
    // push(&s1Top, 40);
    // push(&s1Top, 50);

    // displayStack(s1);

    // printf("\n%d popped\n", pop(&s1, &s1Top));
    // printf("%d popped\n", pop(&s1, &s1Top));

    // displayStack(s1);

    createQueue(10);
    enqueue(55);
    enqueue(65);
    enqueue(75);

    displayQueue();

    printf("\nRemoving %d from queue\n", dequeue());
    printf("\nRemoving %d from queue\n", dequeue());

    enqueue(80);
    enqueue(100);

    displayQueue();

    printf("\nRemoving %d from queue\n", dequeue());
    printf("\nRemoving %d from queue\n", dequeue());
    printf("\nRemoving %d from queue\n", dequeue());

    enqueue(125);
    enqueue(200);

    displayQueue();
}