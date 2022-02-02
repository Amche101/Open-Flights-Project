/**
 * @file Dijkstra.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>

#include "graph.h"
#include "edge.h"

#include "Dijkstra.h"

Dijkstra::Dijkstra(Graph graph) : g_(graph) 
{
}

Dijkstra::Dijkstra(Graph graph, vector<Vertex>vertices) :g_(Graph(false,false)) {
    for (Vertex v : vertices) {
      g_.insertVertex(v);
      for (Vertex u : graph.getAdjacent(v)) {
         if(std::find(vertices.begin(),vertices.end(),u) != vertices.end())
         g_.insertEdge(v,u);
      }
    }
}

vector<Vertex> Dijkstra::shortestPath(Vertex source, Vertex destination) {
    std::vector<Vertex> path;
    if (!g_.vertexExists(source) || !g_.vertexExists(destination)) {
        return path;
    }
    std::map<Vertex, int> distances; // Map of Vertex to distance from source
    std::map<Vertex, Vertex> previous; //Map of Vertex to previous Vertex in path
    auto cmp = [] (std::pair<Vertex, int> a, std::pair<Vertex, int> b)
        {
            return a.second >= b.second;
        };
    //Stores the next Vertex + distance pair to visit sorted by smallest distance 
    std::priority_queue<std::pair<Vertex, int>, std::vector<std::pair<Vertex, int>>, decltype(cmp)> priority_queue(cmp);
    
    vector<Vertex> visited;

    Vertex current = source;
    distances[source] = 0;
    while(current != destination) {
    
        
        for (Vertex neighbor: g_.getAdjacent(current)) {
           
            
            if (std::find(visited.begin(), visited.end(), neighbor) == visited.end()) {
                int dist = g_.getEdgeWeight(current, neighbor) + distances.find(current)->second;
                
                //If the neighbor already has a recorded distance, update if new distance is smaller
                if (distances.find(neighbor) != distances.end()) {
                    int oldDist = distances[neighbor];
                    
                    if (dist < oldDist) {
                        distances[neighbor] = dist;
                        previous[neighbor] = current;
                        priority_queue.push(*distances.find(neighbor));
                    }
                } else {
                    distances[neighbor] = dist;
                    previous[neighbor] = current;
                    priority_queue.push(*distances.find(neighbor));
                }
            }
        }

        visited.push_back(current);
        if (priority_queue.size() == 0) {
            break;
        }
        current = priority_queue.top().first;
        priority_queue.pop();
        
    }

    //Path could not be found
    if (current != destination) {
        return path;
    }

    path.push_back(destination);
    for (Vertex i = previous[destination]; i != source; i = previous[i]) {
        path.push_back(i);
    }
    path.push_back(source);
    path_distance_ = distances.find(destination)->second;
    std::reverse(path.begin(), path.end());
    path_ = path;
    return path;
}

void Dijkstra::print() {
    std::stringstream ss;
    if (path_.size() == 0) {
        ss << "path could not be found" << std::endl;
    } else {
        ss << "Shortest Path:" << std::endl;
        ss << "\nStartpoint:" << std::endl;
        ss << g_.getNode(path_[0]).name_ << std::endl;
        ss << "Endpoint:" << std::endl;
        ss << g_.getNode(path_[path_.size() - 1]).name_ << std::endl;
        ss << "\nPath:" << std::endl;
        for (Vertex vert: path_) {
            ss << "\nID: " + vert << std::endl;
            ss << "Name: " + g_.getNode(vert).name_ << std::endl;
        }
        ss << "\nTotal Distance: " << path_distance_ << std::endl;
    }
    std::cout << ss.str();
}