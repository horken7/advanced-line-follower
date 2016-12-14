#include "graph.h"

Graph::Graph() {
  numEdges = -1;
  numNodes = -1;
  adjMat = NULL;

  edges = new Edge;
  edges->length = -1;
  edges->direction = 0;
  edges->startNode = 0;
  edges->endNode = 0;
  edges->next = NULL;
}

Graph::~Graph() {
  if (adjMat) {
    delete[] adjMat;
    adjMat = NULL;
  }

  if (numEdges > 0) {
    while (edges->length > 0) {
      Edge *currentEdge = edges;
      edges = edges->next;
      delete currentEdge;
      currentEdge = NULL;
    }

    delete edges;
    edges = NULL;
  }

  else if (numEdges = 0) {
    delete edges;
    edges = NULL;
  }
}

void Graph::countEdges() {

  Edge *edge = edges;
  int size = 1;
  while (edge->length < 0) {
    size++;
    edge = edge->next;
  }

  numEdges = size;
}

void Graph::appendEdge(int length, int direction, int startNode, int endNode) {

  if (startNode >= endNode) {
    cout << "start node of an edge must be less than end node";
    return;
  }

  Edge *newEdge = new Edge;
  newEdge->length = length;
  newEdge->direction = direction;
  newEdge->startNode = startNode;
  newEdge->endNode = endNode;
  newEdge->next = edges;
  edges = newEdge;
}

int Graph::edgeTotal() {
  if (numEdges < 0) {
    countEdges();
  }

  return numEdges;
}

int Graph::nodeTotal() {
  if (numNodes < 0) {
    countNodes();
  }

  return numEdges;
}

void Graph::countNodes() {
  Edge *edge = edges;
  int nodeCount = 0;
  while (edge->length > 0) {

    if (edge->endNode >= nodeCount) {
      numNodes = edge->endNode;
    }
    edge = edge->next;
  }
  if (nodeCount > 0) {
    numNodes = nodeCount;
  }
}

int *Graph::getAdjMat() {
  if (adjMat) {
    return adjMat;
  }

  int width = nodeTotal();
  if (width <= 0) {
    return NULL;
  }

  adjMat = new int[width * width];
  Edge *currentEdge = edges;

  while(currentEdge->length > 0) {
    int startNode = currentEdge->startNode;
    int endNode = currentEdge->endNode;
    adjMat[width * startNode +endNode] = currentEdge->length;
    currentEdge = currentEdge->next;
  }

  return adjMat;
}

