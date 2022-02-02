/**
 * @file Eulerian.cpp
 * @author Haijian Wang
 * CS 225: Data Structures
 */

#pragma once

#include <vector>
#include <algorithm>

#include "graph.h"
#include "edge.h"
#include "node.h"



/**
 * Represents a algorithm to determine the Eulerian path of a graph.
 * Some minor assumptions/modifications:
 * we are making an directed/undirected graph into a undirected graph to analyze
 * because we are assuming no one is traveling back and forth between
 * two same airports and there will normally be a flight going back and
 * forth between two places
 */
class Eulerian {
  public:
      Graph g_;
      vector<Vertex> path_;
      /**
       * Constructor to create a eulerian analyzer.
       * @param graph - the input graph we want to create a subgraph from
       * @param vertices - the vertices we want to include to determine a Eulerian path
       */
      Eulerian(Graph graph, vector<Vertex>vertices);

      /**
       * Function to determine if the graph is Eulerian or not
       * @return - If graph is not Eulerian, return 0;
       *         - If graph has an Euler path (Semi-Eulerian), return 1;
       *         - If graph has an Euler Circuit (Eulerian), return 2;
       */
      int isEulerian();

      /**
       * Method to check if all non-zero degree vertices are connected.
       * @return - All non-zero degree vertices are connected or not.
       */
      bool isConnected(); 

      /**
       * Recursive Implementation to Run DFS for isConnected method
       * @param v - input vertex v to run DFS from 
       * @param visited - input map that label vertex as visited or not
       */
      void DFS(Vertex v, unordered_map<Vertex,bool> visited);

      /**
       * Method to find the Eulerian path for the whole graph and 
       * store it in the public variable path_
       */
      void findEulerTour();

      /**
       * Recursive Method to find the Eulerian path for the graph unitil vertex u and 
       * store it in the public variable path_
       */
      void findEulerUtil(Vertex u);

      /**
       * Count the Reachable Vertices from a given vertex
       * @param v - input vertex v to run DFSCount from 
       * @param visited - input map that label vertex as visited or not
       * @return - an integer for the number of reachable vertices
       */
      int DFSCount(Vertex v, unordered_map<Vertex,bool> &visited); 

      /**
       * Check to see if the next edge is a valid edge to pick or not
       * @param u - input source vertex for the edge 
       * @param v - input dest vertex for the edge
       * @return - true for valid pick
       */
      bool isValidNextEdge(Vertex u, Vertex v); 

      /**
       * print out the path in terms of vertices 
       */ 
      void print() const;



  private:

};
