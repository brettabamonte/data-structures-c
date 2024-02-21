#include <stdio.h>
#include <stdlib.h>

struct Node
{
    struct Node *prev;
    int data;
    struct Node *next;
};

struct Node *create(int A[], int n)
{
    struct Node *t, *last;
    struct Node *first;

    first = (struct Node *)malloc(sizeof(struct Node));
    first->data = A[0];
    first->prev = first;
    first->next = first;
    last = first;

    for (int i = 1; i < n; i++)
    {
        t = (struct Node *)malloc(sizeof(struct Node));
        t->data = A[i];
        t->prev = last;
        t->next = first;
        last->next = t;
        last = t;
    }

    return first;
}

void display(struct Node *head)
{
    struct Node *p = head;
    do
    {
        printf("%d ", p->data);
        p = p->next;
    } while (p != NULL && p != head);
}

// Insert node using 0 index
void insert(int pos, int x, struct Node **head)
{
    struct Node *p = *head;
    struct Node *t = (struct Node *)malloc(sizeof(struct Node));
    t->data = x;

    if (pos == 0)
    {
        if (*head)
        {
            t->next = *head;
            t->prev = (*head)->prev;
            (*head)->prev->next = t;
            (*head)->prev = t;
            *head = t;
        }
        else
        {
            t->prev = t;
            t->next = t;
            *head = t;
        }
    }
    else if (pos > 0)
    {
        // Find position in list. Stop at end node
        for (int i = 1; i < pos - 1 && p->next != *head; i++)
        {
            p = p->next;
        }
        t->next = p->next;
        t->prev = p;
        p->next->prev = t;
        p->next = t;
    }
    else
    {
        return;
    }
}

int delete(int pos, struct Node **head)
{

    struct Node *p = *head;

    if (pos == 0)
    {
        int x = p->data;

        if (p->next)
        {
            // Change link on last node to second node
            p->prev->next = p->next;
            p->next->prev = p->prev;
            *head = p->next;
            free(p);
        }
        else
        {
            free(p);
            *head = NULL;
        }

        return x;
    }
    else if (pos > 0)
    {
        for (int i = 0; i < pos - 1 && p && p->next != *head; i++)
            p = p->next;

        int x = p->data;
        p->prev->next = p->next;
        p->next->prev = p->prev;
        free(p);
        return x;
    }
    else
    {
        return -1;
    }
}

int main()
{
    int A[] = {3, 5, 6, 7, 8, 10, 17};

    struct Node *head = create(A, 7);
    insert(2, 35, &head);
    display(head);
    printf("\n%d\n", delete (2, &head));
    printf("%d\n", delete (10, &head));
    display(head);
}