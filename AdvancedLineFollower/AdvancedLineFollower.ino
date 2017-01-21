#include "AdvancedLineFollowerFunctions.h"
//#include "graph.h"
//#include "pathPlanning.h"

//Graph graph;

void setup() {
  calibrate_sensors();
  Serial.begin (9600);
  initialPrint(); // Optional, label columns in potential .csv export
  
}

void loop() 
{
  followSegment();
  intersection();
  turn('L');
}

void navigator()
{
  /*
  graph.appendEdge(2,1,0,1);
  graph.appendEdge(4,1,1,2);
  graph.appendEdge(3,1,0,3);
  graph.appendEdge(5,1,2,3);
  int size = graph.nodeTotal();
  /*int *adjMtx = graph.getAdjMat();
  for(int i=0; i<3;i++){
    Serial.print(path[i]);
  }
  */
}
