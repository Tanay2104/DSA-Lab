# Graph DFS and Topological Sort

The adj in GraphNode is the adjacency list for each node. It contains pairs of values
which indicate the label of the node (first value) and the weight of the edge (second
value). The weights do not matter for this lab. All edges are directed.

Your task is to implement the function topoSort. This function should do a topological
sort of the given Graph. Topological ordering of a directed graph is a linear ordering
of its vertices such that for every directed edge u->v from vertex u to vertex v, u comes
before v in the ordering.

The output should be stored into the vector such that the main driver code function can
appropriately print it. You can use the dfs helper function that has been added to
the class, but you cannot remove the main topologicalSort function.
If a cycle is present then return empty vector.

To check your implementation, run "make". There could be more than one correct
topological sort outputs in general, but assume that the input will be such that
all adjacency lists will have labels in increasing order.

Input format:

N

E

e1 (in u,v pair)

e2

e3

e4

.
.
eE

Output format is the topologically sorted node labels.
