#ifndef GRAPH_H
#define GRAPH_H

struct Edge {
  int length;
  int direction;
  int startNode;
  int endNode;
  Edge *next;
};

class Graph {
  public:
  void appendEdge(int length, int direction, int startNode, int endNode);
  int edgeTotal();
  int nodeTotal();
  int * getAdjMat();




  private:
  Edge *edges;
  int numEdges;
  int numNodes;
  void countEdges();
  void countNodes();
  int *adjMat;
};

#endif /*GRAPH_H*/
