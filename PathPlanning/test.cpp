#include "pathPlanning.h"
#include <stdio.h>

int main()
{
  int list[] = {0,2,0,3,2,0,4,0,0,4,0,5,3,0,5,0};
  int start = 0;
  int goal = 2;
  int V = 4;
  int *path = calculateShortestPath(list, start, goal, V);
  for(int i=0; i<3;i++){
    printf("%d\n", path[i]);
  }
  return 0;
}