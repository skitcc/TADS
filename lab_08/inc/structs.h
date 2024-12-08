#ifndef STRUCTS_H
#define STRUCTS_H

#define MAX_NODES 100

typedef struct Edge 
{
    int to;
    int weight;
    struct Edge* next;
} Edge;

typedef struct Graph 
{
    Edge* adj[MAX_NODES];
    int numNodes;
} Graph;

typedef struct KruskalEdge 
{
    int from;
    int to;
    int weight;
} KruskalEdge;

#endif