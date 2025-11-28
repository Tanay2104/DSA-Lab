#ifndef TOPOLOGICAL_H
#define TOPOLOGICAL_H

#include <vector>
#include <utility>

class Graph
{
public:
    int V;                             // number of vertices
    std::vector<std::vector<int>> adj; // adjacency list

    Graph() : V(0) {}
    Graph(int v, const std::vector<std::pair<int, int>> &edges);
    void addEdge(int u, int v, int directed);
};

// Separate topological sort function that takes Graph as parameter
std::vector<int> topologicalSort(const Graph &graph);

#endif