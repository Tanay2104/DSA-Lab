#include <iostream>
#include <fstream>
#include "all-topological.h"

using namespace std;

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];

	for(int i = 0; i < V; i++)
	{
		indegree.push_back(0);
	}

	visited = new bool[V];
	for(int i = 0; i < V; i++)
	{
		visited[i] = false;
	}
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w);
	indegree[w]++;
}


void Graph::report_a_sorted_order()
{
	for(size_t i = 0; i < sorted.size(); i++)
	{
		cout << sorted[i] + 1 << " ";
	}
	cout << endl;
}

void Graph::report_failed_to_sort()
{
	if(found_cycle == false)
	{
		cout << "-1" << endl;
	}
	found_cycle = true;
}


void Graph::alltopologicalSort()
{
	if(V == 0)
	{
		cout << "-1" << endl;
		return;
	}

	bool flag = false;

	for(int i = 0; i < V; i++)
	{
		if(indegree[i] == 0 && !visited[i])
		{
			for(auto j : adj[i])
			{
				indegree[j]--;
			}

			sorted.push_back(i);
			visited[i] = true;

			alltopologicalSort();

			visited[i] = false;
			sorted.pop_back();

			for(auto j : adj[i])
			{
				indegree[j]++;
			}

			flag = true;
		}
	}

	if(!flag)
	{
		if(static_cast<int>(sorted.size()) == V)
		{
			report_a_sorted_order();
		}
		else
		{
			report_failed_to_sort();
		}
	}
}


void Graph::dump_dot()
{
	ofstream output("g.dot");
	output << "digraph graphname {\n";
	for(int v = 0; v < V; v++)
	{
		for(auto w : adj[v])
		{
			output << v + 1 << "->" << w + 1 << "\n";
		}
	}
	output << "}\n";
	output.close();
}
