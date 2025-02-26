#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "dijkstra.h"
/**
 * Performs Dijkstra's algorithm to find the shortest path and distance from a start vertex to a target vertex in a graph.
 * 
 * Parameters:
 *  - graph: Pointer to the graph.
 *  - startVertex: Index of the start vertex.
 *  - targetVertex: Index of the target vertex.
 * 
 * Returns:
 *  - DijkstraResult containing the shortest distance and path. The path is a dynamically allocated array of vertex indices,
 *    which must be freed by the caller. If no path is found or if an allocation fails, returns a result with pathSize set to -1.
 */
DijkstraResult dijkstra(Graph* graph, int startVertex, int targetVertex) {
    int V = graph->numVertices;
    int* dist = (int*)malloc(V * sizeof(int));
    int* prev = (int*)malloc(V * sizeof(int));
    bool* sptSet = (bool*)malloc(V * sizeof(bool));

    // Check for memory allocation failure
    if (!dist || !prev || !sptSet) {
        // Free already allocated memory
        free(dist);
        free(prev);
        free(sptSet);
        DijkstraResult errorResult = {0, NULL, -1};
        return errorResult;
    }

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
        sptSet[i] = false;
    }
    dist[startVertex] = 0;

    for (int count = 0; count < V - 1; count++) {
        int minDistance = INT_MAX, u = -1;
        
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && dist[v] < minDistance) {
                minDistance = dist[v], u = v;
            }
        }

        if (u == -1) break; // No more vertices to process
        
        sptSet[u] = true;

        for (EdgeNode* node = graph->array[u].head; node != NULL; node = node->next) {
            int v = node->dest;
            if (!sptSet[v] && dist[u] + node->distance < dist[v]) {
                dist[v] = dist[u] + node->distance;
                prev[v] = u;
            }
        }
    }

    free(sptSet);

    int tempPath[V], pathIndex = 0;
    for (int at = targetVertex; at != -1; at = prev[at]) {
        tempPath[pathIndex++] = at;
    }

    DijkstraResult result = {dist[targetVertex], NULL, 0};
    if (dist[targetVertex] != INT_MAX) { // Path exists
        result.pathSize = pathIndex;
        result.path = (int*)malloc(pathIndex * sizeof(int));
        if (!result.path) {
            // Handle memory allocation failure for the path
            free(dist);
            free(prev);
            result.pathSize = -1; // Indicate an error
            return result;
        }
        for (int i = 0; i < pathIndex; i++) {
            result.path[i] = tempPath[pathIndex - i - 1]; // Reverse path
        }
    }

    free(dist);
    free(prev);
    return result;
}
    

