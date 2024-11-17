#include "tree_operations.h"

node_t *create_node(char *value)
{
    node_t *new_node = malloc(sizeof(node_t));
    if (!new_node)
    {
        return NULL;
    }

    new_node->value = strdup(value);
    if (!new_node->value)
    {
        
        free(new_node);
        return NULL;
    }

    free(value);
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

node_t *insert(node_t *root, char *value)
{
    if (root == NULL)
    {
        return create_node(value);
    }
    int diff = strcmp(value, root->value); 
    if (diff < 0)
        root->left = insert(root->left, value);
    if (diff > 0)
        root->right = insert(root->right, value);

    return root;
}


