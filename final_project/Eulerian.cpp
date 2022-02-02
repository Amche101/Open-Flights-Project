/**
 * @file Eulerian.cpp
 * @author Haijian Wang
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>

#include "graph.h"
#include "edge.h"
#include "Eulerian.h"

Eulerian::Eulerian(Graph graph, vector<Vertex>vertices) :g_(Graph(false,false)) {
    for (Vertex v : vertices) {
      g_.insertVertex(v);
      for (Vertex u : graph.getAdjacent(v)) {
         if(std::find(vertices.begin(),vertices.end(),u) != vertices.end())
         g_.insertEdge(v,u);
      }
    }
   }

void Eulerian::DFS(Vertex v, unordered_map<Vertex,bool> visited) { 
    visited[v] = true; 
    // Recursive for all the vertices adjacent
    for (Vertex u : g_.getAdjacent(v)) 
        if (!visited[u]) 
        DFS(u, visited); 
   } 

bool Eulerian::isConnected() 
{ 
   // Start to label all the vertices as not visited 
   unordered_map<Vertex,bool> visited; 
   for (Vertex v : g_.getVertices()) {
      visited[v] = false;
   }
       
   bool flag = false;
   Vertex u;
   // Find a vertex with non-zero degree 
   for (Vertex v : g_.getVertices()) {
      if (g_.getAdjacent(v).size() != 0) {
         u = v;
         flag = true;
      }     
   }

   // If there are no edges in the graph, return true 
   if (flag) 
   return true; 

   //Run DFS from a vertex with non-zero degree 
   DFS(u, visited);  
   for (Vertex v : g_.getVertices()) {
      if (visited[v] == false && g_.getAdjacent(v).size() > 0) 
      return false; 
   }

   return true;
}

int Eulerian::isEulerian() 
{ 
   //check if all non-zero degree vertices are connected,  
   if (isConnected() == false) 
   return 0; 
  
   // Count odd vertices
   int odd = 0; 
   for (Vertex v : g_.getVertices()) {
      if (g_.getAdjacent(v).size() % 2 == 1)
      odd++;
   }             

   // If there are more than 2 odd vertices, graph is not Eulerian 
   if (odd > 2) 
   return 0; 
  
   // If odd count is 2, then semi-eulerian. 
   // If odd count is 0, then eulerian 
   return (odd)? 1 : 2; 
} 

void Eulerian::findEulerTour() 
{ 
  Vertex u = g_.getStartingVertex(); 
  //Start with an odd vertex is there is one
   for (Vertex v : g_.getVertices()) {
      if (g_.getAdjacent(v).size()%2 == 1) {   
         u = v;
         break;  
      }
   }  
   path_.push_back(u);
   findEulerUtil(u); 
}

void Eulerian::findEulerUtil(Vertex u) 
{ 
   //Recursive for all the adjacent vertices 
   for (Vertex v : g_.getAdjacent(u)) {  
      if(g_.edgeExists(u,v) && isValidNextEdge(u,v)) { 
         path_.push_back(v);
         g_.removeEdge(u,v);
         findEulerUtil(v);
      }
   } 
} 

bool Eulerian::isValidNextEdge(Vertex u, Vertex v) 
{ 
   //If v is the only adjacent vertex of u, then must pick
   if (g_.getAdjacent(u).size() == 1) 
   return true; 

   unordered_map<Vertex,bool> visited; 
   for (Vertex v : g_.getVertices()) {
      visited[v] = false;
   }
   //count the reachable number of vertices before removing the edge
   int count1 = DFSCount(u, visited); 
  
   for (Vertex v : g_.getVertices()) {
      visited[v] = false;
   } 
   g_.removeEdge(u,v);
   //count the reachable number of vertices after removing the edge
   int count2 = DFSCount(u, visited); 
   g_.insertEdge(u, v); 

   //if the reachable number of vertices changes, then not valid
   if (count1>count2)
   return false;
   else
   return true;
} 

int Eulerian::DFSCount(Vertex v, unordered_map<Vertex,bool> & visited) 
{ 
   visited[v] = true; 
   int count = 1; 

   for (Vertex u : g_.getAdjacent(v)) {
      if (g_.edgeExists(v,u) && !visited[u]) 
      count += DFSCount(u, visited);
   }
   return count; 
} 

void Eulerian::print() const {
   for (Vertex v: path_) {
      cout<<v<<",";
   }
   cout<<endl;
}