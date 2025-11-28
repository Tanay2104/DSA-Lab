#ifndef PRIM_H
#define PRIM_H

#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <utility>
#include <functional>

using namespace std;

class Graph
{
	int V;  // Number of vertices
	list<pair<int, int>> *adj; // Adjacency list: (neighbor, weight)

	//Syntax of priority queue: priority_queue<Type, Container, Comparator>
	//Type: The type of element we want to store in queue
	//Container: What Data Structure should the queue uses for storing it internally
	//Comparator: comparision function to sort the elements
	//We are using "greater" to sort the queue in non-decreasing order
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	


	public:
		vector<int> parent; // parent of each node in MST
		vector<int> key;    // weight of edge connecting node to MST

		Graph(int V);                        // Constructor
		void addEdge(int u, int v, int w);   // Add an edge
		void primMST(int startNode);         // Compute MST (fills parent & key)
		int dumpMST() const;                 // Print MST edges and return total weight
};

#endif
