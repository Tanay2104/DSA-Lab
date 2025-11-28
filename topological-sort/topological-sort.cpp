#include "topological-sort.h"

bool topologicalSortDFSHelper(const Graph &graph, int node,
                              std::vector<bool> &visited,
                              std::vector<bool> &recStack,
                              std::vector<int> &result)
{
    if (recStack[node])
    {
        return false; // Cycle detected
    }

    if (visited[node])
    {
        return true;
    }

    visited[node] = true;
    recStack[node] = true;

    for (int neighbor : graph.adj[node])
    {
        if (!topologicalSortDFSHelper(graph, neighbor, visited, recStack, result))
        {
            return false;
        }
    }

    recStack[node] = false;
    result.push_back(node);
    return true;
}

std::vector<int> topologicalSort(const Graph &graph)
{
    std::vector<bool> visited(graph.V, false);
    std::vector<bool> recStack(graph.V, false);
    std::vector<int> result;

    for (int i = 0; i < graph.V; ++i)
    {
        if (!visited[i])
        {
            if (!topologicalSortDFSHelper(graph, i, visited, recStack, result))
            {
                return {}; // Return empty vector if cycle detected
            }
        }
    }

    std::reverse(result.begin(), result.end());
    return result;
}