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
    // Create pointers to the first node or head. And to the last node we've created
    struct Node *first, *last;

    // Create node in heap
    first = (struct Node *)malloc(sizeof(struct Node));
    // Set data to the first element in array
    first->data = A[0];
    // Set pointer to next node to NULL for now.
    first->next = NULL;
    // Set the last node we made to the head!
    last = first;

    // Loop through array
    for (i = 1; i < n; i++)
    {
        // Create a new node in heap
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        // Set data of new node to respective element in array
        newNode->data = A[i];
        // Set next pointer to NULL for now.
        newNode->next = NULL;
        // Set the pointer for the last node we created to the node we just made.
        // E.G. For the 2nd element set the pointer of the head to this new node
        last->next = newNode;
        // Set last node we made to this current one
        last = newNode;
    }

    return first;
}

void display(struct Node *node)
{
    // Check if node is NULL
    while (node != NULL)
    {
        // It's not so print then set the current node to the next node in the list
        printf("%d ", node->data);
        node = node->next;
    }
}

int countIterative(struct Node *p)
{
    int count;

    while (p != NULL)
    {
        count++;
        p = p->next;
    }
    return count;
}

int countRecursive(struct Node *p)
{
    if (p == NULL)
        return 0;

    return countRecursive(p->next) + 1;
}

int sumIterative(struct Node *p)
{
    int sum = 0;

    while (p != NULL)
    {
        sum += p->data;
        p = p->next;
    }

    return sum;
}

int sumRecursive(struct Node *p)
{
    if (p == NULL)
        return 0;

    return sumRecursive(p->next) + p->data;
}

void RDisplay(struct Node *p)
{
    if (p != NULL)
    {
        printf("%d ", p->data);
        RDisplay(p->next);
    }
}

int maxIterative(struct Node *p)
{
    int m = -32768;

    while (p != NULL)
    {
        if (p->data > m)
            m = p->data;
        p = p->next;
    }

    return m;
}

int maxRecursive(struct Node *p)
{
    if (p == NULL)
        return -32768;

    return maxRecursive(p->next) > p->data ? maxRecursive(p->next) : p->data;
}

struct Node *search(struct Node *p, int key)
{
    // Linear search and moves found key to head
    struct Node *q;        // Tail pointer
    struct Node *head = p; // Head pointer

    while (p != NULL)
    { // Key is found
        if (p->data == key)
        {
            // Set pointer on tail pointer to the correct next node
            q->next = p->next; // Set previous node's pointer to pointer after found node

            // Set pointer on found node to the original head b/c now the orig head is th
            p->next = head;

            // Set head to point to 1st node
            head = p;

            return p; // Return pointer
        }
        else
        {
            // Didn't find key so increment pointer and tail pointer
            q = p;
            p = p->next;
        }
    }

    return NULL;
}

void insert(int pos, int x, struct Node **first)
{
    // Create pointers for new node and the pointer for previous node
    struct Node *t, *p;

    // Start previous node at first
    p = *first;

    // If we are inserting a 0 index. Create node and make first pointer point to this node.
    if (pos == 0)
    {
        t = (struct Node *)malloc(sizeof(struct Node));
        t->data = x;
        t->next = (*first)->next;
        *first = t;
    }
    else if (pos > 0)
    {
        // Move pointer, p, to the node that is at the index pos. Make sure the pos provided is valid and points to a valid node
        for (int i = 0; i < pos - 1 && p; i++)
            p = p->next;

        // If p is pointing to a node
        if (p != NULL)
        {
            t = (struct Node *)malloc(sizeof(struct Node));
            t->data = x;
            t->next = p->next;
            p->next = t;
        }
    }
}

void insertLast(int x, struct Node *first, struct Node **last)
{
    struct Node *t = (struct Node *)malloc(sizeof(struct Node));
    t->data = x;
    t->next = NULL;

    // Check if list is empty
    if (first == NULL)
    {
        first = *last = t;
    }
    else
    {
        // List isn't empty
        (*last)->next = t;
        *last = t;
    }
}

struct Node *findLastNode(struct Node *head)
{
    while (head->next != NULL)
    {
        head = head->next;
    }

    return head;
}

void insertSortedList(int x, struct Node **head)
{
    // Create pointer for new node and trailing node
    struct Node *t, *q = NULL;

    struct Node *p = *head; // Get reference to head so we can traverse list

    // Create node
    t = (struct Node *)malloc(sizeof(struct Node));
    t->data = x;
    t->next = NULL;

    // If head doesn't exist. Make head point to new node
    if (p == NULL)
    {
        *head = t;
    }
    else
    {
        // Traverse through list until x is < current node's data
        while (p && p->data < x)
        {
            // Set trailing pointer to current node
            q = p;
            // Set pointer to next node
            p = p->next;
        }
        // If the x value is less than the head
        if (p == *head)
        {
            // Set new node to point to old head
            t->next = p;
            // Set head to point to new node
            *head = t;
        }
        else
        {
            // Set new node to point to trailing node's next pointer
            t->next = q->next;
            // Set trailing nodes pointer to new node
            q->next = t;
        }
    }
}

int delete(int pos, struct Node **head)
{

    if (pos == 1)
    {
        struct Node *q = *head;
        *head = (*head)->next;
        return q->data;
        free(q);
    }
    else if (pos > 1)
    {
        struct Node *p = *head;
        struct Node *q = NULL;

        for (int i = 0; i < pos - 1 && p; i++)
        {
            q = p;
            p = p->next;
        }

        if (p)
        {
            q->next = p->next;
            return p->data;
            free(p);
        }
    }

    return 0;
}

int isListSorted(struct Node *head)
{
    int x = head->data;
    struct Node *p = head->next;

    while (p != NULL)
    {
        if (x > p->data)
        {
            return 0;
        }
        x = p->data;
        p = p->next;
    }

    return 1;
}

void deleteDuplicatesSortedList(struct Node **head)
{
    struct Node *p = *head;
    struct Node *q = p->next;

    while (q != NULL)
    {
        if (p->data != q->data)
        {
            p = q;
            q = q->next;
        }
        else
        {
            p->next = q->next;
            free(q);
            q = p->next;
        }
    }
}

void reverseIterative(struct Node **head)
{
    struct Node *r, *q;
    r = NULL;
    q = NULL;

    struct Node *p = *head;

    // Iterate over each node and slide pointers
    while (p != NULL)
    {
        r = q;
        q = p;
        p = p->next;
        q->next = r; // Reverse link to previous node
    }
    // Set new head to q
    *head = q;
}

void reverseRecursively(struct Node *q, struct Node *p, struct Node **head)
{
    if (p != NULL)
    {
        // Slide pointers
        reverseRecursively(p, p->next, head);

        // On return point node to previous node
        p->next = q;
    }
    else
    {
        // End of list is reached
        *head = q;
    }
}

struct Node *concat(struct Node *first, struct Node *second)
{
    struct Node *head = first;

    while (first->next != NULL)
    {
        first = first->next;
    }

    first->next = second;
    return head;
}

struct Node *merge(struct Node *first, struct Node *second)
{
    // Create pointers
    //  last = last node created in merge list
    //  third = points to head of newly created list
    // Set them equal to NULL to start
    struct Node *last, *third;
    last = third = NULL;

    // Compare first nodes. Set head of third list to correct one
    // Set last to the new head
    // Move correct pointer so we can continue comparing lists
    if (first->data < second->data)
    {
        third = first;
        last = third;
        first = first->next;
    }
    else
    {
        third = second;
        last = third;
        second = second->next;
    }

    // Keep comparing while there are both nodes that aren't NULL
    while (first != NULL && second != NULL)
    {
        // Check which node in the two lists is <
        // Point last node to the smaller node
        // Move pointer to next node in the correct list
        // Set last node pointer to NULL in case it's the end of the list
        if (first->data < second->data)
        {
            last->next = first;
            last = first;
            first = first->next;
            last->next = NULL;
        }
        else
        {
            last->next = second;
            last = second;
            second = second->next;
            last->next = NULL;
        }
    }

    // One of the lists is empty. Merge remaining nodes in other list
    if (first != NULL)
        last->next = first;
    else
        last->next = second;

    return third;
}

int isLoop(struct Node *head)
{
    // Create two pointers
    struct Node *p, *q;
    p = q = head;

    do
    {
        // Increment pointer by 1
        p = p->next;
        // Increment second pointer by 2 or set to NULL
        q = q->next;
        q = q != NULL ? q->next : NULL;
    } while (p && q && p != q); // Continue looping while p & q exist and they don't equal

    // If p and q are equal, there's a loop
    if (p == q)
        return 1;
    else
        return 0;
}

int middleNode(struct Node *head)
{
    // find length of linked list
    int count = 0;
    struct Node *p = head;
    while (p)
    {
        p = p->next;
        count++;
    }

    p = head;
    int middle = (count / 2) - ((count / 2) % 10 / 10);
    for (int i = 0; i < middle; i++)
    {
        p = p->next;
    }

    return p->data;
}

int intersectingNode(struct Node *p, struct Node *q)
{
    while (p->next != q->next && p && q)
    {
        p = p->next;
        q = q->next;
    }
    if (p->next == NULL || q->next == NULL)
        return -1;
    else
        return p->next->data;
    // return p->next != NULL ? p->next->data : -1;
}

int main()
{

    int A[] = {3, 5, 6, 8, 10, 15};
    int B[] = {3, 5, 6, 6, 10, 15};

    struct Node *head = create(A, 6);
    struct Node *head2 = create(B, 6);

    head2->next->next = head->next;

    printf("%d\n", intersectingNode(head, head2));

    return 1;
}