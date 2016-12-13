// A C / C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph

#include <stdio.h>
#include <limits.h>

struct Edge
{
  int weight;
  int direction;
  int firstNode;
  int secondNode;
};

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[], int V)
{
   // Initialize min value
 int min = INT_MAX, min_index;

 for (int v = 0; v < V; v++)
   if (sptSet[v] == false && dist[v] <= min)
     min = dist[v], min_index = v;

   return min_index;
 }

// A utility function to print the constructed distance array
void printSolution(int dist[], int V)
{
   printf("Vertex   Distance from Source\n");
   for (int i = 0; i < V; i++)
    printf("%d \t\t %d\n", i, dist[i]);
}

// A utility function to print the path to goal
void printPath(Edge previous[], int start, int goal)
{
  int i = goal;
  while (previous[i].firstNode != start || previous[i].secondNode != start) 
  {
    if (previous[i].firstNode == i)
    {
      printf("From %d to %d\n", previous[i].firstNode, previous[i].secondNode);
    }
    if (previous[i].secondNode == i)
    {
      printf("From %d to %d\n", previous[i].secondNode, previous[i].firstNode);
    }
    else
    {
      printf("Goal\n");
      break;
    }
  }
}

// Funtion that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(Edge graph[], int src, int V, int dist[], Edge previous[])
{ 
     bool sptSet[V]; // sptSet[i] will true if vertex i is included in shortest
                     // path tree or shortest distance from src to i is finalized

     // Initialize all distances as INFINITE and stpSet[] as false
     for (int i = 0; i < V; i++)
      dist[i] = INT_MAX, sptSet[i] = false;

     // Distance of source vertex from itself is always 0
    dist[src] = 0;

     // Find shortest path for all vertices
    for (int count = 0; count < V-1; count++)
    {
       // Pick the minimum distance vertex from the set of vertices not
       // yet processed. u is always equal to src in first iteration.
     int u = minDistance(dist, sptSet, V);

       // Mark the picked vertex as processed
     sptSet[u] = true;

       // Update dist value of the adjacent vertices of the picked vertex.
     for (int v = 0; v < V; v++)
         // Update dist[v] only if, there is an edge from u to v
         // v is not in sptSet, and total weight of path from src to v through u is 
         // smaller than current value of dist[v]
       if ((graph[v].firstNode == u || graph[v].secondNode == u) 
        && (!sptSet[v] && dist[u] != INT_MAX && graph[v].weight+dist[u] < dist[v]))
       {
        dist[v] = dist[u] + graph[u].weight;
        previous[v] = graph[v];
      }
    }
  }
  
// driver program to test above function
int main()
{
  Edge *edge0 = new Edge;
  edge0->weight = 5;
  edge0->direction = 1;
  edge0->firstNode = 0;
  edge0->secondNode = 1;


  Edge *edge1 = new Edge;
  edge1->weight =2;
  edge1->direction = 1;
  edge1->firstNode = 1;
  edge1->secondNode = 2;

  Edge *edge2 = new Edge;
  edge2->weight = 8;
  edge2->direction = 1;
  edge2->firstNode = 2;
  edge2->secondNode = 4;

  Edge *edge3 = new Edge;
  edge3->weight = 3;
  edge3->direction = 1;
  edge3->firstNode = 0;
  edge3->secondNode = 3;

  Edge *edge4 = new Edge;
  edge4->weight = 7;
  edge4->direction = 1;
  edge4->firstNode = 3;
  edge4->secondNode = 5;

  Edge *edge5 = new Edge;
  edge5->weight = 1;
  edge5->direction = 1;
  edge5->firstNode = 4;
  edge5->secondNode = 5;

  Edge *edge6 = new Edge;
  edge6->weight = 1;
  edge6->direction = 1;
  edge6->firstNode = 2;
  edge6->secondNode = 3;

  Edge graph[] = {*edge0,*edge1,*edge2,*edge3,*edge4,*edge5,*edge6};

  int V = 6;  // Number of nodes in the graph
  int start = 0;
  int goal = 4;

  int dist[V];  // dist[i] will hold the shortest distance from src to i
  Edge previous[V]; // previous[i] will hold the previous shortest path edge to i


  dijkstra(graph, start, V, dist, previous);
  //printSolution(dist, V);  // print the constructed distance array
  printPath(previous, start, goal);

  return 0;
}