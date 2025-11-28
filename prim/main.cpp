#include <iostream>
#include "prim.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc > 1) {
        if (freopen(argv[1], "r", stdin) == nullptr) // cin redirects to file argv[1]
        {
            std::cerr << "Error: Could not open input file " << argv[1] << std::endl;
            return 1;
        }
    }
	int V, E;
	cin >> V;  // first line: number of vertices
	cin >> E;  // second line: number of edges

	Graph g(V);

	for (int i = 0; i < E; i++)
	{
		int u, v, w;
		cin >> u >> v >> w; // next E lines: edges
		g.addEdge(u, v, w);
	}

	int startNode;
	cin >> startNode; // last line: start node

	g.primMST(startNode);
	g.dumpMST();

	return 0;
}
