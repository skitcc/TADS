#include "delete_module.h"


void free_node(node_t *node)
{
    if (node)
    {
        free(node->value);
        free(node);
        node = NULL;
    }
}


static node_t *find_min(node_t *root) 
{
    while (root && root->left)
        root = root->left;
    return root;
}

// node_t *delete_node_by_value(node_t *root, const char *value)
// {
//     if (root == NULL)
//         return NULL;

//     int diff = strcmp(value, root->value);

//     if (diff < 0)
//     {
//         root->left = delete_node_by_value(root->left, value);
//     }
//     else if (diff > 0)
//     {
//         root->right = delete_node_by_value(root->right, value);
//     }
//     else
//     {
//         return delete_node(root);
//     }

//     return root;
// }


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
        free(node->value); // Освобождаем старое значение
        node->value = strdup(min_node->value); // Копируем значение
        node->right = delete_node(min_node);
        return node;
    }
}




node_t *delete_nodes_starting_with(node_t *root, char start_char) 
{
    if (root == NULL)
        return NULL;

    root->left = delete_nodes_starting_with(root->left, start_char);
    root->right = delete_nodes_starting_with(root->right, start_char);

    if (tolower(root->value[0]) == tolower(start_char)) 
        return delete_node(root);

    return root;
}


int delete_elems_starts_with(char **mas, int len, char start_char)
{

    int new_len = len;

    // Удаляем элементы и уменьшаем длину
    for (int i = 0; i < len; i++)
    {
        // printf("i : %d\n", i);
        if (mas[i] && tolower(mas[i][0]) == tolower(start_char)) 
        {
            free(mas[i]);
            mas[i] = NULL;
            new_len--;
        }
    }


    int shift = 0;
    for (int i = 0; i < len; i++)
    {
        if (mas[i] == NULL)
        {
            for (int j = i; j < len - 1; j++)
            {
                mas[j] = mas[j + 1];
            }
            // mas[len - 1] = NULL; 
            shift++;
        }
    }

    // printf("out\n");

    return new_len;
}



