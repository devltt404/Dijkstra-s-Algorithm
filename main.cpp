/*
    This file contains the main function to test the Graph class.
    Compile with command: g++ -std=gnu++11 *.cpp
    Compile and run in Windows: g++ -std=gnu++11 *.cpp & .\a.exe
*/

#include "Graph.hpp"
#include <iostream>
#include <vector>

using namespace std;

// Set up a graph with given vertices and edges
void setupGraph(Graph &graph, const vector<string> &vertices,
                const vector<tuple<string, string, unsigned long>> &edges) {
  for (const auto &vertex : vertices) {
    graph.addVertex(vertex);
  }
  for (const auto &edge : edges) {
    graph.addEdge(get<0>(edge), get<1>(edge), get<2>(edge));
  }
}

// Test the shortest path method and print results
void testShortestPath(Graph &graph, const string &start, const string &end) {
  vector<string> path;
  try {
    unsigned long distance = graph.shortestPath(start, end, path);
    graph.printShortestPath(path, start, end);
    cout << "Distance: " << distance << endl;
  } catch (const exception &e) {
    cout << "Error: " << e.what() << endl;
  }
}

// Test a graph
void testGraph(const vector<string> &vertices,
               const vector<tuple<string, string, unsigned long>> &edges,
               const pair<string, string> &labels) {
  cout << "\nGraph: " << endl;
  Graph graph;
  setupGraph(graph, vertices, edges);
  graph.printGraph();
  cout << "Query: Shortest path from " << labels.first << " to "
       << labels.second << endl;
  testShortestPath(graph, labels.first, labels.second);
}

int main() {
  // Test in PP4 Doc
  testGraph({"1", "2", "3", "4", "5", "6"},
            {{"1", "2", 7},
             {"1", "3", 9},
             {"1", "6", 14},
             {"2", "3", 10},
             {"2", "4", 15},
             {"3", "4", 11},
             {"3", "6", 2},
             {"4", "5", 6},
             {"5", "6", 9}},
            {"1", "5"});

  // Test: https://www.youtube.com/watch?v=EFg3u_E6eHU
  testGraph({"A", "B", "C", "D", "E", "F", "G"},
            {
                {"A", "C", 3},
                {"A", "F", 2},
                {"C", "F", 2},
                {"C", "E", 1},
                {"F", "E", 3},
                {"C", "D", 4},
                {"D", "B", 1},
                {"B", "G", 2},
                {"E", "B", 2},
                {"F", "B", 6},
                {"F", "G", 5},
            },
            {"A", "B"});

  // Test: Normal graph
  testGraph({"A", "B", "C", "D"},
            {{"A", "B", 1}, {"A", "C", 4}, {"B", "C", 2}, {"C", "D", 1}},
            {"A", "D"});

  // Test: Disconnected graph
  testGraph({"A", "B", "C", "D"}, {{"A", "B", 3}, {"C", "D", 5}}, {"A", "D"});

  // Test: Graph with a cycle
  testGraph({"1", "2", "3"}, {{"1", "2", 1}, {"2", "3", 1}, {"3", "1", 1}},
            {"1", "3"});

  // Test: Single vertex
  testGraph({"A"}, {}, {"A", "A"});

  // Test: Start and end are the same
  testGraph({"A", "B"}, {{"A", "B", 5}}, {"A", "A"});

  // Test: No path between start and end
  testGraph({"A", "B", "C"}, {}, {"A", "C"});

  // Test: Negative weights (invalid for Dijkstra)
  testGraph({"A", "B"}, {{"A", "B", -5}}, {"A", "B"});

  // Test: Large graph
  vector<string> vertices9;
  for (char label = 'A'; label <= 'J'; ++label) {
    vertices9.push_back(string(1, label));
  }
  testGraph(vertices9,
            {{"A", "B", 1},
             {"B", "C", 1},
             {"C", "D", 1},
             {"D", "E", 1},
             {"E", "F", 1},
             {"F", "G", 1},
             {"G", "H", 1},
             {"H", "I", 1},
             {"I", "J", 1}},
            {"A", "J"});

  // Test0: Disconnected graph but both vertices exist
  testGraph({"A", "B", "C"}, {{"A", "B", 3}}, {"A", "C"});

  // Test1: Not existing vertices
  testGraph({"A", "B"}, {{"A", "B", 1}}, {"A", "C"});

  return 0;
}