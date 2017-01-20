#include "pathPlanning.h"
#include "graph.h"
#include <stdio.h>

#include <iostream> 

int main()
{

  Graph graph;
  graph.appendEdge(2,1,0,1);
  graph.appendEdge(4,1,1,2);
  graph.appendEdge(3,1,0,3);
  graph.appendEdge(5,1,2,3);
  int *test = graph.getAdjMat();
  graph.edgeTotal();
/*
  int list[] = {0,2,0,3,2,0,4,0,0,4,0,5,3,0,5,0};
  int start = 0;
  int goal = 2;
  int V = 4;
  int *path = calculateShortestPath(list, start, goal, V);
  for(int i=0; i<3;i++){
    printf("%d\n", path[i]);
  }
  */
  return 0;
}