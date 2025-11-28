#include "kruskal.h"

Graph::Graph(int v) : vertices(v) {}

void Graph::addEdge(int u, int v, int weight)
{
    if (u > v)
        std::swap(u, v);
    edges.emplace_back(u, v, weight);
}

int Graph::getVertices() const
{
    return vertices;
}

const std::vector<Edge> &Graph::getEdges() const
{
    return edges;
}

void Graph::sortEdges()
{
    std::sort(edges.begin(), edges.end(),
              [](const Edge &a, const Edge &b)
              {
                  return a.weight < b.weight;
              });
}