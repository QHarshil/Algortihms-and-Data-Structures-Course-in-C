#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include "adjlist.h"
#include "cities.h"
#include "dijkstra.h"

/**
 * Main program
 */
int main(int argc, char* argv[]) {

    char* fileNameCities = NULL;
    char* fileNameDistances = NULL;
    char* cityFrom = NULL;
    char* cityTo = NULL;

    // This code is provided to read the command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0) {
            if (i + 1 < argc) {
                fileNameCities = argv[++i];
            } else {
                printf("Missing argument for -c\n");
                return 1;
            }
        } else if (strcmp(argv[i], "-d") == 0) {
            if (i + 1 < argc) {
                fileNameDistances = argv[++i];
            } else {
                printf("Missing argument for -d\n");
                return 1;
            }
        } else if (strcmp(argv[i], "-f") == 0) {
            if (i + 1 < argc) {
                cityFrom = argv[++i];
            } else {
                printf("Missing argument for -f\n");
                return 1;
            }
        } else if (strcmp(argv[i], "-t") == 0) {
            if (i + 1 < argc) {
                cityTo = argv[++i];
            } else {
                printf("Missing argument for -t\n");
                return 1;
            }
        } else {
            printf("Unknown argument: %s\n", argv[i]);
            return 1;
        }
    }

    if (!fileNameCities || !fileNameDistances || !cityFrom || !cityTo) {
        printf("Usage: %s -c <cities_file> -d <distances_file> -f <city_from> -t <city_to>\n", argv[0]);
        return 1;
    }

// Initialize the graph
    Graph* graph = readCities(fileNameCities);
    if (!graph) {
        printf("Failed to create graph from cities file.\n");
        return 1;
    }

    readDistances(graph, fileNameDistances);

    // Find the indices for cityFrom and cityTo
    int fromIndex = -1, toIndex = -1;
    for (int i = 0; i < graph->numVertices; i++) {
        if (strcmp(graph->cities[i], cityFrom) == 0) fromIndex = i;
        if (strcmp(graph->cities[i], cityTo) == 0) toIndex = i;
    }

    if (fromIndex == -1 || toIndex == -1) {
        printf("One of the specified cities was not found in the graph.\n");
        freeGraph(graph);
        return 1;
    }
    
    DijkstraResult result = dijkstra(graph, fromIndex, toIndex);
    
    if (result.pathSize == 0 || result.distance == INT_MAX) {
        printf("No path found from %s to %s\n", cityFrom, cityTo);    
    } else {
        printf("Origin: %s\nDestination: %s\nDistance: %d\nPath cities:\n", 
                graph->cities[fromIndex], graph->cities[toIndex], result.distance);
        for (int i = 0; i < result.pathSize; i++) {
            printf("%s\n", graph->cities[result.path[i]]);
        }
        free(result.path);
    } 
    freeGraph(graph);

    return 0;
}
