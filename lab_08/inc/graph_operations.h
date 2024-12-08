#ifndef GRAPH_OPERATIONS_H
#define GRAPH_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "structs.h"
#include "visualise_graph.h"


Graph* read_graph_from_file(const char* filename, int *count);
Graph* create_graph(int numNodes);
void add_edge(Graph* graph, int from, int to, int weight);
void find_max_paths(Graph* graph);
int kruskal_MST(Graph* graph);
bool is_graph_connected(Graph* graph);


#endif