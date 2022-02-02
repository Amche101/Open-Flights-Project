
#include "../cs225/catch/catch.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "../cs225/PNG.h"
#include "../cs225/HSLAPixel.h"
#include "../graph.h"
#include "../Eulerian.h"
#include "../Dijkstra.h"

using namespace cs225;
using namespace std;

TEST_CASE("BFS maintains the BFS ordering") {
  Graph g2 = Graph(false,false);
  g2.insertVertex("0");
  g2.insertVertex("1");
  g2.insertVertex("2");
  g2.insertVertex("3");
  g2.insertEdge("0", "1");
  g2.insertEdge("0", "2");
  g2.insertEdge("1", "2");
  g2.insertEdge("2", "0");
  g2.insertEdge("2", "3");
  g2.insertEdge("3", "3");
  Vertex start = g2.getStartingVertex();
  g2.BFS(start);
  unsigned size = g2.getVertices().size();
  vector<string> output;
  for (Vertex w : g2.getVertices()) {
    for (unsigned i = 0; i < size; i++) {
      output.push_back(g2.getNodeLabel(w));
      cout << output[i] << endl;
    }
  }
  for (unsigned i = 0; i < size; i++) {
    REQUIRE(output[i] == "VISITED");
  }
}

TEST_CASE("BFS maintains the BFS ordering part 2") {
  Graph g = Graph(false,false);
  g.insertVertex("0");
  g.insertVertex("1");
  g.insertVertex("2");
  g.insertVertex("3");
  g.insertEdge("0", "1");
  g.insertEdge("0", "2");
  g.insertEdge("1", "2");
  g.insertEdge("2", "0");
  g.insertEdge("2", "3");
  g.insertEdge("3", "3");
  Vertex start = g.getStartingVertex();
  g.BFS(start);
  unsigned size = g.getVertices().size();
  vector<string> output;
  for (Vertex w : g.getVertices()) {
    for (unsigned i = 0; i < size; i++) {
      output.push_back(g.getNodeLabel(w));
      cout << output[i] << endl;
    }
  }
  for (unsigned i = 0; i < size; i++) {
    REQUIRE(output[i] == "VISITED");
  }
}

TEST_CASE("Eulerian Path -> If graph has an Euler path (Semi-Eulerian)") {
  Graph g = Graph(false,false);
  g.insertVertex("0");
  g.insertVertex("1");
  g.insertVertex("2");
  g.insertVertex("3");
  g.insertEdge("0", "1");
  g.insertEdge("0", "2");
  g.insertEdge("1", "2");
  g.insertEdge("2", "0");
  g.insertEdge("2", "3");
  g.insertEdge("3", "3");
  Eulerian e(g, g.getVertices());
  REQUIRE(e.isEulerian() == 1);
}

 TEST_CASE("Eulerian Path -> Graph has a eulerian path 1") {
   Graph g = Graph(false,false);
   g.insertVertex("0");
   g.insertVertex("1");
   g.insertVertex("2");
   g.insertVertex("3");
   g.insertEdge("0", "1");
   g.insertEdge("1", "2");
   g.insertEdge("2", "3");
   g.insertEdge("3", "0");
   g.insertEdge("0", "3");
   g.insertEdge("1", "0");
   g.insertEdge("0", "2");
   Eulerian e(g, g.getVertices());
   REQUIRE(e.isEulerian() == 1);
}

TEST_CASE("Eulerian Path -> Graph has a eulerian path 2") {
   Graph g = Graph(false,false);
   g.insertVertex("0");
   g.insertVertex("1");
   g.insertVertex("2");
   g.insertVertex("3");
   g.insertEdge("0", "1");
   g.insertEdge("1", "2");
   g.insertEdge("2", "3");
   g.insertEdge("3", "0");
   g.insertEdge("0", "3");
   g.insertEdge("1", "0");
   g.insertEdge("0", "2");
   Eulerian e(g, g.getVertices());
   REQUIRE(e.isEulerian() == 1);
}

TEST_CASE("Eulerian Path -> Graph prints a right eulerian path 1") {
  Graph g = Graph(false,false);
  g.insertVertex("0");
  g.insertVertex("1");
  g.insertVertex("2");
  g.insertVertex("3");
  g.insertVertex("4");
  g.insertEdge("0", "1");
  g.insertEdge("0", "2");
  g.insertEdge("1", "2");
  g.insertEdge("2", "3");
  g.insertEdge("0", "3");
  g.insertEdge("4", "3");
  g.insertEdge("1", "3");
  g.insertEdge("2", "4");
  Eulerian e = Eulerian(g, g.getVertices());
  e.findEulerTour();
  vector<Vertex> p = {"0","3","1","0","2","4","3","2","1"};
  REQUIRE(p == e.path_);
}

TEST_CASE("Eulerian Path -> Graph prints a right eulerian path 2") {
  Graph g= Graph(false);
  g.insertVertex("0");
  g.insertVertex("1");
  g.insertVertex("2");
  g.insertEdge("0", "1");
  g.insertEdge("1", "2");
  g.insertEdge("2", "0");
  Eulerian e =  Eulerian(g, g.getVertices());
  e.findEulerTour();
  vector<Vertex> p = {"0","2","1","0"};
  REQUIRE(p == e.path_);
}

TEST_CASE("Eulerian Path -> Graph prints a right eulerian path 3") {
  Graph g = Graph(false,false);
  g.insertVertex("0");
  g.insertVertex("1");
  g.insertVertex("2");
  g.insertVertex("3");
  g.insertEdge("0", "1");
  g.insertEdge("0", "2");
  g.insertEdge("1", "2");
  g.insertEdge("2", "3");
  Eulerian e(g, g.getVertices());
  e.findEulerTour();
  vector<Vertex> p = {"2","0","1","2","3"};
  REQUIRE(p == e.path_);
}



TEST_CASE("Shortest path: simple") {
  Graph g1(true, false);
  g1.insertVertex("a");
  g1.insertVertex("b");
  g1.insertVertex("c");
  g1.insertVertex("d");
  g1.insertEdge("a", "b");
  g1.setEdgeWeight("a", "b", 1);
  g1.insertEdge("a", "c");
  g1.setEdgeWeight("a", "c", 3);
  g1.insertEdge("b", "d");
  g1.setEdgeWeight("b", "d", 2);
  g1.insertEdge("c", "d");
  g1.setEdgeWeight("c", "d", 4);

  Dijkstra g_dijkstra = Dijkstra(g1);
  vector<Vertex> path = g_dijkstra.shortestPath("a","d");
  vector<Vertex> expected = {"a", "b", "d"};
  REQUIRE(expected == path);

  g1.setEdgeWeight("a", "b", 4);
  g_dijkstra = Dijkstra(g1);
  path = g_dijkstra.shortestPath("a","d");
  expected = {"a", "b", "d"};
  REQUIRE(expected == path);

  g1.setEdgeWeight("b", "d", 10);
  g_dijkstra = Dijkstra(g1);
  path = g_dijkstra.shortestPath("a","d");
  expected = {"a", "c", "d"};
  REQUIRE(expected == path);
}

//Example from https://courses.grainger.illinois.edu/cs225/fa2020/resources/dijkstra/
TEST_CASE("Shortest Path Complex") {
  Graph g1(true, false);
  g1.insertVertex("Siebel");
  g1.insertVertex("Rantoul");
  g1.insertVertex("Bloomington");
  g1.insertVertex("Kankakee");
  g1.insertVertex("Pontiac");
  g1.insertVertex("Chicago");
  g1.insertVertex("Joliet");
  g1.insertVertex("Cloud");

  g1.insertEdge("Siebel", "Rantoul");
  g1.setEdgeWeight("Siebel", "Rantoul", 21);
  g1.insertEdge("Siebel", "Bloomington");
  g1.setEdgeWeight("Siebel", "Bloomington", 50);
  
  g1.insertEdge("Rantoul", "Kankakee");
  g1.setEdgeWeight("Rantoul", "Kankakee", 57);
  g1.insertEdge("Bloomington", "Pontiac");
  g1.setEdgeWeight("Bloomington", "Pontiac", 42);
  
  g1.insertEdge("Kankakee", "Chicago");
  g1.setEdgeWeight("Kankakee", "Chicago", 63);
  g1.insertEdge("Pontiac", "Kankakee");
  g1.setEdgeWeight("Pontiac", "Kankakee", 53);
  g1.insertEdge("Pontiac", "Joliet");
  g1.setEdgeWeight("Pontiac", "Joliet", 57);
  g1.insertEdge("Pontiac", "Chicago");
  g1.setEdgeWeight("Pontiac", "Chicago", 40);
  
  g1.insertEdge("Joliet", "Chicago");
  g1.setEdgeWeight("Joliet", "Chicago", 51);
  
  g1.insertEdge("Chicago", "Cloud");
  g1.setEdgeWeight("Chicago", "Cloud", 1);

    
  Dijkstra g_dijkstra = Dijkstra(g1);
  vector<Vertex> path = g_dijkstra.shortestPath("Siebel","Cloud");
  vector<Vertex> expected = {"Siebel", "Bloomington", "Pontiac", "Chicago", "Cloud"};
  REQUIRE(expected == path);
}

TEST_CASE("Shortest path: Invalid Vertex") {

  Graph g1(true, false);
  g1.insertVertex("a");
  g1.insertVertex("b");
   Dijkstra g_dijkstra = Dijkstra(g1);
  vector<Vertex> path = g_dijkstra.shortestPath("a","c");
  vector<Vertex> expected;
  REQUIRE(expected == path);
}

TEST_CASE("Shortest path: Path not found") {
  Graph g1(true, false);
  g1.insertVertex("a");
  g1.insertVertex("b");
   Dijkstra g_dijkstra = Dijkstra(g1);
  vector<Vertex> path = g_dijkstra.shortestPath("a","b");
  vector<Vertex> expected;
  REQUIRE(expected == path);
}



