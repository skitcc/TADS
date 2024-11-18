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


node_t *delete_node(node_t *node)
{
    if (node == NULL)
        return NULL;

    if (node->left == NULL)
    {
        node_t *temp = node->right;
        free_node(node);
        return temp;
    }
    else if (node->right == NULL)
    {
        node_t *temp = node->left;
        free_node(node);
        return temp;
    }

    else if (node->left == NULL && node->right == NULL)
    {
        free_node(node);
        return NULL;
    }

    else
    {
        node_t *min_node = find_min(node->right);
        free(node->value);
        node->value = strdup(min_node->value);
        node->right = delete_node(min_node);
        return node;
    }
}


node_t *search_node(node_t *node, const char *value)
{
    if (node == NULL)
        return NULL;

    int diff = strcmp(value, node->value);

    if (diff == 0)
        return node;
    else if (diff < 0)
        return search_node(node->left, value);
    else
        return search_node(node->right, value);
}


void prefix_traversal(node_t *root, bool is_measuring)
{
    if (root)
    {
        if (!is_measuring)
            printf("%s ", root->value);
        prefix_traversal(root->left, is_measuring);
        prefix_traversal(root->right, is_measuring);
    }
}

void infix_traversal(node_t *root, bool is_measuring)
{
    if (root)
    {
        infix_traversal(root->left, is_measuring);   
        if (!is_measuring)
            printf("%s ", root->value);              
        infix_traversal(root->right, is_measuring);
    }
}

void postfix_traversal(node_t *root, bool is_measuring)
{
    if (root)
    {
        postfix_traversal(root->left, is_measuring);   
        postfix_traversal(root->right, is_measuring);  
        if (!is_measuring)
            printf("%s ", root->value);                
    }
}
