#ifndef ADJLIST_H
#define ADJLIST_H

#include <stdbool.h>

typedef struct EdgeNode {
    int dest; // Index in the graph's array of cities
    int distance;
    struct EdgeNode* next;
} EdgeNode;

typedef struct {
    EdgeNode* head; // head of the list of edges
} AdjList;

typedef struct {
    int numVertices;
    char** cities; // Array of city names
    AdjList* array; // Array of lists
} Graph;

Graph* createGraph(int numVertices);
void addEdge(Graph* graph, int src, int dest, int distance);
void freeGraph(Graph* graph);

#endif

