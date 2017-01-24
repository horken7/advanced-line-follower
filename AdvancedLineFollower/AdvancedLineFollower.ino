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
  turn('L');

}

