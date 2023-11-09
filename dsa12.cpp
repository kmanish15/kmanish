


#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;


Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}


Node* leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}


Node* rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

Node* splay(Node* root, int data) {
    if (root == NULL || root->data == data)
        return root;

    if (data < root->data) {
        if (root->left == NULL)
            return root;

        if (data < root->left->data) {
            root->left->left = splay(root->left->left, data);
            root = rightRotate(root);
        } else if (data > root->left->data) {
            root->left->right = splay(root->left->right, data);
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }

        return (root->left == NULL) ? root : rightRotate(root);
    } else {
        if (root->right == NULL)
            return root;

        if (data < root->right->data) {
            root->right->left = splay(root->right->left, data);
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        } else if (data > root->right->data) {
            root->right->right = splay(root->right->right, data);
            root = leftRotate(root);
        }

        return (root->right == NULL) ? root : leftRotate(root);
    }
}

Node* insert(Node* root, int data) {
    if (root == NULL)
        return createNode(data);

    root = splay(root, data);

    if (data < root->data) {
        Node* newNode = createNode(data);
        newNode->right = root;
        newNode->left = root->left;
        root->left = NULL;
        return newNode;
    } else if (data > root->data) {
        Node* newNode = createNode(data);
        newNode->left = root;
        newNode->right = root->right;
        root->right = NULL;
        return newNode;
    } else {
        return root;
    }
}


Node* search(Node* root, int data) {
    return splay(root, data);
}


void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

int main() {
    Node* root = NULL;
    int choice, data;

    while (1) {
        printf("\nSplay Tree Operations\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Print In-order\n");
        printf("4. Exit\n");
        printf("Enter your choice number: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                root = insert(root, data);
                break;
            case 2:
                printf("Enter data to search: ");
                scanf("%d", &data);
                root = search(root, data);
                if (root->data == data)
                    printf("Data found: %d\n", data);
                else
                    printf("Data not found: %d\n", data);
                break;
            case 3:
                printf("In-order traversal: ");
                inOrder(root);
                printf("\n");
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Please try again.tinue and then Allow when prompted by your browser.
