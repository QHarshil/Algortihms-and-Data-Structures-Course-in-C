#include "adjlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Creates a graph with a specified number of vertices.
 * Initializes the adjacency list and city names for each vertex.
 *
 * Parameters:
 * numVertices - The number of vertices in the graph.
 *
 * Returns:
 * A pointer to the newly created graph.
 */
Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) {
        fprintf(stderr, "Error allocating memory for graph\n");
        return NULL;
    }

    graph->numVertices = numVertices;
    graph->array = (AdjList*)malloc(numVertices * sizeof(AdjList));
    if (!graph->array) {
        fprintf(stderr, "Error allocating memory for adjacency list array\n");
        free(graph); // Clean up previously allocated graph before returning
        return NULL;
    }

    graph->cities = (char**)malloc(numVertices * sizeof(char*));
    if (!graph->cities) {
        fprintf(stderr, "Error allocating memory for cities array\n");
        free(graph->array); // Clean up previously allocated array
        free(graph);        // Clean up graph before returning
        return NULL;
    }

    for (int i = 0; i < numVertices; i++) {
        graph->array[i].head = NULL;
        graph->cities[i] = NULL;
    }

    return graph;
}
/**
 * Adds an edge from a source vertex to a destination vertex with a given distance.
 * Updates the adjacency list of the graph accordingly.
 *
 * Parameters:
 * graph - A pointer to the graph.
 * src - The index of the source vertex.
 * dest - The index of the destination vertex.
 * distance - The distance between the source and destination vertices.
 */
void addEdge(Graph* graph, int src, int dest, int distance) {
    if (src < 0 || src >= graph->numVertices || dest < 0 || dest >= graph->numVertices) {
        fprintf(stderr, "Invalid source or destination index\n");
        return;
    }

    EdgeNode* newNode = (EdgeNode*)malloc(sizeof(EdgeNode));
    if (!newNode) {
        fprintf(stderr, "Error allocating memory for new edge node\n");
        return;
    }

    newNode->dest = dest;
    newNode->distance = distance;
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

/**
 * Frees the memory allocated for the graph, including all its vertices,
 * edges, and city names.
 *
 * Parameters:
 * graph - A pointer to the graph to be freed.
 */
void freeGraph(Graph* graph) {
    if (!graph) return;

    for (int i = 0; i < graph->numVertices; i++) {
        EdgeNode* current = graph->array[i].head;
        while (current) {
            EdgeNode* temp = current;
            current = current->next;
            free(temp);
        }
        if (graph->cities[i]) {
            free(graph->cities[i]);
        }
    }

    free(graph->array);
    free(graph->cities);
    free(graph);
}
