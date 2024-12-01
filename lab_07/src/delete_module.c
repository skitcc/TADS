#include "delete_module.h"


void *delete_nodes_starting_with_non_balanced(void *head, char start_char, int *comparisons) 
{
    bst_t *root = head;
    if (root == NULL)
        return NULL;

    root->left = delete_nodes_starting_with_non_balanced(root->left, start_char, comparisons);
    root->right = delete_nodes_starting_with_non_balanced(root->right, start_char, comparisons);
    if (root->value[0] == start_char) 
    {
        (*comparisons)++;

        return delete_node_bst(root);
    }
    return root;
}

void *delete_nodes_starting_with_balanced(void *head, char start_char, int *comparisons) 
{
    avl_t *root = head;
    if (!root) 
        return NULL;

    root->left = delete_nodes_starting_with_balanced(root->left, start_char, comparisons);
    root->right = delete_nodes_starting_with_balanced(root->right, start_char, comparisons);
    if (root->value[0] == start_char) 
    {
        (*comparisons)++;

        return delete_node_avl(root);
    }
    return root;
}


