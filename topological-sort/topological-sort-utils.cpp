#include "topological-sort.h"
#include <iostream>

Graph::Graph(int v, const std::vector<std::pair<int, int>> &edges) : V(v)
{
    adj.resize(V);
    for (auto [u, w] : edges)
    {
        adj[u].push_back(w);
    }
}
void Graph::addEdge(int u, int v, int directed)
{
    if (V <= std::max(u, v))
    {
        V = std::max(u, v) + 1;
        adj.resize(V);
    }
    adj[u].push_back(v);
    if (!directed)
    {
        if (V <= std::max(v, u))
        {
            V = std::max(v, u) + 1;
            adj.resize(V);
        }
        adj[v].push_back(u);
    }
}