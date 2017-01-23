#include "graph.h"

#ifndef PATHPLANNING_H
#define PATHPLANNING_H

// const int INT_MAX = 999999999;
// have to move def into cpp file when using iostream

int minDistance(int *dist, bool *sptSet, int V);

int countPath(int *previous, int start, int goal);

int * getPath(int *previous, int start, int goal);

void dijkstra(int *graph, int src, int V, int *dist, int *previous);

int *calculateShortestPath(int *graph, int start, int goal, int V);

#endif