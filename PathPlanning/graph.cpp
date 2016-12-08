#include<iostream>

using namespace std;

struct Edge {
  float length;
  float direction;
  int startNode;
  int endNode;
  Edge *next;
};

typedef Edge *Graph;

Edge nullEdge = {0, 0, -1, 0};

void appendEdge(Edge *graph, float length, float direction, int startNode, int endNode);
void printGraph(Edge &);
int sizeList(Graph &graph);

int main(int argc, char *argv[])
{
  Graph graph;

  Edge *edge1 = new Edge;
  edge1->length = 3;
  edge1->direction = 3;
  edge1->startNode = 3;
  edge1->endNode = 4;

  Edge *edge2 = new Edge;
  edge2->length = 3;
  edge2->direction = 3;
  edge2->startNode = 3;
  edge2->endNode = 4;

  Edge *edge3 = new Edge;
  edge3->length = 3;
  edge3->direction = 3;
  edge3->startNode = 3;
  edge3->endNode = 4;

  edge1->next = edge2;
  edge2->next = edge3;
  edge3->next = NULL;

  graph = edge1;
  int size = sizeList(graph);
  cout << size << endl;

  appendEdge(graph, 3, 3, 3, 3);

  size = sizeList(graph);
  cout << size << endl;
  return 0;
}

void appendEdge(Edge *graph, float length, float direction, int startNode, int endNode) {

  Edge *newEdge = new Edge;
  newEdge->length = length;
  newEdge->direction = direction;
  newEdge->startNode = startNode;
  newEdge->endNode = endNode;
  newEdge->next = graph;
  graph = newEdge;


}

void printGraph(Edge &) {
  
}


int sizeList(Graph &graph) {

  Edge *edge = graph;
  int size = 1;
  while (edge->next != NULL) {
    size++;
    edge = edge->next;
  }

  return size;
}
