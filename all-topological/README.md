# Topological Sort

## Objective

In this lab problem, we will implement topological sort on a directed acyclic graph (DAG) and generate all possible topological orderings.

## Tasks
- Implement the function alltopologicalSort() in all-topological.cpp to enumerate all valid topological sorts of a given DAG.

- Handle cases where the graph contains cycles — if a cycle is detected, print -1.

- Apart from these also implement the other functions found in the TO-DO section of all-topological.h in all-topological.cpp


## Input & Output

The main.cpp handles all input and output operations. You can view the file to see how it calls various functions.

Input Format:
Line 1: v (number of vertices)
Line 2: e (number of edges)
next e lines: u v (two numbers representing the edge between vertex u and vertex v, which is directed from u to v)

Output:
all possible topological sortings where each line will have a topological sort order where elements are separated by space

Example: 
Input:
6
5
1 2
2 4
3 4
4 5
5 6

Output: 
1 2 3 4 5 6 
1 3 2 4 5 6 
3 1 2 4 5 6


## Files to Edit (DO NOT MODIFY ANYTHING ELSE !!!!!)
1. all-topological.cpp
