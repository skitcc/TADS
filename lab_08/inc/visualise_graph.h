#ifndef VISUALISE_GRAPH_H
#define VISUALISE_GRAPH_H



#include <stdio.h> 
#include <stdlib.h>

#include "structs.h"
#include "definitions.h"


void export_graph(Graph* graph, const char* filename);
void export_mst(KruskalEdge* mstEdges, int edgeCount, const char* filename);

#endif