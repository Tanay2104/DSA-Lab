#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <utility>

struct Edge
{
    int u, v, weight;
    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}
};

class Graph
{
private:
    int vertices;
    std::vector<Edge> edges;

public:
    Graph(int v);
    void addEdge(int u, int v, int weight);
    int getVertices() const;
    const std::vector<Edge> &getEdges() const;
    void sortEdges();
};

#endif