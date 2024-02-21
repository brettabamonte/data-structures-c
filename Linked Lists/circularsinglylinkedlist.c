#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node *create(int A[], int n)
{
    int i;
    struct Node *t, *last;
    struct Node *head = (struct Node *)malloc(sizeof(struct Node));
    head->data = A[0];
    head->next = head;
    last = head;

    for (i = 1; i < n; i++)
    {
        t = (struct Node *)malloc(sizeof(struct Node));
        t->data = A[i];
        t->next = last->next;
        last->next = t;
        last = t;
    }

    return head;
}

void display(struct Node *head)
{
    struct Node *p = head;
    do
    {
        printf("%d ", p->data);
        p = p->next;
    } while (p != head);
    printf("\n");
}

void insert(int pos, int x, struct Node **head)
{
    struct Node *t;
    struct Node *p;

    if (pos == 0)
    {
        t = (struct Node *)malloc(sizeof(struct Node));
        t->data = x;
        if (*head == NULL)
        {
            t->next = t;
            *head = t;
        }
        else
        {
            t->next = *head;
            p = *head;
            while (p->next != *head)
            {
                p = p->next;
            }
            p->next = t;
            *head = t;
        }
    }
    else if (pos > 0)
    {
        // Create new node
        t = (struct Node *)malloc(sizeof(struct Node));
        t->data = x;

        // Create pointer starting at head
        p = *head;

        // Find position. Check if the previous node is valid && the next pointer isn't the head.
        // If it's the head we need to stop since we want to insert at the end of the list
        for (int i = 0; i < pos - 1 && p && p->next != *head; i++)
        {
            // Get next node
            p = p->next;
        }

        // Set next pointer on new node to prev node link
        t->next = p->next;
        // Set prev node to point to new node
        p->next = t;
    }
    else
    {
        return;
    }
}

int delete(int pos, struct Node **head)
{
    // Deleting head
    if (pos == 0)
    {
        // Get last node
        struct Node *p = *head;
        struct Node *h = *head;
        while (p->next != h)
        {
            p = p->next;
        }
        // We have last node. Update pointer to second element
        p->next = h->next;
        // Move head to 2nd element
        *head = h->next;
        // Return data and Free head node from memory
        int x = h->data;
        free(h);
        return x;
    }
    else if (pos > 0)
    {
        struct Node *p = *head;

        // Find node that is before the node we want to delete
        for (int i = 0; i < pos - 2 && p && p->next != *head; i++)
        {
            p = p->next;
        }
        // Get reference to node we want to delete
        struct Node *q = p->next;
        // Update link
        p->next = q->next;
        // Return data Delete node from memory
        int x = q->data;
        free(q);
        return x;
    }
    else
    {
        return -1;
    }
}

int main()
{

    int A[] = {2, 3, 4, 5, 6};
    struct Node *head = create(A, 5);

    insert(10, 50, &head);
    insert(8, 34, &head);
    insert(0, 89, &head);

    display(head);

    printf("%d\n", delete (4, &head));
    printf("%d\n", delete (2, &head));
    display(head);
}