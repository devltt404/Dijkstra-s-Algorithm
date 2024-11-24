/*
  This file defines the Vertex class, which represents a vertex in a graph.
*/

#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include <unordered_map>

using namespace std;

class Vertex {
public:
  // Constructor
  Vertex(string inpLabel) : label(inpLabel) {}
  // Function to add an edge to the vertex
  void addEdge(Vertex *vertex, unsigned long weight) { edges[vertex] = weight; }
  // Function to remove an edge from the vertex
  void removeEdge(Vertex *vertex) { edges.erase(vertex); }
  // Function to check if the vertex has an edge to another vertex
  bool hasEdge(Vertex *vertex) { return edges.find(vertex) != edges.end(); }
  // Function to get the label of the vertex
  string getLabel() const { return label; }
  // Function to get the edges of the vertex
  unordered_map<Vertex *, unsigned long> getEdges() const { return edges; }

private:
  // Label of the vertex
  string label;
  // Map adjacent vertices to the edge weight
  unordered_map<Vertex *, unsigned long> edges;
};

#endif // VERTEX_H