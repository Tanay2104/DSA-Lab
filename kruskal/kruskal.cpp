#include "kruskal.h"

class DisjointSet
{
private:
    std::vector<int> parent, rank;

public:
    DisjointSet(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    int find(int u)
    {
        if (parent[u] != u)
        {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    void unionSets(int u, int v)
    {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU != rootV)
        {
            if (rank[rootU] > rank[rootV])
            {
                parent[rootV] = rootU;
            }
            else if (rank[rootU] < rank[rootV])
            {
                parent[rootU] = rootV;
            }
            else
            {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};

std::vector<std::pair<int, int>> kruskalMST(Graph &graph, int &totalWeight)
{

    totalWeight = 0;
    std::vector<std::pair<int, int>> mst;
    std::vector<Edge> edges = graph.getEdges();
    std::sort(edges.begin(), edges.end(),
              [](const Edge &a, const Edge &b)
              {
                  return a.weight < b.weight;
              });

    DisjointSet ds(graph.getVertices());

    for (const Edge &edge : edges)
    {
        int u = edge.u;
        int v = edge.v;
        int weight = edge.weight;

        if (ds.find(u) != ds.find(v))
        {
            mst.push_back({u, v});
            totalWeight += weight;
            ds.unionSets(u, v);
        }
    }
    std::sort(mst.begin(), mst.end(),
              [](const std::pair<int, int> &a, const std::pair<int, int> &b)
              {
                  if (a.first == b.first)
                  {
                      return a.second < b.second;
                  }
                  return a.first < b.first;
              });

    return mst;
}