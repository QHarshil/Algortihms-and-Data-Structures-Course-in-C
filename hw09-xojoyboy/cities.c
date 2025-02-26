#include "cities.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Duplicates a string by allocating memory and copying the content.
 * 
 * Parameters:
 * s - The string to duplicate.
 *
 * Returns:
 * A pointer to the duplicated string or NULL if memory allocation fails.
 */
char* my_strdup(const char* s) {
    size_t len = strlen(s) + 1;
    char* newStr = (char*)malloc(len);
    if (newStr) {
        memcpy(newStr, s, len);
    }
    return newStr;
}

/**
 * Populates a graph with cities read from a file. Assumes a graph size of 100.
 * 
 * Parameters:
 * fileNameCities - The name of the file containing city names, one per line.
 *
 * Returns:
 * A pointer to the graph populated with cities or NULL if the file cannot be opened.
 */
Graph* readCities(char* fileNameCities) {
    FILE* file = fopen(fileNameCities, "r");
    if (!file) {
        printf("Cannot open file %s\n", fileNameCities);
        return NULL;
    }

    Graph* graph = createGraph(100);
    char city[256];
    int index = 0;
    while (fscanf(file, "%s", city) == 1 && index < graph->numVertices) {
        graph->cities[index] = my_strdup(city);
        index++;
    }

    fclose(file);
    graph->numVertices = index; // Adjust the number of vertices based on the actual cities read
    return graph;
}

/**
 * Reads distances between cities from a file and updates the graph with edges representing these distances.
 * 
 * Parameters:
 * graph - The graph to which edges will be added.
 * fileNameDistances - The name of the file containing distances between cities.
 *
 * Remarks:
 * The file format is expected to be 'city1 city2 distance'. Each valid line results in an edge added to the graph.
 * If the graph is intended to be undirected, edges are added in both directions.
 */
void readDistances(Graph* graph, char* fileNameDistances) {
    FILE* file = fopen(fileNameDistances, "r");
    if (!file) {
        printf("Cannot open file %s\n", fileNameDistances);
        return;
    }

    char src[256], dest[256];
    int distance;
    while (fscanf(file, "%s %s %d", src, dest, &distance) == 3) {
        int srcIndex = -1, destIndex = -1;
        for (int i = 0; i < graph->numVertices; i++) {
            if (strcmp(graph->cities[i], src) == 0) srcIndex = i;
            if (strcmp(graph->cities[i], dest) == 0) destIndex = i;
        }
        if (srcIndex != -1 && destIndex != -1) {
            // Add a directed edge from src to dest
            addEdge(graph, srcIndex, destIndex, distance);
        }
    }

    fclose(file);
}
 

