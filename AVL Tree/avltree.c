#include <stdio.h>
#include <stdlib.h>

struct TreeNode
{
    struct TreeNode *leftChild;
    int data;
    int height;
    struct TreeNode *rightChild;
} *root = NULL;

int nodeHeight(struct TreeNode *p)
{
    int hl, hr;
    hl = p && p->leftChild ? p->leftChild->height : 0;
    hr = p && p->rightChild ? p->rightChild->height : 0;

    return hl > hr ? hl + 1 : hr + 1;
}

int balanceFactor(struct TreeNode *p)
{
    int hl, hr;
    hl = p && p->leftChild ? p->leftChild->height : 0;
    hr = p && p->rightChild ? p->rightChild->height : 0;

    return hl - hr;
}

struct TreeNode *llRotation(struct TreeNode *p)
{
    struct TreeNode *pl = p->leftChild;
    struct TreeNode *plr = pl->rightChild;

    pl->rightChild = p;
    p->leftChild = plr;
    p->height = nodeHeight(p);
    pl->height = nodeHeight(pl);

    if (root == p)
        root = pl;

    return pl;
}

struct TreeNode *lrRotation(struct TreeNode *p)
{
    // Create two additional pointer for node's left child and that nodes right child. Hence Left-Right
    struct TreeNode *pl = p->leftChild;
    struct TreeNode *plr = pl->rightChild;

    // Re-assign the Left-Right Node's children to the Left-Node and P
    pl->rightChild = plr->leftChild;
    p->leftChild = plr->rightChild;

    // Re-assign Left and the Node P to be children of Left-Right Node
    plr->leftChild = pl;
    plr->rightChild = p;

    // Re-calculate heights of each node
    pl->height = nodeHeight(pl);
    p->height = nodeHeight(p);
    plr->height = nodeHeight(plr);

    if (p == root)
        root = plr;

    return plr;
}
struct TreeNode *rrRotation(struct TreeNode *p)
{
    return NULL;
}
struct TreeNode *rlRotation(struct TreeNode *p)
{
    return NULL;
}

struct TreeNode *insert(struct TreeNode *p, int key)
{
    struct TreeNode *t = NULL;

    if (p == NULL)
    {
        t = (struct TreeNode *)malloc(sizeof(struct TreeNode));
        t->data = key;
        t->height = 1;
        t->leftChild = t->rightChild = NULL;
        return t;
    }

    if (key < p->data)
        p->leftChild = insert(p->leftChild, key);
    else if (key > p->data)
        p->rightChild = insert(p->rightChild, key);

    p->height = nodeHeight(p);

    // Imbalanced on left-left side.
    if (balanceFactor(p) == 2 && balanceFactor(p->leftChild) == 1)
        return llRotation(p);
    else if (balanceFactor(p) == 2 && balanceFactor(p->leftChild) == -1)
        return lrRotation(p);
    else if (balanceFactor(p) == -2 && balanceFactor(p->rightChild) == -1)
        return rrRotation(p);
    else if (balanceFactor(p) == -2 && balanceFactor(p->rightChild) == 1)
        return rlRotation(p);

    return p;
}

void inOrderTraversal(struct TreeNode *p)
{
    if (p != NULL)
    {
        inOrderTraversal(p->leftChild);
        printf("%d ", p->data);
        inOrderTraversal(p->rightChild);
    }
}

int main()
{
    root = insert(root, 50);
    insert(root, 10);
    insert(root, 20);

    inOrderTraversal(root);

    return 0;
}