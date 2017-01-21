#include <iostream>
#include "graph.h"

using namespace std;

int main() {

  Graph graph;

  graph.appendEdge(1, 1, 1, 2);
  graph.appendEdge(1, 1, 2, 3);

  graph.appendEdge(1, 1, 1, 4);
  graph.appendEdge(1, 1, 2, 5);
  graph.appendEdge(1, 1, 3, 6);

  graph.appendEdge(1, 1, 4, 5);
  graph.appendEdge(1, 1, 5, 6);

  cout << graph.nodeTotal() << endl;

  int *adjMat = graph.getAdjMat();


  cout << adjMat[3] << endl;


  return 0;
}
