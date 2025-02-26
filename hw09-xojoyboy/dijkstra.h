#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "adjlist.h"

typedef struct {
    int distance;
    int* path;
    int pathSize;
} DijkstraResult;

DijkstraResult dijkstra(Graph* graph, int startVertex, int endVertex);

#endif

