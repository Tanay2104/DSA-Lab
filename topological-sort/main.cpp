// ----------------------------
//       DO NOT MODIFY
// ----------------------------

#include <iostream>
#include "topological-sort.h"

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

    int N, E;
    std::cin >> N >> E;
    Graph g;
    for (int i = 0; i < E; i++)
    {
        int u, v;
        std::cin >> u >> v;
        g.addEdge(u, v, 1);
    }
    std::vector<int> topoOrder = topologicalSort(g);

    // Print the result in main
    for (size_t i = 0; i < topoOrder.size(); ++i)
    {
        std::cout << topoOrder[i];
        if (i < topoOrder.size() - 1)
        {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}