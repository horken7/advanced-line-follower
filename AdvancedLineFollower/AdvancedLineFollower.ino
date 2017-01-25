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
  //followSegment();
  //turn('L');

  navigator();
}

void navigator()
{
  Graph graph;

  // graph.appendEdge(weight, state, start, goal);
  graph.appendEdge(1, 2, 1, 2);
  graph.appendEdge(2, 2, 2, 3);
  graph.appendEdge(3, 3, 1, 4);
  graph.appendEdge(4, 3, 2, 5);
  graph.appendEdge(5, 3, 3, 6);
  graph.appendEdge(6, 2, 4, 5);
  graph.appendEdge(7, 2, 5, 6);
  graph.appendEdge(8, 3, 4, 7);
  graph.appendEdge(9, 3, 5, 8);
  graph.appendEdge(10, 3, 6, 9);
  graph.appendEdge(11, 2, 7, 8);
  graph.appendEdge(12, 2, 8, 9);
  

  int x = graph.nodeTotal();

  int *adjMat = graph.getAdjMat();

  int start = 1;
  int goal = 9;
  int initialState = 2;

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

