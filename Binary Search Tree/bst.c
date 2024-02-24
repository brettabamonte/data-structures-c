#include <stdio.h>
#include <stdlib.h>

struct TreeNode
{
    struct TreeNode *leftChild;
    int data;
    struct TreeNode *rightChild;
};

struct TreeNode *create(struct TreeNode *p, int key)
{
    p = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    p->leftChild = p->rightChild = NULL;
    p->data = key;
    return p;
}

void insert(struct TreeNode *p, int key)
{
    struct TreeNode *t, *r;
    t = p;
    r = NULL;

    while (t != NULL)
    {
        r = t;

        if (t->data == key)
            return;
        else if (key < t->data)
        {
            t = t->leftChild;
        }
        else
        {
            t = t->rightChild;
        }
    }

    t = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    t->data = key;
    t->leftChild = t->rightChild = NULL;

    if (key < r->data)
        r->leftChild = t;
    else
        r->rightChild = t;
}

int height(struct TreeNode *p)
{
    int x, y;

    if (p != NULL)
    {
        x = height(p->leftChild);
        y = height(p->rightChild);

        if (x > y)
            return x + 1;
        else
            return y + 1;
    }

    return 0;
}

struct TreeNode *inorderPre(struct TreeNode *p)
{
    while (p && p->rightChild != NULL)
    {
        p = p->rightChild;
    }
    return p;
}

struct TreeNode *inorderSuc(struct TreeNode *p)
{
    while (p && p->leftChild != NULL)
    {
        p = p->leftChild;
    }
    return p;
}

struct TreeNode *rInsert(struct TreeNode *p, int key)
{
    struct TreeNode *t = NULL;
    if (p == NULL)
    {
        t = (struct TreeNode *)malloc(sizeof(struct TreeNode));
        t->data = key;
        t->leftChild = t->rightChild = NULL;
        return t;
    }

    if (key < p->data)
    {
        p->leftChild = rInsert(p->leftChild, key);
    }
    else if (key > p->data)
    {
        p->rightChild = rInsert(p->rightChild, key);
    }
    return p;
}

struct TreeNode *delete(struct TreeNode *p, int key)
{
    struct TreeNode *q;

    if (p == NULL)
        return NULL;
    if (p->leftChild == NULL && p->rightChild == NULL)
    {
        free(p);
        return NULL;
    }

    if (key < p->data)
    {
        p->leftChild = delete (p->leftChild, key);
    }
    else if (key > p->data)
    {
        p->rightChild = delete (p->rightChild, key);
    }
    else
    {
        if (height(p->leftChild) > height(p->rightChild))
        {
            q = inorderPre(p->leftChild);
            p->data = q->data;
            p->leftChild = delete (p->leftChild, q->data);
        }
        else
        {
            q = inorderSuc(p->rightChild);
            p->data = q->data;
            p->rightChild = delete (p->rightChild, q->data);
        }
    }

    return p;
}

void displayBST(struct TreeNode *p)
{
    if (!p)
        return;
    displayBST(p->leftChild);
    printf("%d ", p->data);
    displayBST(p->rightChild);
}

int main()
{
    struct TreeNode *root = NULL;
    root = rInsert(root, 10);
    rInsert(root, 20);
    rInsert(root, 5);
    rInsert(root, 2);
    rInsert(root, 78);
    rInsert(root, 65);

    delete (root, 10);

    displayBST(root);

    printf("\nHeight of tree %d\n", height(root));
}