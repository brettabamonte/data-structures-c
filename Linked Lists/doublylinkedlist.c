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
    int i;

    struct Node *first = (struct Node *)malloc(sizeof(struct Node));
    first->data = A[0];
    first->prev = first->next = NULL;
    last = first;

    for (i = 1; i < n; i++)
    {
        t = (struct Node *)malloc(sizeof(struct Node));
        t->data = A[i];
        t->next = last->next;
        t->prev = last;
        last->next = t;
        last = t;
    }
    return first;
}

void display(struct Node *p)
{
    while (p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int length(struct Node *p)
{
    int length = 0;
    while (p)
    {
        length++;
        p = p->next;
    }
    return length;
}

void insert(int pos, int x, struct Node **head)
{
    struct Node *t = (struct Node *)malloc(sizeof(struct Node));
    t->data = x;

    if (pos == 0)
    {
        if (*head)
        {
            (*head)->prev = t;
            t->next = *head;
            t->prev = NULL;
            *head = t;
        }
        else
        {
            *head = t;
            t->prev = NULL;
            t->next = NULL;
        }
    }
    else if (pos > 0)
    {
        int i;
        struct Node *p = *head;

        for (i = 0; i < pos - 1 && p->next; i++)
            p = p->next;

        if (p->next != NULL)
        {
            t->next = p->next;
            p->next->prev = t;
            p->next = t;
            t->prev = p;
        }
        else
        {
            t->next = NULL;
            t->prev = p;
            p->next = t;
        }
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
        if (*head)
        {
            int x = (*head)->data;
            if ((*head)->next == NULL)
            {
                free(*head);
                *head = NULL;
                return x;
            }
            else
            {
                *head = (*head)->next;
                return x;
            }
        }
        else
        {
            return -1;
        }
    }
    else if (pos > 0)
    {
        // Get node we want to delete
        for (int i = 0; i < pos - 1 && p->next; i++)
            p = p->next;

        // Get data to return
        int x = p->data;

        if (p->next)
        {
            p->prev->next = p->next;
            p->next->prev = p->prev;
            free(p);
            return x;
        }
        else
        {
            p->prev->next = NULL;
            free(p);
            return x;
        }
    }
    else
    {
        return -1;
    }
}

void reverse(struct Node **head)
{
    struct Node *p = *head;
    struct Node *temp;

    // Traverse list and get reference to last node
    while (p != NULL)
    {
        // Get temp reference to next node
        temp = p->next;
        // Set next node's next ref to prev node
        p->next = p->prev;
        // Set next node prev node to temp
        p->prev = temp;
        // Get next prev node
        p = p->prev;
        if (p != NULL && p->next == NULL)
        {
            *head = p;
        }
    }
}

int main()
{
    int A[] = {3, 5, 6, 7, 10, 14};

    struct Node *head = create(A, 6);
    display(head);
    printf("Length is %d\n", length(head));

    // insert(6, 92, &head);
    // insert(8, 100, &head);
    // insert(1, 11, &head);
    // display(head);

    // delete (0, &head);
    // display(head);
    // delete (4, &head);
    // display(head);

    reverse(&head);
    display(head);
}