# MST FROM PRIM

## Objective

In this lab problem, we will implement Prims Algorithm, a famous MST producing algorithm with the help of a priority queue. We will do this for an Undirected Graph.


## Prims Algorithm

The basic Prims Algorithm Works as Follows:

1. Pick an arbitrary starting vertex.

2. Repeat until all vertices are included:

    - Identify all edges connecting the current MST vertices (vertices that are part of the MST) to non-MST vertices(vertices that are not added to the MST yet).

    - Choose the minimum weight edge among these.

    - Add it to the MST. (The vertices that belong to this edge are now part of the MST)

3. Return MST.

This is the naive Prims Algorithm. The loop runs one time for each vertex, so O(V). Everytime we need to find the minimum weighted edge for that vertex, which takes O(V) each time. So in total we have a time complexity of O(V^2).

But in this problem we will implement an optimized version of Prims Algorithm that uses Priority Queue. Priority Queue in this problem contains a pair as one element. The first element of the pair is a weight. The second element of the pair is the neighbor of the current vertex. You can see the declaration of the Priority Queue in prim.h.

The Prims Algorithm with Priority Queue works as follows:

1. Pick a starting vertex.

2. Maintain a priority queue (min-heap) of (weight, vertex) for non-MST vertices.

3. While the queue is not empty:

    - Pop the vertex with the minimum key (weight to MST).

    - Mark it as included in MST.

    - For each neighbor, if not in MST and edge weight < current key:

    - Update key and parent.

    - Push into priority queue.

4. Return MST.

Here key is the minimum weight of any edge connecting vertex v to the current MST. We will use an array to store the key values. key[i] represents key of vertex "i".

We will use a parent array to store which edges are added to the MST.

To understand what key, parent means go through the following example which illustrates step-by-step action the algorithm takes.

We will understand this using an example:

Let us consider a graph where we have vertices 0, 1, 2, 3 & 4 with the following edges and weights
u - v : w
0 - 1 : 2
0 - 3 : 6
1 - 2 : 3
1 - 3 : 8
1 - 4 : 5
2 - 4 : 7
3 - 4 : 1

Let the starting node be 0 and pq be our priority queue.

We initially add {0,0} to pq as distance to "0" from "0" is zero and it is the starting node. "0" is now part of the MST. key of "0" is zero.

Initial key array: [0, Inf, Inf, Inf, Inf]
Initial Parent array: [0, -1, -1, -1, -1]
Current MST: {}

The first iteration is as follows:
    - Pop the first element of pq which is {0, 0}. So current vertex is "0". pq is now empty.
    
    - "0" is now part of MST.
    
    - Now we look at all the neighbors of "0" which are: "1" and "3".
    
    - Both the vertices are currently not part of the MST. So for both the vertices key is Infinite as there is no edge between the current MST and these vertices.
    
    - For 0-1: 2 < Infinite is true, so we add {2,1} to pq ({wight of edge to the neighbor, neighbor} pair)
    
    - For 0-3: 6 < Infinite is true, so we add {6,3} to pq
    
    - pq internally sorts them by weight. So state of pq is [ {2,1}, {6,3} ]
    
    - key of vertex "1" is updated to 2, and key of vertex "3" is updated to 6. key is minimum weight of the edge that connects the vertices to already existing MST. Since previously "1" is not connected to the MST, its distance from MST is Infinite. In the current MST "0" is the only one that has an edge to "1". So the minimum weighted edge that connects the current MST to the vertex "1" is 2. So key of "1" is 2. Similarly for "3" key is 6
    
    - parent of both "1" and "3" is set to "0"
    
Current MST: {0}
Key array: [0, 2, Inf, 6, Inf]
Parent array: [0, 0, -1, 0, -1]

Second Iteration:
    - Pop the first element of pq which is {2, 1}. So current vertex is "1". pq is now [ {6,3} ].
    
    - "1" is now part of MST.
    
    - Now we look at all the neighbors of "1" which are: "0", "2","3" and "4".
    
    - "0" is already part of MST, so we ignore it.
    
    - key of "2" is Infinite as it is not part of MST. So for 1-2: 3 < Infinite is true, so we add {3, 2} to pq.
    
    - key of "3" is 6. Distance between current vertex "1" and "3" is 8. So for 1-3: 8 < 6 is false, so we skip this edge.
    
    - key of "4" is Infinite as it is not part of MST. So for 1-4: 5 < Infinite is true, so we add {5, 4} to pq.
    
    - pq internally sorts them by weight. So state of pq is [ {3,2}, {5,4}, {6,3} ]
    
    - keys of "2" and "4" are updated to 3 and 5 respectively.
    
    - parent of both "2" and "4" is set to "1".

Current MST: {0, 1}
Key array: [0, 2, 3, 6, 5]
Parent array: [0, 0, 1, 0, 1]

Third Iteration:
    - Pop the first element of pq which is {3, 2}. So current vertex is "2". pq is now [ {5,4}, {6,3} ].
    
    - "2" is now part of MST.
    
    - Now we look at all the neighbors of "2" which are: "1" and "4".
    
    - "1" is already part of MST so we ignore it.
    
    - key of "4" is 5. So for 2-4: 7 < 5 is false, so we skip this edge.
    
    - Current state state of pq is [ {5,4}, {6,3} ]

Current MST: {0, 1, 2}
Key array: [0, 2, 3, 6, 5]
Parent array: [0, 0, 1, 0, 1]


Fourth Iteration:
    - Pop the first element of pq which is {5, 4}. So current vertex is "4". pq is now [ {6,3} ].
    
    - "4" is now part of MST.
    
    - Now we look at all the neighbors of "4" which are: "1", "2" and "3".
    
    - "1" and "2" are already part of MST so we ignore them.
    
    - key of "3" is 6. So for 3-4: 1 < 6 is true, so we add {1, 3} to pq.
    
    - key of "3" is updated to 1.
    
    - parent of "3" is set to 4.
    
    - Current state state of pq is [ {1,3}, {6,3} ]

Current MST: {0, 1, 2, 4}
Key array: [0, 2, 3, 1, 5]
Parent array: [0, 0, 1, 4, 1]

Fifth Iteration:
    - Pop the first element of pq which is {1, 3}. So current vertex is "3". pq is now [ {6,3} ].
    
    - "3" is now part of MST.
    
    - Now we look at all the neighbors of "3" which are: "0", "1" and "4".
    
    - All are part of MST, so we ignore them.
    
    - Current state state of pq is [ {6,3} ]
    
Current MST: {0, 1, 2, 4, 3}
Key array: [0, 2, 3, 1, 5]
Parent array: [0, 0, 1, 4, 1]


Similarly in the sixth iteration we will not make any new additions to pq and key and parent arrays do not change. So this ends here.

Using the Parent Array we can now see what edges are added to the MST.

0-1, 1-2, 3-4, 1-4 are the edges we add to MST.

So MST looks like:

                    0
                
                /       \
                
            1               4
            
        /                       \
        
    2                               3
    

The time complexity if this implementation is O(E x log(V)). Why do you think so?

## Tasks
- Implement the function primMST() in prim.cpp to find the MST of a graph. This is to be done using a priority queue.

- Apart from that also implement the other functions prim.cpp 

## Input & Output

The main.cpp handles all input. You can view the file to see how it calls various functions. You need to print the edges in dumpMST().

Input Format:
Line 1: v (number of vertices)
Line 2: e (number of edges)
next e lines: u v w(three numbers representing the edge between vertex u and vertex v, which has a weight w)
last line: startNode (the node at which we start building the MST)

Output:
Lines containing edges of the MST in the format u-v. The last line contains the weight of the MST

Example: 
Input:
5
7
0 1 2
0 3 6
1 2 3
1 3 8
1 4 5
2 4 7
3 4 9
0

Output: 
0-1
0-3
1-2
1-4
Weight of MST: 16


**Note:** If we have edges in the format u-v: 
    - u is less than v 
    - edges are ordered according to u
    - if u is same for two edges, we order them by v
    
In the above output you can see that when ordered by u both 0-3 and 0-1 will come before 1-2 and 1-4. Since there are two ties we order them according to v. So 0-1 comes first, then 0-3, then 1- and at last 1-4. 

There should not be any edge like 4-3 in the output as 4 > 3.
    
## Files to Edit (DO NOT MODIFY ANYTHING ELSE !!!!!)
1. prim.cpp
