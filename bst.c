#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char id[20];
    struct Node *left, *right;
};

struct Node* createNode(char id[]) {
    struct Node* newNode =
        (struct Node*)malloc(sizeof(struct Node));

    strcpy(newNode->id, id);
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, char id[]) {
    if (root == NULL)
        return createNode(id);

    if (strcmp(id, root->id) < 0)
        root->left = insert(root->left, id);
    else if (strcmp(id, root->id) > 0)
        root->right = insert(root->right, id);

    return root;
}

void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%s ", root->id);
        inorder(root->right);
    }
}

int bstSearch(struct Node* root, char key[],
              int *comparisons) {
    while (root != NULL) {
        (*comparisons)++;

        int result = strcmp(key, root->id);

        if (result == 0)
            return 1;

        if (result < 0)
            root = root->left;
        else
            root = root->right;
    }

    return 0;
}

int linearSearch(char ids[][20], int n,
                 char key[], int *comparisons) {
    for (int i = 0; i < n; i++) {
        (*comparisons)++;

        if (strcmp(ids[i], key) == 0)
            return 1;
    }

    return 0;
}

int main() {
    char ids[8][20] = {
        "A102", "A25", "A7", "B100",
        "B12", "A120", "B3", "A45"
    };

    struct Node* root = NULL;

    for (int i = 0; i < 8; i++)
        root = insert(root, ids[i]);

    printf("Inorder traversal:\n");
    inorder(root);
    printf("\n");

    char key[20] = "A45";
    int bstCount = 0, linearCount = 0;

    int foundBST = bstSearch(root, key, &bstCount);
    int foundLinear =
        linearSearch(ids, 8, key, &linearCount);

    printf("\nSearching for %s\n", key);

    printf("BST: %s, comparisons = %d\n",
           foundBST ? "Found" : "Not found", bstCount);

    printf("Linear Search: %s, comparisons = %d\n",
           foundLinear ? "Found" : "Not found",
           linearCount);

    return 0;
}