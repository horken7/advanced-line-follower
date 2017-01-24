#include <iostream>
#include <stdio.h>
#include "graph.h"
#include "pathPlanning.h"

using namespace std;

int main() {

  Graph graph;

  graph.appendEdge(100, 2, 1, 2);
  graph.appendEdge(2, 1, 1, 3);

  graph.appendEdge(3, 2, 3, 4);

  graph.appendEdge(7, 1, 2, 4);
  graph.appendEdge(5, 3, 2, 5);


  int x = graph.nodeTotal();

  int *adjMat = graph.getAdjMat();

  int start = 1;
  int goal = 5;

  int *path2 = calculateShortestPath(adjMat, start, goal, x);

  for (int i = 0; i < 6; i++)
  {
  	printf("%d\n", path2[i]);
  }
  cout << "---------------------------------------\n";
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

  for (int i = 1; i <= path2[0]; i++) {
    if (i == 1) {
      graph.getDirectionCart(2, path2[i], path2[i + 1]);
    }
    else {
      graph.getDirectionCart(path2[i - 1], path2[i], path2[i + 1]);
    }
  }


  return 0;
}
