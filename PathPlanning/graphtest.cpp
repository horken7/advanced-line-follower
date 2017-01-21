#include <iostream>
#include "graph.h"

using namespace std;

int main() {

  Graph graph;

  graph.appendEdge(1, 1, 1, 2);
  graph.appendEdge(2, 1, 1, 3);

  graph.appendEdge(3, 1, 2, 3);
  graph.appendEdge(4, 1, 2, 4);


  int x = graph.nodeTotal();

  int *adjMat = graph.getAdjMat();

  cout << "Adj Mat =   \n";

  for (int i = 0; i < (x * x); i++) {
    if (i % 4 == 0 ) {
      cout << endl;
      cout << "      ";
    }

    cout << adjMat[i] << "  ";
  }

  cout << endl;
  cout << "---------------------------------------\n";



  return 0;
}
