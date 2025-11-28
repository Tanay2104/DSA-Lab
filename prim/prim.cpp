#include "prim.h"
#include <iostream>
#include <limits>

using namespace std;

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<pair<int, int>>[V];
	parent.resize(V, -1);
	key.resize(V, numeric_limits<int>::max());
}

void Graph::addEdge(int u, int v, int w)
{
	adj[u].push_back({v, w});
	adj[v].push_back({u, w});
}

void Graph::primMST(int startNode)
{
	vector<bool> inMST(V, false);

	// Clear priority queue before starting
	pq = priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>();

	key[startNode] = 0;
	pq.push({0, startNode});

	while (!pq.empty())
	{
		int u = pq.top().second;
		pq.pop();

		if (inMST[u])
		{
			continue;
		}
		
		inMST[u] = true;

		for (auto &edge : adj[u])
		{
			int v = edge.first;
			int weight = edge.second;

			if (!inMST[v] && weight < key[v])
			{
				key[v] = weight;
				pq.push({key[v], v});
				parent[v] = u;
			}
		}
	}
}

int Graph::dumpMST() const
{
    vector<pair<int,int>> edges;
    int totalWeight = 0;

    // Collect MST edges and ensure u < v
    for (int i = 0; i < V; i++)
    {
        if (parent[i] != -1)
        {
            int u = parent[i];
            int v = i;
            if (u > v)
                swap(u, v);
            edges.push_back({u, v});
            totalWeight += key[i];
        }
    }

    // Sort edges by first vertex, then second vertex
    sort(edges.begin(), edges.end());

    // Print edges
    for (auto &e : edges)
        cout << e.first << "-" << e.second << endl;

    cout << "Weight of MST: " << totalWeight << endl;

    return totalWeight;
}
