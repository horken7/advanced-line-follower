#include "graph.h"

const int INT_MAX = 999999999;

int minDistance(int *dist, bool *sptSet, int V);

int countPath(int *previous, int start, int goal);

int * getPath(int *previous, int start, int goal);

void dijkstra(int *graph, int src, int V, int *dist, int *previous);

int *calculateShortestPath(int *graph, int start, int goal, int V);