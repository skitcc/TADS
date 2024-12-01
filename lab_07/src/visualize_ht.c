#include "visualise_ht.h"

void visualize_closed(closed_ht* table, const char* filename) 
{
    FILE* file = fopen(filename, "w");
    fprintf(file, "digraph ClosedHashTable {\n");
    fprintf(file, "    node [shape=record];\n");

    for (int i = 0; i < table->size; i++) 
    {
        fprintf(file, "    node%d [label=\"<f0> %d | ", i, i);
        hash_node_t* node = table->closed_table[i];
        int first = 1;

        while (node) {
            if (!first) fprintf(file, " -> ");
            fprintf(file, "%s", node->word);
            node = node->next;
            first = 0;
        }

        fprintf(file, "\"];\n");
    }

    fprintf(file, "}\n");
    fclose(file);

    char image[LEN_FILENAME];
    snprintf(image, LEN_FILENAME, "dot -Tpng -O %s", filename);
    int rc = system(image);
    printf("here\n");
    if (rc == 0)
    {
        PRINT_COLOR(GREEN, "Закрытая хэш таблица успешно визуализирована в файл");
        printf("%s %s%s!\n", GREEN, filename, RESET);
    }
}

void visualize_open(open_ht* table, const char* filename) 
{
    FILE* file = fopen(filename, "w");
    fprintf(file, "digraph OpenHashTable {\n");
    fprintf(file, "    node [shape=record];\n");

    fprintf(file, "    table [label=\"");
    for (int i = 0; i < table->size; i++) 
    {
        if (i > 0) fprintf(file, "|");
        if (table->status[i] == 1) {
            fprintf(file, "<f%d> %s", i, table->open_table[i]);
        } else {
            fprintf(file, "<f%d> NULL", i);
        }
    }
    fprintf(file, "\"];\n");

    fprintf(file, "}\n");
    fclose(file);

    char image[LEN_FILENAME];
    snprintf(image, LEN_FILENAME, "dot -Tpng -O %s", filename);
    int rc = system(image);
    printf("here\n");
    if (rc == 0)
    {
        PRINT_COLOR(GREEN, "Открытая хэш таблица успешно визуализирована в файл");
        printf("%s %s%s!\n", GREEN, filename, RESET);
    }
}
