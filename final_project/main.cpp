#include "Eulerian.h"
#include <vector>
#include <iostream>
#include "edge.h"
#include <fstream>
#include <sstream>
#include "Dijkstra.h"

using namespace std;

int main() {
  Graph g1 = Graph(true,true);
  //open airports file
  string fName = "airports.txt";
  ifstream iFile(fName.c_str());
  if ( iFile.fail() ) {
    cout << "File not found: " << fName << endl; 
    return 0;
  }

  vector<Vertex> IDs;
  vector<string> names;
  vector<double> latitudes;
  vector<double> longitudes;
  int ID;
  double latitude, longitude;
  string name,line;
  int i = 0;

  //parsing the data 
  while(getline(iFile,line))
  { 
    std::stringstream ss(line);//make each line input like a stream
    ss>>ID;
    ss.ignore(INT_MAX,'"');
    getline(ss,name,'"');
    ss.ignore(INT_MAX,',');//skip some data separated by comma
    ss.ignore(INT_MAX,',');
    ss.ignore(INT_MAX,',');
    ss.ignore(INT_MAX,',');
    ss.ignore(INT_MAX,',');
    ss>>latitude;
    ss.ignore(INT_MAX,',');
    ss>>longitude;
    ss.ignore(INT_MAX,',');
    IDs.push_back(to_string(ID));
    g1.insertVertex(IDs[i]);
    g1.insertNode(IDs[i], Node(name,latitude,longitude));
    names.push_back(name);
    latitudes.push_back(latitude);
    longitudes.push_back(longitude);
    i++;
  }
  
  //open airports file
  string fName2 = "routes.txt";
  ifstream iFile2(fName2.c_str());
  if ( iFile2.fail() ) {
    cout << "File not found: " << fName2 << endl; 
    return 0;
  }

  int source,dest;
  vector<Vertex> sources;
  vector<Vertex> dests;
  int j = 0;
  //parsing the data 
  while(getline(iFile2,line))
  { 
    std::stringstream ss(line);//make each line input like a stream
    ss.ignore(INT_MAX,',');
    ss.ignore(INT_MAX,',');
    ss.ignore(INT_MAX,',');
    ss>>source;
    ss.ignore(INT_MAX,',');
    ss.ignore(INT_MAX,',');
    ss>>dest;
    sources.push_back(to_string(source));
    dests.push_back(to_string(dest));
    g1.insertEdge(sources[j],dests[j]);
    double lat = g1.getNode(sources[j]).latitude_ - g1.getNode(dests[j]).latitude_;
    double lon = g1.getNode(sources[j]).longitude_ - g1.getNode(dests[j]).longitude_;
    lat = lat * lat;
    lon = lon * lon;
    g1.setEdgeWeight(sources[j], dests[j], sqrt(lat + lon));
    j++;
  }

  g1.print();

  Dijkstra g_dijkstra = Dijkstra(g1);
  vector<Vertex> path = g_dijkstra.shortestPath("3437","6404");
  g_dijkstra.print();  

  return 0;
}
