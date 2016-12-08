#include<iostream>

using namespace std;

struct Edge {
  float length;
  float direction;
  int startNode;
  int endNode;
};

Edge nullEdge = {0, 0, -1, 0};

void appendEdge(Edge newEdge, Edge *graph);
void printGraph(Edge &);
int sizeList(Edge *list);

int main(int argc, char *argv[])
{
  Edge *graph = new Edge[3];
  graph[0].length = 2;
  graph[0].startNode = 0;
  graph[0].endNode = 2;
  graph[0].direction = 2;

  graph[1].length = 2;
  graph[1].startNode = 0;
  graph[1].endNode = 2;
  graph[1].direction = 2;

  graph[2] = nullEdge;


  int size = sizeList(graph);
  cout << size << endl;


  Edge newEdge;
  newEdge.endNode = 3;
  newEdge.startNode = 5;
  newEdge.length = 2;
  newEdge.direction = 2;

  appendEdge(newEdge, graph);

  size = sizeList(graph);
  cout << size << endl;

  delete[] graph;
  return 0;
}

void appendEdge(Edge newEdge, Edge *graph) {

  int size = sizeList(graph);
  Edge *newGraph = new Edge[size + 2];
  for (int i = 0; i < size; i++) {
    newGraph[i] = graph[i];
  }

  newGraph[size] = newEdge;
  newGraph[size + 1] = nullEdge;
  delete[] graph;
  graph = newGraph;

}

void printGraph(Edge &) {
  
}


int sizeList(Edge *list) {
  int size = 0;
  while (list[size].startNode >= 0) {
    size++;
  }
  return size;
}
