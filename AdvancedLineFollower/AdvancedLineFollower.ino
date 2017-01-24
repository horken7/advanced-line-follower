#include "AdvancedLineFollowerFunctions.h"
#include "graph.h"
#include "pathPlanning.h"


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

  graph.appendEdge(100, 2, 1, 2);
  graph.appendEdge(2, 1, 1, 3);

  graph.appendEdge(3, 2, 3, 4);

  graph.appendEdge(7, 1, 2, 4);
  graph.appendEdge(5, 3, 2, 5);


  int x = graph.nodeTotal();

  int *adjMat = graph.getAdjMat();

  int start = 3;
  int goal = 1;
  int initialState = 1;

  int *path = calculateShortestPath(adjMat, start, goal, x);
  int nrEdges = path[0];
  for(int i = 0; i<= nrEdges; i++){
    Serial.println(path[i]);
    }

  followSegment();
  
  for (int i = 1; i <= nrEdges; i++) {
    if (i == 1) {
      graph.getDirectionCart(initialState, path[i], path[i + 1]);
    }
    else {
      graph.getDirectionCart(path[i - 1], path[i], path[i + 1]);
    }
    followSegment();
  }
}
