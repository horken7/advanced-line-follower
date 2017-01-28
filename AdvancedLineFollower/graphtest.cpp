#include <iostream>
#include <stdio.h>
#include "graph.h"
#include "pathPlanning.h"

using namespace std;

void mapper();
int main() {

  Graph graph;

  // graph.addNewNode(3, 1);
  graph.addNewNode(2, 2);

  // graph.appendEdge(1, 1, 1, 2);
  // graph.setNodeType(2, 3);
  // graph.appendEdge(1, 1, 3, 5);

  // graph.appendEdge(1, 2, 2, 4);
  // graph.appendEdge(1, 2, 1, 3);

  cout << "Stats:\n";
  

  //graph.stats();
 // \\ graph.mergeNodes();


  return 0;
}

void mapper() {
  cout << "-------------------------------------------\n";
  cout << "Mapping\n";
  /*
    Variables:
    current direction
    previous node
    current node

    next node = getLowHangingNode()

    Loop:
    Goto next node
  */
  // addNewNode()
  // appendEdge()
}

// graph.appendEdge(1, 1, 1, 2);
// graph.appendEdge(1, 2, 2, 4);

// graph.appendEdge(1, 1, 4, 7);

// graph.appendEdge(1, 2, 3, 6);
// graph.appendEdge(1, 1, 2, 3);

// graph.appendEdge(1, 4, 2, 5);




// for (int i = 0; i < 7; i++) {
//   graph.incTempNodeNum();
// }

// for (int i = 0; i < 7; i++) {
//   graph.setNodeHanging(i + 1, false);
//   graph.setNodeType(i + 1, 2);
// }
// graph.setNodeType(5, 1);
// graph.setNodeType(1, 1);
// graph.setNodeType(2, 4);

// graph.setNodeHanging(6, true);
// graph.setNodeHanging(7, true);
