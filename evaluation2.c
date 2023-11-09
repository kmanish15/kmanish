#include <stdio.h>
#include <stdlib.h>

#define DEGREE 3

struct BTreeNode
{
    int keys[2 * DEGREE - 1];
    struct BTreeNode *children[2 * DEGREE];
    int keyCount;
    int isLeaf;
};

struct BTreeNode *createNode()
{
    struct BTreeNode *newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
    newNode->keyCount = 0;
    newNode->isLeaf = 1;
    for (int i = 0; i < 2 * DEGREE; i++)
    {
        newNode->keys[i] = 0;
        newNode->children[i] = NULL;
    }
    return newNode;
}

int search(struct BTreeNode *root, int key)
{
    int i = 0;
    while (i < root->keyCount && key > root->keys[i])
    {
        i++;
    }

    if (i < root->keyCount && key == root->keys[i])
    {
        return 1; // Key found
    }
    else if (root->isLeaf)
    {
        return 0; // Key not found
    }
    else
    {
        return search(root->children[i], key);
    }
}

void insert(struct BTreeNode **root, int key)
{
    if (*root == NULL)
    {
        struct BTreeNode *newNode = createNode();
        newNode->keys[0] = key;
        newNode->keyCount = 1;
        *root = newNode;
    }
    else
    {
        if ((*root)->keyCount == 2 * DEGREE - 1)
        {
            // Split the root
            struct BTreeNode *newRoot = createNode();
            newRoot->children[0] = *root;
            splitChild(&newRoot, 0);
            *root = newRoot;
        }
        insertNonFull(*root, key);
    }
}