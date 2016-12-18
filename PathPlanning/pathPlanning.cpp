#include "pathPlanning.h"

// A C / C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph
// Algorithm from: http://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/
  
// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int *dist, bool *sptSet, int V)
{
   // Initialize min value
   int min = INT_MAX, min_index;
  
   for (int v = 0; v < V; v++)
     if (sptSet[v] == false && dist[v] <= min)
         min = dist[v], min_index = v;
  
   return min_index;
}

int countPath(int *previous, int start, int goal)
{
  int count = 1;
  int i = goal;
  //  loop through the path to goal to get amount of nodes to visit
  while (previous[i] != start)
  {
    i = previous[i];
    count++;
  }
  return count;
}

// A utility function to get the path from start to goal into an ordered array
int * getPath(int *previous, int start, int goal)
{
  int count = countPath(previous, start, goal);
  int * path = new int[count+1];  // Using a fixed size array
  int i = goal;
  path[count] = i;
  // Adding the nodes to the array
  for (int j = count-1; j >= 0; j--)
  {
    path[j] = previous[i];
    i = previous[i];
  }
  return path;
} 
  
// Funtion that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int *graph, int src, int V, int *dist, int *previous)
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
       {
         // Update dist[v] only if is not in sptSet, there is an edge from 
         // u to v, and total weight of path from src to  v through u is 
         // smaller than current value of dist[v]
         if (!sptSet[v] && graph[(u*V)+v] && dist[u] != INT_MAX 
                                       && dist[u]+graph[(u*V)+v] < dist[v])
         {
            dist[v] = dist[u] + graph[(u*V)+v];
            previous[v] = u;
         }
       }
     }
}
  
// driver program to test above function
int *calculateShortestPath(int *graph, int start, int goal, int V)
{
  int dist[V];      // dist[i] will hold the shortest distance from start to i
  int previous[V];  // previous[i] will hold previous node for shortest path from start 
      

  dijkstra(graph, start, V, dist, previous);
  int *path = getPath(previous, start, goal); // Get shorest path from start to goal, returned as an int array

  return path;
}
