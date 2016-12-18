#include "AdvancedLineFollowerFunctions.h"
//#include "graph.h"

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
  graph.appendEdge(1,1,0,1);
  graph.appendEdge(1,1,0,2);
  graph.appendEdge(1,1,1,2);
  graph.appendEdge(1,1,2,3);
  */
}
