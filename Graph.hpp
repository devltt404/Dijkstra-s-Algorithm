/*
    This file contains the Graph class definition.
*/

#ifndef GRAPH_H
#define GRAPH_H

#include "GraphBase.hpp"
#include "Vertex.hpp"
#include <unordered_map>

using namespace std;

class Graph : public GraphBase {
public:
  Graph();  // Constructor
  ~Graph(); // Destructor

  // Function to add a vertex to the graph
  void addVertex(string label);
  // Function to remove a vertex from the graph
  void removeVertex(string label);
  // Function to add an edge to the graph
  void addEdge(string label1, string label2, unsigned long weight);
  // Function to remove an edge from the graph
  void removeEdge(string label1, string label2);
  // Function to find the shortest path between two vertices
  unsigned long shortestPath(string startLabel, string endLabel,
                             vector<string> &path);

  // Function to print the vertices and edges of the graph
  void printGraph();
  // Function to print the shortest path between two vertices
  void printShortestPath(vector<string> &path, string startLabel,
                         string endLabel);

private:
  // Stores the vertices of the graph, map label -> vertex
  unordered_map<string, Vertex *> vertices;
};

#endif // GRAPH_H