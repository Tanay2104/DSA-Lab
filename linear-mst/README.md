

## Linear-Time Minimum Spanning Tree

### Overview

In this assignment, you will implement an algorithm to compute the **Minimum Spanning Tree (MST)** of a weighted, undirected graph in **expected linear time**.

This algorithm is based on the famous result by **Karger, Klein, and Tarjan (1995)**, who designed a **randomized MST algorithm** that achieves **expected O(E)** runtime — faster than classical algorithms like Kruskal (O(E log V)) and Prim (O(E + V log V)).

You will write your implementation in **`linear-mst.cpp`** using ideas from this paper.

---

### Problem Statement

Given an undirected weighted graph with

* `n` nodes (numbered 0 … n − 1)
* `m` edges with weights (u, v, w)

Your task is to return a set of edges forming a **Minimum Spanning Tree** (MST) — a subset of edges that connects all vertices with **minimum total weight** and contains **no cycles**.

---

### Input Format
You are given n and the set of edges as arguments to the function `linear_mst`
* Vertices are numbered from 0 to n−1.
* Edge weights are real numbers (integers or floating-point).
* The graph is guaranteed to be connected.

---

### Output Format

Return the minimum total weight of the MST.

---

### File Structure

```
.
├── main.cpp          # handles input/output and calls your function
├── linear-mst.h      # defines Edge struct and function signature
├── linear-mst.cpp    # YOU: implement the MST algorithm here
└── README.md         # this file
```

You **must not modify** `main.cpp` or `linear-mst.h`.
All your work should go into `linear-mst.cpp`.

---

### Algorithmic Background

#### Classical MST Algorithms

* **Kruskal’s Algorithm** — sorts all edges (O(E log E)) and builds MST using union-find.
* **Prim’s Algorithm** — grows MST using a priority queue (O(E + V log V)).

Both rely on sorting or priority queues, so they cannot beat O(E log V).

#### Expected Linear-Time MST (Karger–Klein–Tarjan, 1995)

The key idea is to reduce the problem recursively using **randomization** and **graph contraction**.

##### 1. Borůvka’s Steps

* Each vertex picks its lightest incident edge.
* All such edges must be in the MST.
* Contract these edges to merge vertices.
* After a few Borůvka steps, the number of vertices decreases by a constant factor.

##### 2. Random Sampling

* Randomly select about half the remaining edges.
* Compute MST of this sample recursively.
* Use the sampled MST to identify and discard **heavy edges** — edges that cannot be part of any MST.

##### 3. Filtering

* Keep only the remaining **light** edges and recursively compute MST again.
* Combine the edges from Borůvka and the filtered MSTs.

Each recursive step reduces the problem size geometrically, and the expected total work across all steps is **O(E)**.

---

### Hints for Implementation

* Implement **Union-Find (Disjoint Set Union)** for component contraction.
* Use **Borůvka steps** to contract multiple components quickly.
* Use a random generator to sample edges (e.g., Bernoulli(0.5)).
* Recurse on smaller subproblems (sample and filtered sets).
* Fall back to **Kruskal’s algorithm** for very small edge sets (e.g., ≤ 2n edges).

---

### Reference

* **Karger, D. R., Klein, P. N., & Tarjan, R. E. (1995).**
  *A randomized linear-time algorithm to find minimum spanning trees.*
  *Journal of the ACM (JACM)*, 42(2), 321–328.
  DOI: [10.1145/201019.201022](https://doi.org/10.1145/201019.201022)
* You can also look at the wikipedia page or google for resources to understand how the algorithm works


