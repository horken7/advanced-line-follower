#include <iostream>
#include <vector>

#include "graph.h"

using namespace std;
// Directions N=1, E=2, S=3, W=4

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

  countEdges();
  countNodes();
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

  else if (numEdges == 0) {
    delete edges;
    edges = NULL;
  }
}

void Graph::countEdges() {
  Edge *edge = edges;
  int size = 0;
  while (edge->length > 0 && edge->next != NULL) {
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
  countEdges();
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

  return numNodes;
}

void Graph::countNodes() {
  Edge *edge = edges;
  int nodeCount = 0;
  while (edge->length > 0 && edge->next != NULL) {

    if (edge->endNode >= nodeCount) {
      nodeCount = edge->endNode;
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
  for (int i = 0; i < (width * width); i++) {
    adjMat[i] = 0;
  }
  Edge *currentEdge = edges;

  while (currentEdge->length > 0) {
    int startNode = currentEdge->startNode;
    int endNode = currentEdge->endNode;
    adjMat[width * (startNode - 1) + endNode - 1] = currentEdge->length;
    adjMat[width * (endNode - 1) + startNode - 1] = currentEdge->length;

    currentEdge = currentEdge->next;
  }

  return adjMat;
}

void Graph::getDirectionCart(int prevNode, int curNode, int nextNode) {
  // prevNode = 4;
  // curNode = 2;
  // nextNode = 1;

  bool negCurrentHeading = false;
  bool negNewHeading = false;

  if (curNode < prevNode) {
    negCurrentHeading = true;
  }

  if (nextNode < curNode) {
    negNewHeading = true;
  }

  int currentHeading = 0;
  int newHeading = 0;

  Edge *edge = edges;
  if (negCurrentHeading && negNewHeading) {
    // serach for current node as the start node for current heading
    // serach for next node as the start node for new heading
    int completeSearch = 0;
    while (edge->length > 0) {
      if (edge->startNode == curNode && edge->endNode == prevNode) {
        currentHeading = (edge->direction + 1 % 4) + 1;
        completeSearch++;
      }

      else if (edge->startNode == nextNode && edge->endNode == curNode) {
        newHeading = (edge->direction + 1 % 4) + 1;
        completeSearch++;
      }

      else if (completeSearch >= 2) {
        break;
      }
      edge = edge->next;
    }
  }

  else if (negCurrentHeading && !negNewHeading) {
    // serach for current node as the start node for current heading
    // serach for current node as the start node for new heading
    int completeSearch = 0;
    while (edge->length > 0) {
      if (edge->startNode == curNode && edge->endNode == prevNode) {
        currentHeading = (edge->direction + 1 % 4) + 1;
        completeSearch++;
      }

      else if (edge->startNode == curNode && edge->endNode == nextNode) {
        newHeading = edge->direction;
        completeSearch++;
      }

      else if (completeSearch >= 2) {
        break;
      }
      edge = edge->next;
    }
  }

  else if (!negCurrentHeading && negNewHeading) {
    // serach for prev node as the start node for current heading
    // serach for next node as the start node for new heading
    int completeSearch = 0;
    while (edge->length > 0) {
      if (edge->startNode == prevNode && edge->endNode == curNode) {
        currentHeading = edge->direction;
        completeSearch++;
      }

      else if (edge->startNode == nextNode && edge->endNode == curNode) {
        newHeading = (edge->direction + 1 % 4) + 1;
        completeSearch++;
      }

      else if (completeSearch >= 2) {
        break;
      }
      edge = edge->next;
    }
  }

  else if (!negCurrentHeading && !negNewHeading) {
    // serach for prev node as the start node for current heading
    // serach for cur node as the start node for new heading
    int completeSearch = 0;
    while (edge->length > 0) {
      if (edge->startNode == prevNode && edge->endNode == curNode) {
        currentHeading = edge->direction;
        completeSearch++;
      }

      else if (edge->startNode == curNode && edge->endNode == nextNode) {
        newHeading = edge->direction;
        completeSearch++;
      }

      else if (completeSearch >= 2) {
        break;
      }
      edge = edge->next;
    }
  }

  /**************************************************/

  switch (currentHeading) {
  case 1: {
    switch (newHeading) {
    case 1: {
      cout << "Straight \n";
      break;
    }

    case 2: {
      cout << "Right \n";
      break;
    }

    case 3: {
      cout << "Back\n";
      break;
    }

    case 4: {
      cout << "left \n";
      break;
    }

    default:
      cout << "STOP\n";
      break;
    }
    break;
  }

  case 2: {
    switch (newHeading) {
    case 1: {
      cout << "Left \n";
      break;
    }

    case 2: {
      cout << "Straight \n";
      break;
    }

    case 3: {
      cout << "Right \n";
      break;
    }

    case 4: {
      cout << "Back \n";
      break;
    }

    default:
      cout << "STOP\n";
      break;
    }
    break;
  }
  case 3: {
    switch (newHeading) {
    case 1: {
      cout << "Back \n";
      break;
    }

    case 2: {
      cout << "Left \n";
      break;
    }

    case 3: {
      cout << "Straight \n";
      break;
    }

    case 4: {
      cout << "Right \n";
      break;
    }

    default:
      cout << "STOP\n";
      break;
    }
    break;
  }
  case 4: {
    switch (newHeading) {
    case 1: {
      cout << "Right \n";
      break;
    }

    case 2: {
      cout << "Back \n";
      break;
    }

    case 3: {
      cout << "Left \n";
      break;
    }

    case 4: {
      cout << "Straight \n";
      break;
    }

    default:
      cout << "STOP\n";
      break;
    }
    break;
  }

  default: {
    cout << "STOP\n";
    break;
  }
  }
}
