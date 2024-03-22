                //DONE BY
      //1. GERISHON KIHATO SCT221-0219/2022
      //2. VINCENT KIMANTHI SCT221-0690/2022

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int key;
    struct Node *left, *right;
};

struct Node* newNode(int item)
{
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

struct Node* insert(struct Node* node, int key)
{
    if (node == NULL) return newNode(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    return node;
}


struct Node* deleteNode(struct Node* root, int key) 
{
    if (root == NULL) return root;
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL)
		{
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
		{
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        struct Node* temp = root->right;
        while (temp && temp->left != NULL)
            temp = temp->left;
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}


int height(struct Node* node)
{
    if (node == NULL) return -1;
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}


void printLevelAndHeight(struct Node* root, int key, int level)
{
    if (root == NULL)
	{
        printf("Node not found in the BST\n");
        return;
    }
    if (root->key == key)
	{
        printf("Level of node %d: %d\n", key, level);
        printf("Height of node %d: %d\n", key, height(root));
    }
    else if (key < root->key)
        printLevelAndHeight(root->left, key, level + 1);
    else
        printLevelAndHeight(root->right, key, level + 1);
}

void inorder(struct Node* root)
{
    if (root != NULL)
	{
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

void preorder(struct Node* root)
{
    if (root != NULL)
	{
        printf("%d ", root->key); 
        preorder(root->left); 
        preorder(root->right); 
    }
}


int main()
{
    int arr[] = {30, 20, 40, 10, 25, 35, 45, 5, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    struct Node* root = NULL;

    int i;
    for (i = 0; i < n; i++)
        root = insert(root, arr[i]);

    printf("Inorder traversal of the BST: ");
    inorder(root);
    printf("\n");
    
    printf("Preorder traversal of the BST: ");
    preorder(root);
    printf("\n");

    root = deleteNode(root, 20);
    printf("\nInorder traversal after deleting node with key 20: ");
    inorder(root);
    printf("\nPreorder traversal after deleting node with key 20: ");
    preorder(root);
    printf("\n");
    printf("\n");

    printf("Height of the BST: %d\n", height(root));

    printLevelAndHeight(root, 30, 0);

    return 0;
}

