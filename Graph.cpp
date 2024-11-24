/*
  This file contains the Graph class implementation.
*/

#include "Graph.hpp"
#include "Vertex.hpp"
#include <algorithm>
#include <iostream>
#include <limits.h>
#include <queue>
#include <stdexcept>

using namespace std;

// Constructor
Graph::Graph() {}
// Destructor
Graph::~Graph() {
  // Iterate through the vertices and delete them
  for (auto &vertexPair : vertices) {
    delete vertexPair.second;
  }
}

// Add a vertex to the graph
void Graph::addVertex(string label) {
  // Add the new vertex if it doesn't exist
  if (vertices.find(label) == vertices.end()) {
    vertices[label] = new Vertex(label);
  } else {
    throw invalid_argument("The vertex already exists.");
  }
}

// Remove a vertex from the graph
void Graph::removeVertex(string label) {
  // Find the iterator for the vertex with given lable
  auto vertexIt = vertices.find(label);

  // If the vertex exists, remove it
  if (vertexIt != vertices.end()) {
    Vertex *vertexToRemove = vertexIt->second;

    // Iterate through adjacent vertices of the vertex to remove
    for (auto &adjVertexPair : vertexToRemove->getEdges()) {
      // Remove the edge from the adjacent vertex to the vertex to remove
      adjVertexPair.first->removeEdge(vertexToRemove);
    }

    // Delete the vertex and remove it from the vertices map
    delete vertexToRemove;
    vertices.erase(vertexIt);
  }
}

// Add an edge to the graph
void Graph::addEdge(string label1, string label2, unsigned long weight) {
  // Check if the both vertices exist
  if (vertices.find(label1) == vertices.end() ||
      vertices.find(label2) == vertices.end()) {
    throw invalid_argument("Some of the vertices do not exist.");
  }

  // A vertex can not have an edge to itself
  if (label1 == label2) {
    throw invalid_argument("Start and end vertices can not be the same.");
  }

  // Get the pointers to vertices with the given labels
  Vertex *vertex1 = vertices[label1];
  Vertex *vertex2 = vertices[label2];

  // There must not already be an edge between the vertices
  if (vertex1->hasEdge(vertex2) || vertex2->hasEdge(vertex1)) {
    throw invalid_argument("The edge already exists.");
  }

  // Add the edge between the vertices
  vertex1->addEdge(vertex2, weight);
  vertex2->addEdge(vertex1, weight);
}

// Remove an edge from the graph
void Graph::removeEdge(string label1, string label2) {
  // Check if the both vertices exist
  if (vertices.find(label1) == vertices.end() ||
      vertices.find(label2) == vertices.end()) {
    throw invalid_argument("Some of the vertices do not exist.");
  }

  // Get the pointers to vertices with the given labels
  Vertex *vertex1 = vertices[label1];
  Vertex *vertex2 = vertices[label2];

  // There must be an edge between the vertices
  if (!vertex1->hasEdge(vertex2) || !vertex2->hasEdge(vertex1)) {
    throw invalid_argument("The edge does not exist.");
  }

  // Remove the edge between the vertices
  vertex1->removeEdge(vertex2);
  vertex2->removeEdge(vertex1);
}

// CompareVertex struct to compare vertices based on the distance
struct CompareVertex {
  bool operator()(std::pair<Vertex *, unsigned long> &a,
                  std::pair<Vertex *, unsigned long> &b) {
    return a.second >
           b.second; // Min-heap: smaller distance has higher priority
  }
};

/*
  Find the shortest path between two vertices using Dijkstra's algorithm.
*/
unsigned long Graph::shortestPath(string startLabel, string endLabel,
                                  vector<string> &path) {
  // Check if the vertices exist
  if (vertices.find(startLabel) == vertices.end() ||
      vertices.find(endLabel) == vertices.end()) {
    throw invalid_argument("Some of the vertices do not exist.");
  }

  unordered_map<Vertex *, unsigned long> distances; // To store the distances
  unordered_map<Vertex *, bool> visited; // To keep track of visited vertices
  unordered_map<Vertex *, Vertex *> previous; // To store the previous vertex

  // Create a min-heap priority queue to store the vertices with their distances
  priority_queue<pair<Vertex *, unsigned long>,
                 vector<pair<Vertex *, unsigned long>>, CompareVertex>
      pq;

  // Get the start and end vertices
  Vertex *startVertex = vertices[startLabel];
  Vertex *endVertex = vertices[endLabel];

  // Iterate through the vertices and initialize the distances, visited and
  // previous vertex
  for (auto &vertexPair : vertices) {
    distances[vertexPair.second] = ULONG_MAX; // Set the distance to infinity
    visited[vertexPair.second] = false;       // Mark the vertex as not visited
    previous[vertexPair.second] = nullptr;    // Set the previous vertex to null
  }

  // Set the distance of the start vertex to 0
  distances[startVertex] = 0;

  // Add the start vertex to the priority queue
  pq.push({startVertex, 0});

  // Implement Dijkstra's algorithm
  while (!pq.empty()) {
    // Get and pop the vertex with the smallest distance
    Vertex *currentVertex = pq.top().first;
    pq.pop();

    // If the vertex is already visited, skip it
    if (visited[currentVertex])
      continue;

    // Mark the vertex as visited
    visited[currentVertex] = true;

    // If the current vertex is the end vertex, break the loop
    if (currentVertex == endVertex) {
      break;
    }

    for (auto &adjVertexPair : currentVertex->getEdges()) {
      // Calculate the new distance
      unsigned long newDistance =
          distances[currentVertex] + adjVertexPair.second;

      // If the new distance is smaller than the current distance, update the
      // distance and previous vertex
      if (newDistance < distances[adjVertexPair.first]) {
        distances[adjVertexPair.first] = newDistance;
        previous[adjVertexPair.first] = currentVertex;

        // Push the adjacent vertex to the priority queue with the new distance
        pq.push({adjVertexPair.first, newDistance});
      }
    }
  }

  // Clear the path vector to store the new path
  path.clear();

  // If the end vertex is not visited, return infinity to indicate that there is
  // no valid path
  if (!visited[endVertex]) {
    return ULONG_MAX;
  }

  Vertex *currentVertex = endVertex;
  // Iterate through the previous vertices and add the labels to the end of the
  // path vector
  while (currentVertex != nullptr) {
    path.push_back(currentVertex->getLabel());
    currentVertex = previous[currentVertex];
  }

  // Reverse the path to get the correct order
  reverse(path.begin(), path.end());

  // Return the distance between the start and end vertices
  return distances[endVertex];
}

// Print the shortest path
void Graph::printShortestPath(vector<string> &path, string startLabel,
                              string endLabel) {
  // If the path is empty, print that there is no valid path
  if (path.empty()) {
    cout << "There is no valid path from " << startLabel << " to " << endLabel
         << endl;
    return;
  }

  // Print the shortest path
  cout << "Shortest Path from " << startLabel << " to " << endLabel << ": ";
  for (size_t i = 0; i < path.size(); ++i) {
    cout << path[i];
    if (i != path.size() - 1) {
      cout << " -> ";
    }
  }
  cout << endl;
}

// Print the graph
void Graph::printGraph() {
  // Print the vertices
  cout << "Vertices: ";
  for (auto &vertexPair : vertices) {
    cout << vertexPair.first << " ";
  }
  cout << endl;

  // Print the edges
  cout << "Edges: " << endl;
  for (auto &vertexPair : vertices) {
    Vertex *vertex = vertexPair.second;
    for (auto &adjVertexPair : vertex->getEdges()) {
      cout << "\t" << vertex->getLabel() << " -> "
           << adjVertexPair.first->getLabel()
           << " (Weight: " << adjVertexPair.second << ")" << endl;
    }
  }
}