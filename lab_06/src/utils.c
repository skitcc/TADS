#include "utils.h"


void free_tree(node_t *root)
{
    if (root)
    {
        free_tree(root->left);
        free_tree(root->right);
        free(root->value);
        free(root);
    }
}

void print_tree(node_t *root, int depth, const char *relation) 
{
    if (root) 
    {
        for (int i = 0; i < depth; i++) 
            printf("  ");
        printf("[%s] %s\n", relation, root->value);

        // Рекурсивно вызываем для левого потомка
        print_tree(root->left, depth + 1, "son");

        // Рекурсивно вызываем для правого брата
        print_tree(root->right, depth, "brother");
    }
}


void debug_tree_structure(node_t *root)
{
    if (root)
    {
        printf("Node: %s\n", root->value);
        if (root->left)
            printf("  Left: %s\n", root->left->value);
        if (root->right)
            printf("  Right: %s\n", root->right->value);

        debug_tree_structure(root->left);
        debug_tree_structure(root->right);
    }
}

void print_mas(char **mas, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%s ", mas[i]);
    }
    printf("\n");
}

void free_node(node_t *node)
{
    if (node)
    {
        free(node->value);
        free(node);
        node = NULL;
    }
}


node_t *find_min(node_t *root) 
{
    while (root && root->left)
        root = root->left;
    return root;
}

void free_mas(char **mas, int len)
{
    if (mas == NULL)
        return;
    for (int i = 0; i < len; i++)
    {
        free(mas[i]);
        mas[i] = NULL;
    }
    free(mas);
}

void gen_data_file(const char *filename, int len)
{
    srand(time(NULL));

    FILE *file = fopen(filename, "w");

    if (!file)
        return;
    for (int i = 0; i < len; i++)
    {
        int x = 1 + rand() % (500 - 1 + 1);

        fprintf(file, "%d\n", x);
    }

    fclose(file);
}

int clean_file(const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL) 
        return 1;
    fclose(file);
    return 0;
}


