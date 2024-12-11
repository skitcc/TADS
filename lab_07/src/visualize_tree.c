#include "visualize_tree.h"


bool detect_cycle(avl_t *node, avl_t **visited_nodes, int *visited_count) 
{
    if (!node) 
        return false;

    for (int i = 0; i < *visited_count; i++) {
        if (visited_nodes[i] == node) {
            return true; // Цикл найден
        }
    }

    visited_nodes[*visited_count] = node;
    (*visited_count)++;

    return detect_cycle(node->left, visited_nodes, visited_count) || 
           detect_cycle(node->right, visited_nodes, visited_count);
}

bool has_cycle(void *head) 
{
    avl_t *visited_nodes[1000]; // Ограничение на размер
    int visited_count = 0;
    return detect_cycle(head, visited_nodes, &visited_count);
}

void generate_dot(void *head, FILE *file, bool is_bst)
{
    if (head == NULL)
        return;

    if (is_bst)
    {
        bst_t *root = head;
        if (root->left)
            fprintf(file, "    \"%s\" -> \"%s\";\n", root->value, root->left->value);
        if (root->right)
            fprintf(file, "    \"%s\" -> \"%s\" [style=dashed];\n", root->value, root->right->value);
        generate_dot(root->left, file, is_bst);
        generate_dot(root->right, file, is_bst);
    }
    else
    {
        avl_t *root = head;
        
        if (root->left)
            fprintf(file, "    \"%s\" -> \"%s\";\n", root->value, root->left->value);
        if (root->right)
            fprintf(file, "    \"%s\" -> \"%s\" [style=dashed];\n", root->value, root->right->value);
        generate_dot(root->left, file, is_bst);
        generate_dot(root->right, file, is_bst);
    }
}

void export_to_dot(void *head, const char *filename, bool is_bst)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        perror("Failed to open file");
        return;
    }

    fprintf(file, "digraph Tree {\n");
    fprintf(file, "    node [shape=circle];\n");
    generate_dot(head, file, is_bst);
    fprintf(file, "}\n");
    fclose(file);

    // Генерация PNG через Graphviz
    char image[LEN_FILENAME];
    snprintf(image, LEN_FILENAME, "dot -Tpng -O %s", filename);
    int rc = system(image);
    // printf("here\n");
    if (rc == 0)
    {
        PRINT_COLOR(GREEN, "Дерево успешно визуализировано в файл");
        printf("%s %s%s!\n", GREEN, filename, RESET);
    }
}
