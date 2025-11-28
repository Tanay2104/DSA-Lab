#include <iostream>
#include "all-topological.h"

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
	cin >> V;
	cin >> E;

	Graph g(V);

	for(int i = 0; i < E; i++)
	{
		int u, v;
		cin >> u >> v;
		u--; // convert to 0-indexed
		v--;
		g.addEdge(u, v);
	}

	g.dump_dot();
	g.alltopologicalSort();

	return 0;
}

