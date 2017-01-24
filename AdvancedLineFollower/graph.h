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
  Graph();
  ~Graph();
  void appendEdge(int length, int direction, int startNode, int endNode);
  int edgeTotal();
  int nodeTotal();
  int * getAdjMat();
  void getDirectionCart(int prevNode, int curNode, int nextNode);




  private:
  Edge *edges;
  int numEdges;
  int numNodes;
  void countEdges();
  void countNodes();
  int *adjMat;
};

#endif /*GRAPH_H*/
