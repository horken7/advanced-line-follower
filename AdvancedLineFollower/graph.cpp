#include "graph.h"
//#include "AdvancedLineFollowerFunctions.h"
#include <iostream>
#include "pathPlanning.h"

using namespace std;
// Directions N=1, E=2, S=3, W=4

Graph::Graph() {
  numEdges = -1;
  numNodes = -1;
  adjMat = NULL;
  calcNewMat = true;

  edges = new Edge;
  edges->length = -1;
  edges->direction = 0;
  edges->startNode = 0;
  edges->endNode = 0;
  edges->next = NULL;

  tempNodeNum = 0;
  nodeHanging = new bool[20];
  nodeType = new int[20];

  unexploredEdges = new int[20];
  dirUnexploredEdges = new int[4 * 20];

  for (int i = 0; i < 20; i++) {
    nodeHanging[i] = true;
    nodeType[i] = 0;
  }

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

  if (nodeHanging) {
    delete[] nodeHanging;
    nodeHanging = NULL;
  }

  if (nodeType) {
    delete[] nodeType;
    nodeType = NULL;
  }

  if (dirUnexploredEdges) {
    delete[] dirUnexploredEdges;
    dirUnexploredEdges = NULL;
  }

  if (unexploredEdges) {
    delete[] unexploredEdges;
    unexploredEdges = NULL;
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
    //cout << "start node of an edge must be less than end node";
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
  if (adjMat && !calcNewMat) {
    return adjMat;
  }

  int width = nodeTotal();
  if (width <= 0) {
    return NULL;
  }

  if (calcNewMat && adjMat) {
    delete[] adjMat;
    adjMat = NULL;
    calcNewMat = false;
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
        currentHeading = ((edge->direction + 1) % 4) + 1;
        completeSearch++;
      }

      if (edge->startNode == nextNode && edge->endNode == curNode) {
        newHeading = ((edge->direction + 1) % 4) + 1;
        completeSearch++;
      }

      if (completeSearch >= 2) {
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
        currentHeading = ((edge->direction + 1) % 4) + 1;
        completeSearch++;
      }

      if (edge->startNode == curNode && edge->endNode == nextNode) {
        newHeading = edge->direction;
        completeSearch++;
      }

      if (completeSearch >= 2) {
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

      if (edge->startNode == nextNode && edge->endNode == curNode) {
        newHeading = ((edge->direction + 1) % 4) + 1;
        completeSearch++;
      }

      if (completeSearch >= 2) {
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

      if (edge->startNode == curNode && edge->endNode == nextNode) {
        newHeading = edge->direction;
        completeSearch++;
      }

      if (completeSearch >= 2) {
        break;
      }
      edge = edge->next;
    }
  }

  /**************************************************/
  // cout << "negate prev heading: " << negCurrentHeading <<endl;
  // cout << "negate new heading: " << negNewHeading <<endl;
  // cout << "current heading: " << currentHeading <<endl;
  // cout << "new heading: " << newHeading <<endl;

  switch (currentHeading) {
  case 1: {
    switch (newHeading) {
    case 1: {
      //Serial.println("Straight");
      turn('S');
      //cout << "Straight\n";
      break;
    }

    case 2: {
      //Serial.println("Right");
      turn('R');
      //cout << "Right\n";
      break;
    }

    case 3: {
      //Serial.println("Back");
      turn('B');
      //cout << "Back\n";
      break;
    }

    case 4: {
      //Serial.println("Left");
      turn('L');
      //cout << "Left\n";
      break;
    }

    default:
      //Serial.println("STOP");
      turn('X');
      //cout << "STOP\n";
      break;
    }
    break;
  }

  case 2: {
    switch (newHeading) {
    case 1: {
      //Serial.println("Left");
      turn('L');
      //cout << "Left\n";
      break;
    }

    case 2: {
      //Serial.println("Straight");
      turn('S');
      //cout << "Straight\n";
      break;
    }

    case 3: {
      turn('R');
      //cout << "Right\n";
      // Serial.println("Right");
      break;
    }

    case 4: {
      //Serial.println("Back");
      turn('B');
      //cout << "Back\n";
      break;
    }

    default:
      //Serial.println("STOP");
      turn('X');
      //cout << "STOP\n";
      break;
    }
    break;
  }
  case 3: {
    switch (newHeading) {
    case 1: {
      //Serial.println("Back");
      turn('B');
      //cout << "Back\n";
      break;
    }

    case 2: {
      //Serial.println("Left");
      turn('L');
      //cout << "Left\n";
      break;
    }

    case 3: {
      //Serial.println("Straight");
      turn('S');
      //cout << "Straight\n";
      break;
    }

    case 4: {
      //Serial.println("Right");
      turn('R');
      //cout << "Right\n";
      break;
    }

    default:
      //Serial.println("STOP");
      turn('X');
      //cout << "STOP\n";
      break;
    }
    break;
  }
  case 4: {
    switch (newHeading) {
    case 1: {
      //Serial.println("Right");
      turn('R');
      //cout << "Right\n";
      break;
    }

    case 2: {
      //Serial.println("Back");
      turn('B');
      //cout << "Back\n";
      break;
    }

    case 3: {
      //Serial.println("Left");
      turn('L');
      //cout << "Left\n";
      break;
    }

    case 4: {
      //Serial.println("Straight");
      turn('S');
      //cout << "Straight\n";
      break;
    }

    default:
      //Serial.println("STOP");
      turn('X');
      //cout << "STOP\n";
      break;
    }
    break;
  }

  default: {
    //Serial.println("STOP");
    // turn('X');
    cout << "STOP\n";
    break;
  }
  }
}

int Graph::getTempNodeNum(){
  return tempNodeNum;
}

void Graph::incTempNodeNum() {
  tempNodeNum++;
}

void Graph::decTempNodeNum() {
  tempNodeNum--;
}


int Graph::getNodeType(int nodeID) {
  // deadend = 1
  // corner = 2
  // T = 3
  // Cross = 4
  if (nodeID > tempNodeNum) {
    return -1;
  }
  else {
    return nodeType[nodeID - 1];
  }
}

void Graph::setNodeType(int nodeID, int newNodeType) {
  // deadend = 1
  // corner = 2
  // T = 3
  // Cross = 4
  if (nodeID <= tempNodeNum) {
    nodeType[nodeID - 1] = newNodeType;
  }
}

bool Graph::getNodeHanging(int nodeID){
  if (nodeID <= tempNodeNum) {
    return nodeHanging[nodeID - 1];
  }

  else {
    return true;
  }
}

void Graph::setNodeHanging(int nodeID, bool val) {
    if (nodeID <= tempNodeNum) {
      nodeHanging[nodeID -1] = val;
    }
}



void Graph::mergeNodes() {
  int nodeA[10] = {0,0,0,0,0,0,0,0,0};
  int nodeB[10] = {0,0,0,0,0,0,0,0,0};
  int numPairs = 0;

  for (int i = 0; i < tempNodeNum; i++) {
    for (int j = i + 1; j < tempNodeNum; j++) {
      if (nodeHanging[i] && nodeHanging[j] && i < j) {
        getAdjMat();
        int *path1 = calculateShortestPath(adjMat, i + 1, j + 1, tempNodeNum);
        int *path2 = calculateShortestPath(adjMat, j + 1, i + 1, tempNodeNum);


        int path1Sum[2] = {0, 0};
        int path2Sum[2] = {0, 0};
        for (int k = 1; k < path1[0]; k++) {
          Edge *searchEdge = edges;

          if (path1[k + 1] < path1[k]) {
            while(searchEdge->length > 0) {
              if ((searchEdge->startNode == path1[k + 1]) && (searchEdge->endNode == path1[k])) {
                // invert direction
                switch (searchEdge-> direction) {
                  case 1: {
                    // travelling downwards
                    path1Sum[1] -= searchEdge->length;
                    break;
                  }

                  case 2: {
                    // travelling left
                    path1Sum[0] -= searchEdge->length;
                    break;
                  }

                  case 3: {
                    // travelling upwards
                    path1Sum[1] += searchEdge->length;
                    break;
                  }

                  case 4: {
                    // travelling right
                    path1Sum[0] += searchEdge->length;
                    break;
                  }
                }
                break;
              }
              searchEdge = searchEdge->next;
            }
          }

          else if (path1[i] < path1[i + 1]) {
            while(searchEdge->length > 0) {
              if ((searchEdge->startNode == path1[k]) && (searchEdge->endNode == path1[k + 1])) {
                // do not inver direction
                switch (searchEdge-> direction) {
                case 1: {
                  // travelling upwards
                  path1Sum[1] += searchEdge->length;
                  break;
                }

                case 2: {
                  // travelling right
                  path1Sum[0] += searchEdge->length;
                  break;
                }

                case 3: {
                  // travelling downwards
                  path1Sum[1] -= searchEdge->length;
                  break;
                }

                case 4: {
                  // travelling left
                  path1Sum[0] -= searchEdge->length;
                  break;
                }
                }
                break;
              }
              searchEdge = searchEdge->next;
            }
          }

        }

        for (int k = 1; k < path2[0]; k++) {
          Edge *searchEdge = edges;
          if (path2[k + 1] < path2[k]) {
            while(searchEdge->length > 0) {
              if ((searchEdge->startNode == path2[k + 1]) && (searchEdge->endNode == path2[k])) {
                // invert direction

                switch (searchEdge-> direction) {
                  case 1: {
                    // travelling downwards
                    path2Sum[1] -= searchEdge->length;
                    break;
                  }

                  case 2: {
                    // travelling left
                    path2Sum[0] -= searchEdge->length;
                    break;
                  }

                  case 3: {
                    // travelling upwards
                    path2Sum[1] += searchEdge->length;
                    break;
                  }

                  case 4: {
                    // travelling right
                    path2Sum[0] += searchEdge->length;
                    break;
                  }
                }
                break;
              }
              searchEdge = searchEdge->next;
            }
          }
          else if (path2[k] < path2[k + 1]) {
            while(searchEdge->length > 0) {
              if ((searchEdge->startNode == path2[k]) && (searchEdge->endNode == path2[k + 1])) {
                // do not inver direction

                switch (searchEdge-> direction) {
                case 1: {
                  // travelling upwards
                  path2Sum[1] += searchEdge->length;
                  break;
                }

                case 2: {
                  // travelling right
                  path2Sum[0] += searchEdge->length;
                  break;
                }

                case 3: {
                  // travelling downwards
                  path2Sum[1] -= searchEdge->length;
                  break;
                }

                case 4: {
                  // travelling left
                  path2Sum[0] -= searchEdge->length;
                  break;
                }
                }
                break;
              }
              searchEdge = searchEdge->next;
            }
          }
        }



        if (path1Sum[0] == 0 && path1Sum[1] == 0 && path2Sum[0] == 0 && path2Sum[1] == 0) {
          cout << "Merging nodes: " << i + 1 << " and " << j + 1 << endl;

          nodeA[numPairs] = i + 1;
          nodeB[numPairs] = j + 1;
          numPairs++;
        }

      }
    }
  }

  for (int i = 0; i < numPairs; i++) {

    if (nodeA[i] < nodeB[i]) {
      Edge *searchEdge = edges;
      while (searchEdge->length > 0) {
        if (searchEdge->endNode == nodeB[i]) {
          searchEdge->endNode = nodeA[i];
        }
        else if (searchEdge->startNode == nodeB[i] ) {
          searchEdge->startNode = nodeA[i];
        }
        searchEdge = searchEdge->next;
      }
      // to byte below
      int unExploredCount = 0;
      for (int l = 0; l < 4; l++) {
        int dir1 = dirUnexploredEdges[nodeA[i] * 4 + l];
        int dir2 = dirUnexploredEdges[nodeB[i] * 4 + l];

        if (dir1 == dir2) {
          dirUnexploredEdges[nodeA[i] * 4 + l] = 1;
          unExploredCount++;
        }
        else {
          dirUnexploredEdges[nodeA[i] * 4 + l] = 0;
        }

        dirUnexploredEdges[nodeB[i] * 4 + l] = 0;

      }
      tempNodeNum--;
      unexploredEdges[nodeA[i] - 1] = unExploredCount;
      unexploredEdges[nodeB[i] - 1] = 0;
      calcNewMat = true;
      countNodes();
    }

    else {
      Edge *searchEdge = edges;
      while (searchEdge->length > 0) {
        if (searchEdge->endNode == nodeA[i] ) {
          searchEdge->endNode = nodeB[i];
        }
        else if (searchEdge->startNode == nodeA[i] ) {
          searchEdge->startNode = nodeB[i];
        }
        searchEdge = searchEdge->next;
      }

      // to byte below
      int unExploredCount = 0;
      for (int l = 0; l < 4; l++) {
        int dir1 = dirUnexploredEdges[nodeA[i] * 4 + l];
        int dir2 = dirUnexploredEdges[nodeB[i] * 4 + l];

        if (dir1 == dir2) {
          dirUnexploredEdges[nodeB[i] * 4 + l] = 1;
          unExploredCount++;
        }
        else {
          dirUnexploredEdges[nodeB[i] * 4 + l] = 0;
        }

        dirUnexploredEdges[nodeA[i] * 4 + l] = 0;

      }

      tempNodeNum--;
      unexploredEdges[nodeB[i] - 1] = unExploredCount;
      unexploredEdges[nodeA[i] - 1] = 0;
      calcNewMat = true;
      countNodes();
    }
  }
  countNodes();
}

void Graph::addNewNode(int juncType, int currentDir) {
  tempNodeNum++;
  setNodeHanging(tempNodeNum - 1, true);

  switch (juncType) {

    case 1: {
      setNodeType(tempNodeNum, 1);
      unexploredEdges[tempNodeNum - 1] = 0;
      break;
    }

    case 2: {
      setNodeType(tempNodeNum, 2);
      unexploredEdges[tempNodeNum - 1] = 1;
      // to byte below
      int idx = (tempNodeNum - 1) * 4 + ((currentDir - 2) % 4);
      dirUnexploredEdges[idx] = 1;
      break;
    }

    case 3: {
      setNodeType(tempNodeNum, 2);
      unexploredEdges[tempNodeNum - 1] = 1;
      // to byte below
      int idx = (tempNodeNum - 1) * 4 + (currentDir % 4);
      dirUnexploredEdges[idx] = 1;
      break;
    }

    case 4: {
      setNodeType(tempNodeNum, 3);
      unexploredEdges[tempNodeNum - 1] = 2;
      // to byte below
      int idx1 = (tempNodeNum - 1) * 4 + ((currentDir - 2) % 4);
      int idx2 = (tempNodeNum - 1) * 4 + currentDir - 1;
      dirUnexploredEdges[idx1] = 1;
      dirUnexploredEdges[idx2] = 1;
      break;
    }

    case 5: {
      setNodeType(tempNodeNum, 3);
      unexploredEdges[tempNodeNum - 1] = 2;
      // to byte below
      int idx1 = (tempNodeNum - 1) * 4 + (currentDir % 4);
      int idx2 = (tempNodeNum - 1) * 4 + currentDir - 1;
      dirUnexploredEdges[idx1] = 1;
      dirUnexploredEdges[idx2] = 1;
      break;
    }

    case 6: {
      setNodeType(tempNodeNum, 3);
      unexploredEdges[tempNodeNum - 1] = 2;
      // to byte below
      int idx1 = (tempNodeNum - 1) * 4 + ((currentDir - 2) % 4);
      int idx2 = (tempNodeNum - 1) * 4 + (currentDir % 4);
      dirUnexploredEdges[idx1] = 1;
      dirUnexploredEdges[idx2] = 1;
      break;
    }

    case 7: {
      setNodeType(tempNodeNum, 4);
      unexploredEdges[tempNodeNum - 1] = 3;
      // to byte below
      int idx1 = (tempNodeNum - 1) * 4 + ((currentDir - 2) % 4);
      int idx2 = (tempNodeNum - 1) * 4 + (currentDir % 4);
      int idx3 = (tempNodeNum - 1) * 4 + currentDir - 1;
      dirUnexploredEdges[idx1] = 1;
      dirUnexploredEdges[idx2] = 1;
      dirUnexploredEdges[idx3] = 1;
      break;
    }

    default:
      break;
    }

  cout << "========================================\n";
  cout << "Node Stats:\n";
  cout << "Node ID: " << tempNodeNum << endl;
  cout << "Node Type: " << nodeType[tempNodeNum -1] << endl;
  cout << "Node Hanging: " << nodeHanging[tempNodeNum -1] << endl;
  cout << "Num unexplored edges: " << unexploredEdges[tempNodeNum -1] << endl;
  cout << "Directions of unexplored edges: " << endl;
  for (int i = 0; i < 4; ++i) {
    cout << "Dir " << i + 1 << "  Val:  ";
    cout << dirUnexploredEdges[4 * (tempNodeNum - 1) + i] << endl;
  }

  cout << "leaving addNewNode\n";
}

int Graph::getLowHangingNode() {
  int i = 0;
  while(!nodeHanging[i]) {
    i++; 
  }

  return i + 1;

}

void stats() {
  
}
