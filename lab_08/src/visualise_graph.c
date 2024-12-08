#include "visualise_graph.h"


void export_graph(Graph* graph, const char* filename) 
{
    FILE* file = fopen(filename, "w");
    fprintf(file, "digraph G {\n");
    for (int i = 0; i < graph->numNodes; i++) {
        Edge* edge = graph->adj[i];
        while (edge != NULL) {
            fprintf(file, "    %d -> %d [label=\"%d\"];\n", i, edge->to, edge->weight);
            edge = edge->next;
        }
    }
    fprintf(file, "}\n");
    fclose(file);

    char image[LEN_FILENAME];
    snprintf(image, LEN_FILENAME, "dot -Tpng -O %s", filename);
    int rc = system(image);
    if (rc == 0)
    {
        PRINT_COLOR(GREEN, "Граф успешно визуализирован в файл");
        printf("%s %s%s!\n", GREEN, filename, RESET);
    }
}

void export_mst(KruskalEdge* mstEdges, int edgeCount, const char* filename) 
{
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Ошибка создания файла Graphviz");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "graph MST {\n");
    for (int i = 0; i < edgeCount; i++) {
        fprintf(file, "    %d -- %d [label=\"%d\"];\n", mstEdges[i].from, mstEdges[i].to, mstEdges[i].weight);
    }
    fprintf(file, "}\n");

    fclose(file);

    char image[LEN_FILENAME];
    snprintf(image, LEN_FILENAME, "dot -Tpng -O %s", filename);
    int rc = system(image);
    if (rc == 0)
    {
        PRINT_COLOR(GREEN, "Остовное дерево успешно визуализировано в файл");
        printf("%s %s%s!\n", GREEN, filename, RESET);
    }
}