#include "kruskal.h"

std::vector<std::pair<int, int>> kruskalMST(Graph &graph, int &totalWeight);

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        if (freopen(argv[1], "r", stdin) == nullptr)
        {
            std::cerr << "Error: Could not open input file " << argv[1] << std::endl;
            return 1;
        }
    }

    int vertices, edges;
    std::cin >> vertices >> edges;

    Graph g(vertices);

    for (int i = 0; i < edges; i++)
    {
        int u, v, weight;
        std::cin >> u >> v >> weight;
        g.addEdge(u, v, weight);
    }

    int startNode;
    std::cin >> startNode;

    int totalWeight;
    std::vector<std::pair<int, int>> mstEdges = kruskalMST(g, totalWeight);

    for (size_t i = 0; i < mstEdges.size(); ++i)
    {
        std::cout << mstEdges[i].first << "-" << mstEdges[i].second;
        if (i < mstEdges.size() - 1)
        {
            std::cout << std::endl;
        }
    }
    if (!mstEdges.empty())
    {
        std::cout << std::endl;
    }
    std::cout << "Weight of MST: " << totalWeight << std::endl;

    return 0;
}