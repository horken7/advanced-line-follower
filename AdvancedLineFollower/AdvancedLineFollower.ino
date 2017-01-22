#include "AdvancedLineFollowerFunctions.h"
#include "graph.h"
#include "pathPlanning.h"

//Graph graph;

void setup() {
  calibrate_sensors();
  Serial.begin (9600);
  initialPrint(); // Optional, label columns in potential .csv export
  
}

void loop() 
{
  navigator();
  
}

void navigator()
{
  Graph graph;

  graph.appendEdge(1, 2, 1, 2);
  graph.appendEdge(2, 1, 1, 3);

  graph.appendEdge(3, 2, 3, 4);

  graph.appendEdge(7, 1, 2, 4);
  graph.appendEdge(5, 3, 2, 5);


  int x = graph.nodeTotal();

  int *adjMat = graph.getAdjMat();

  int start = 1;
  int goal = 5;

  int *path = calculateShortestPath(adjMat, start, goal, x);

  Edge[] theMap = getDirectionsCart(path);

  int i = 0;
  nextTurn = 0;
  while(nextTurn>0)
  {
    followSegment();
    nextTurn = theMap[i];
    i++;
  }
  
}
