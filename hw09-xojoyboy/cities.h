#ifndef CITIES_H
#define CITIES_H

#include "adjlist.h"

Graph* readCities(char* fileNameCities);
void readDistances(Graph* graph, char* fileNameDistances);

#endif

