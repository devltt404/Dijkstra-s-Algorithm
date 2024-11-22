/*
  This file defines the Edge class, which represents an edge in a graph.
*/

#ifndef EDGE_H
#define EDGE_H

#include "Vertex.hpp"

class Edge {
public:
  // Constructor
  Edge(Vertex *source, Vertex *destination, unsigned long weight)
      : source(source), destination(destination), weight(weight) {};

private:
  Vertex *source;
  Vertex *destination;
  unsigned long weight;
};

#endif // EDGE_H