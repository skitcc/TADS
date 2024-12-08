#include "graph_operations.h"

Graph* create_graph(int numNodes) 
{
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numNodes = numNodes;
    for (int i = 0; i < numNodes; i++) {
        graph->adj[i] = NULL;
    }
    return graph;
}

void add_edge(Graph* graph, int from, int to, int weight) 
{
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    edge->to = to;
    edge->weight = weight;
    edge->next = graph->adj[from];
    graph->adj[from] = edge;
}

Graph* read_graph_from_file(const char* filename, int *count) 
{
    FILE* file = fopen(filename, "r");
    if (!file) 
    {
        return NULL;
    }

    int n, m;
    fscanf(file, "%d %d", &n, &m);

    Graph* graph = create_graph(n);
    for (int i = 0; i < m; i++) 
    {
        int u, v, w;
        if (fscanf(file, "%d %d %d", &u, &v, &w) != 3)
        {
            fclose(file);
            return NULL;
        }
        (*count)++;
        add_edge(graph, u, v, w);
    }

    fclose(file);
    return graph;
}

void dfs(Graph* graph, int current, int target, int currentWeight, bool* visited, int* maxWeight, int* path, int pathIndex, int* bestPath, int* bestPathLength) 
{
    path[pathIndex] = current;

    if (current == target) {
        if (currentWeight > *maxWeight) {
            *maxWeight = currentWeight;
            *bestPathLength = pathIndex + 1;
            for (int i = 0; i <= pathIndex; i++) {
                bestPath[i] = path[i];
            }
        }
        return;
    }

    visited[current] = true;

    Edge* edge = graph->adj[current];
    while (edge != NULL) {
        if (!visited[edge->to]) {
            dfs(graph, edge->to, target, currentWeight + edge->weight, visited, maxWeight, path, pathIndex + 1, bestPath, bestPathLength);
        }
        edge = edge->next;
    }

    visited[current] = false;
}

void find_max_paths(Graph* graph) 
{
    for (int i = 0; i < graph->numNodes; i++) 
    {
        for (int j = 0; j < graph->numNodes; j++) 
        {
            if (i != j) {
                bool visited[MAX_NODES] = {false};
                int maxWeight = INT_MIN;
                int path[MAX_NODES], bestPath[MAX_NODES];
                int bestPathLength = 0;

                dfs(graph, i, j, 0, visited, &maxWeight, path, 0, bestPath, &bestPathLength);

                if (maxWeight > INT_MIN) 
                {
                    printf("Максимальный путь между %d и %d: %d\n", i, j, maxWeight);
                    printf("Путь: ");
                    for (int k = 0; k < bestPathLength; k++) 
                    {
                        printf("%d", bestPath[k]);
                        if (k < bestPathLength - 1) 
                        {
                            printf(" -> ");
                        }
                    }
                    printf("\n");
                } else 
                {
                    printf("Между %d и %d пути не существует.\n", i, j);
                }
            }
        }
    }
}

Graph* invert_graph(Graph* graph) 
{
    Graph* inverted = create_graph(graph->numNodes);
    for (int i = 0; i < graph->numNodes; i++) {
        Edge* edge = graph->adj[i];
        while (edge != NULL) {
            add_edge(inverted, edge->to, i, edge->weight);
            edge = edge->next;
        }
    }
    return inverted;
}

void dfs_reachability(Graph* graph, int current, bool* visited) 
{
    visited[current] = true;
    Edge* edge = graph->adj[current];
    while (edge != NULL) {
        if (!visited[edge->to]) 
        {
            dfs_reachability(graph, edge->to, visited);
        }
        edge = edge->next;
    }
}

bool is_graph_connected(Graph* graph) 
{
    bool visited[MAX_NODES] = {false};

    dfs_reachability(graph, 0, visited);
    for (int i = 0; i < graph->numNodes; i++) 
    {
        if (!visited[i]) {
            return false;
        }
    }

    Graph* inverted = invert_graph(graph);
    for (int i = 0; i < graph->numNodes; i++) {
        visited[i] = false;
    }
    dfs_reachability(inverted, 0, visited);
    for (int i = 0; i < graph->numNodes; i++) 
    {
        if (!visited[i]) {
            return false;
        }
    }

    return true;
}

int compare_edges(const void* a, const void* b) 
{
    return ((KruskalEdge*)a)->weight - ((KruskalEdge*)b)->weight;
}

int find_set(int* parent, int v) 
{
    if (parent[v] != v) 
        parent[v] = find_set(parent, parent[v]);
    return parent[v];
}

void union_sets(int* parent, int* rank, int u, int v) 
{
    u = find_set(parent, u);
    v = find_set(parent, v);
    if (u != v) {
        if (rank[u] < rank[v]) {
            parent[u] = v;
        } else if (rank[u] > rank[v]) {
            parent[v] = u;
        } else {
            parent[v] = u;
            rank[u]++;
        }
    }
}

int kruskal_MST(Graph* graph) 
{
    KruskalEdge edges[MAX_NODES * MAX_NODES];
    int edgeCount = 0;

    for (int i = 0; i < graph->numNodes; i++) {
        Edge* edge = graph->adj[i];
        while (edge != NULL) {
            edges[edgeCount++] = (KruskalEdge){i, edge->to, edge->weight};
            edge = edge->next;
        }
    }

    qsort(edges, edgeCount, sizeof(KruskalEdge), compare_edges);

    int parent[MAX_NODES], rank[MAX_NODES];
    for (int i = 0; i < graph->numNodes; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    KruskalEdge mstEdges[MAX_NODES];
    int mstEdgeCount = 0;

    int mstWeight = 0;
    for (int i = 0; i < edgeCount; i++) {
        int u = edges[i].from;
        int v = edges[i].to;
        int weight = edges[i].weight;

        if (find_set(parent, u) != find_set(parent, v)) {
            mstWeight += weight;
            mstEdges[mstEdgeCount++] = edges[i];
            union_sets(parent, rank, u, v);
        }
    }
    export_mst(mstEdges, mstEdgeCount, "./data/mst.dot");

    return mstWeight;
}
