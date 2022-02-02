/**
 * @file Dijkstra.cpp
 * CS 225: Data Structures
 */

#pragma once

#include <vector>
#include <algorithm>

#include "graph.h"
#include "edge.h"
#include "node.h"

/**
 * Represents a algorithm to determine the shortest path between two vertices of a graph.
 * Some minor assumptions/modifications:
 * we are making an directed/undirected graph into a undirected graph to analyze
 * because we are assuming no one is traveling back and forth between
 * two same airports and there will normally be a flight going back and
 * forth between two places
 */
class Dijkstra {
  public:
    /**
     * Default constructor
     * @param graph input graph
     */
    Dijkstra(Graph graph);
    /**
     * Alternate constructor
     * @param graph - Uder input graph
     * @param vertices - Vector of all the vertices in that graph.
     */
    Dijkstra(Graph graph, vector<Vertex>vertices);

    /**
     * Uses Dijkstra's algorithm to find the shortest path
     * Implementation based on https://courses.grainger.illinois.edu/cs225/fa2020/resources/dijkstra/
     * @param source - the startpoint
     * @param destination - the endpoint
     * @return the path found
     */
    vector<Vertex> shortestPath(Vertex source, Vertex destination);

    void print();

  private:
    /**
     * Making a new graph.
     */
    Graph g_;

    //The last shortest path
    vector<Vertex> path_;
    
    //The total distance of the last shortest path
    int path_distance_;
};