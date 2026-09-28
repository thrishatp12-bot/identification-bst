#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IDS 20
#define MAX_LEN 20

/* BST Node */
struct Node {
    char id[MAX_LEN];
    struct Node *left;
    struct Node *right;
};

/* Create a new BST node */
struct Node* createNode(const char id[]) {
    struct Node* newNode =
        (struct Node*)malloc(sizeof(struct Node));

    strcpy(newNode->id, id);
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

/* Insert an ID into the BST */
struct Node* insert(struct Node* root, const char id[]) {

    if (root == NULL)
        return createNode(id);

    if (strcmp(id, root->id) < 0)
        root->left = insert(root->left, id);

    else if (strcmp(id, root->id) > 0)
        root->right = insert(root->right, id);

    return root;
}

/* Inorder traversal */
void inorder(struct Node* root) {

    if (root != NULL) {
        inorder(root->left);
        printf("%s ", root->id);
        inorder(root->right);
    }
}

/* Calculate height of BST */
int height(struct Node* root) {

    if (root == NULL)
        return 0;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return 1 + (leftHeight > rightHeight ?
                leftHeight : rightHeight);
}

/* BST search with comparison count */
int bstSearch(struct Node* root, const char key[],
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

/* Linear search with comparison count */
int linearSearch(char ids[][MAX_LEN], int n,
                 const char key[], int *comparisons) {

    for (int i = 0; i < n; i++) {

        (*comparisons)++;

        if (strcmp(ids[i], key) == 0)
            return 1;
    }

    return 0;
}

/* Free BST memory */
void freeTree(struct Node* root) {

    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

/* Find longest ID */
void keyLengthAnalysis(char ids[][MAX_LEN], int n) {

    int shortest = strlen(ids[0]);
    int longest = strlen(ids[0]);

    char shortestID[MAX_LEN];
    char longestID[MAX_LEN];

    strcpy(shortestID, ids[0]);
    strcpy(longestID, ids[0]);

    printf("\n--- Key Length Analysis ---\n");

    for (int i = 0; i < n; i++) {

        int length = strlen(ids[i]);

        printf("%s -> %d characters\n",
               ids[i], length);

        if (length < shortest) {
            shortest = length;
            strcpy(shortestID, ids[i]);
        }

        if (length > longest) {
            longest = length;
            strcpy(longestID, ids[i]);
        }
    }

    printf("Shortest key : %s (%d characters)\n",
           shortestID, shortest);

    printf("Longest key  : %s (%d characters)\n",
           longestID, longest);
}

/* Build BST and display information */
struct Node* buildTree(char ids[][MAX_LEN], int n,
                       const char orderName[]) {

    struct Node* root = NULL;

    printf("\n--- %s ---\n", orderName);

    printf("Insertion order: ");

    for (int i = 0; i < n; i++) {
        printf("%s ", ids[i]);
        root = insert(root, ids[i]);
    }

    printf("\nInorder traversal: ");
    inorder(root);

    printf("\nBST height: %d\n", height(root));

    return root;
}

int main() {

    /* Identification numbers */
    char ids[MAX_IDS][MAX_LEN] = {
        "A102",
        "A25",
        "A7",
        "B100",
        "B12",
        "A120",
        "B3",
        "A45"
    };

    int n = 8;

    printf("========================================\n");
    printf(" IDENTIFICATION NUMBER MANAGEMENT USING BST\n");
    printf("========================================\n");

    /* Display original IDs */
    printf("\nOriginal IDs:\n");

    for (int i = 0; i < n; i++)
        printf("%s ", ids[i]);

    printf("\n");

    /* Key length analysis */
    keyLengthAnalysis(ids, n);

    /* -------------------------------------------------
       INSERTION ORDER 1
       ------------------------------------------------- */

    struct Node* root1 =
        buildTree(ids, n, "Insertion Order 1");

    /* -------------------------------------------------
       Search multiple IDs
       ------------------------------------------------- */

    char searchKeys[][MAX_LEN] = {
        "A45",
        "A102",
        "B100",
        "B3",
        "C50"
    };

    int searchCount = 5;

    printf("\n========================================\n");
    printf(" SEARCH ANALYSIS\n");
    printf("========================================\n");

    for (int i = 0; i < searchCount; i++) {

        int bstComparisons = 0;
        int linearComparisons = 0;

        int foundBST =
            bstSearch(root1, searchKeys[i],
                      &bstComparisons);

        int foundLinear =
            linearSearch(ids, n, searchKeys[i],
                         &linearComparisons);

        printf("\nSearching for: %s\n",
               searchKeys[i]);

        printf("BST Search    : %s, Comparisons = %d\n",
               foundBST ? "Found" : "Not Found",
               bstComparisons);

        printf("Linear Search : %s, Comparisons = %d\n",
               foundLinear ? "Found" : "Not Found",
               linearComparisons);
    }

    /* -------------------------------------------------
       INSERTION ORDER 2
       -------------------------------------------------
       Same IDs but inserted in a different order.
       This demonstrates the effect of insertion order.
       ------------------------------------------------- */

    char idsOrder2[MAX_IDS][MAX_LEN] = {
        "A7",
        "A25",
        "A45",
        "A102",
        "A120",
        "B3",
        "B12",
        "B100"
    };

    struct Node* root2 =
        buildTree(idsOrder2, n,
                  "Insertion Order 2");

    /* -------------------------------------------------
       Compare BST heights
       ------------------------------------------------- */

    printf("\n========================================\n");
    printf(" INSERTION ORDER ANALYSIS\n");
    printf("========================================\n");

    int height1 = height(root1);
    int height2 = height(root2);

    printf("Height with Order 1: %d\n", height1);
    printf("Height with Order 2: %d\n", height2);

    if (height1 < height2) {
        printf("Order 1 produced a shorter BST.\n");
    }
    else if (height2 < height1) {
        printf("Order 2 produced a shorter BST.\n");
    }
    else {
        printf("Both insertion orders produced the same height.\n");
    }

    /* -------------------------------------------------
       Complexity information
       ------------------------------------------------- */

    printf("\n========================================\n");
    printf(" COMPLEXITY ANALYSIS\n");
    printf("========================================\n");

    printf("BST Search - Average case : O(log n)\n");
    printf("BST Search - Worst case   : O(n)\n");
    printf("Linear Search             : O(n)\n");
    printf("Insertion into BST        : O(log n) average\n");
    printf("Insertion into BST        : O(n) worst case\n");

    /* Free allocated memory */
    freeTree(root1);
    freeTree(root2);

    return 0;
}
