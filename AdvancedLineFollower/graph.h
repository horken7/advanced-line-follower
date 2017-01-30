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
  void mergeNodes();

  int getTempNodeNum();
  void incTempNodeNum();
  void decTempNodeNum();

  bool getNodeHanging(int nodeID);
  void setNodeHanging(int nodeID, bool val);

  int getNodeType(int nodeID);
  void setNodeType(int nodeID, int newNodeType);

  void addNewNode(int juncType, int currentDir);
  int getLowHangingNode();
  int getNextUnmappedEdge();

  void stats();


private:
  Edge *edges;
  bool *nodeHanging;
  int *nodeType; // change to byte
  int *unexploredEdges; // change to byte
  int *dirUnexploredEdges; // to byte ?
  int tempNodeNum;

  int numEdges;
  int numNodes;
  void countEdges();
  void countNodes();
  int *adjMat;
  bool calcNewMat;
};

#endif /*GRAPH_H*/
