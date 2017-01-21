#include <iostream>
#include "graph.h"

using namespace std;

int main() {

  Graph graph;

  graph.appendEdge(1, 2, 1, 2);
  graph.appendEdge(2, 1, 1, 3);

  graph.appendEdge(3, 2, 3, 4);

  graph.appendEdge(4, 1, 2, 4);
  graph.appendEdge(5, 3, 2, 5);


  int x = graph.nodeTotal();

  int *adjMat = graph.getAdjMat();

  cout << "Adj Mat =   \n";

  for (int i = 0; i < (x * x); i++) {
    if (i % 5 == 0 ) {
      cout << endl;
      cout << "      ";
    }

    cout << adjMat[i] << "  ";
  }

  cout << endl;
  cout << "---------------------------------------\n";

  int path[6] = {2, 1, 3, 4, 2, 3};
  //prebious node = 4;
  //current node = 2;

  for (int i = 0; i < 5; i++) {
    if (i == 0) {
      graph.getDirectionCart(4, path[i], path[i + 1]);
    }
    else {
      graph.getDirectionCart(path[i - 1], path[i], path[i + 1]);
    }
  }



  return 0;
}
