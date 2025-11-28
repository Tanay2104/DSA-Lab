#include <vector>
#include <list>

using namespace std;

class Graph 
{

  	int V; // No. of vertices
  	
  	list<int> *adj; // Pointer to an array containing adjacency list
	
	vector<int> indegree; // Vector to store indegree of vertices
	
	bool *visited; // keeps track of visited nodes during recursion
	
	vector<int> sorted; // Store a sorted sequence of nodes
	
  	bool found_cycle = false; // Flag that search has found a cycle
	
	public:
		
  		Graph(int V); // Constructor
  
  		
  		void addEdge(int v, int w); // function to add an edge to graph
  		
  		
  		void dump_dot(); // Dump graph as dotty file // To see the graph, use $xdot g.dot

		void alltopologicalSort(); // Prints all Topological Sorts
  
  		// the following two functions are for printing the results
  		void report_failed_to_sort();
  		
  		void report_a_sorted_order();
};
