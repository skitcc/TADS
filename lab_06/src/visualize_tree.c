#include <stdio.h>
#include "tree_operations.h"

void generate_dot(node_t *root, FILE *file)
{
    if (root == NULL)
        return;

    // Печатаем текущий узел
    if (root->left)
        fprintf(file, "    \"%s\" -> \"%s\";\n", root->value, root->left->value);
    if (root->right)
        fprintf(file, "    \"%s\" -> \"%s\" [style=dashed];\n", root->value, root->right->value);

    // Рекурсивно вызываем для дочернего и соседнего узлов
    generate_dot(root->left, file);
    generate_dot(root->right, file);
}

void export_to_dot(node_t *root, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        perror("Failed to open file");
        return;
    }

    fprintf(file, "digraph Tree {\n");
    fprintf(file, "    node [shape=circle];\n");
    generate_dot(root, file);
    fprintf(file, "}\n");

    fclose(file);
}
