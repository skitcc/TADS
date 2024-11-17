#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t {
    char *value;
    struct node_t *left;
    struct node_t *right;
} node_t;

void free_tree(node_t *root) {
    if (root) {
        free_tree(root->left);  // Free left subtree
        free_tree(root->right); // Free right subtree
        free(root->value);      // Free dynamically allocated value
        free(root);             // Free current node
    }
}

int main() {
    node_t *root = malloc(sizeof(node_t));
    root->value = strdup("root_value"); // Dynamically allocate value
    root->left = malloc(sizeof(node_t));
    root->left->value = strdup("left_value");
    root->left->left = NULL;  // Initialize to NULL
    root->left->right = NULL; // Initialize to NULL

    root->right = malloc(sizeof(node_t));
    root->right->value = strdup("right_value");
    root->right->left = NULL;  // Initialize to NULL
    root->right->right = NULL; // Initialize to NULL

    // Free entire tree
    free_tree(root);

    return 0;
}
