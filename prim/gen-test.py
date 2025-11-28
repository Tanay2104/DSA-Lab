import os
import random
import heapq

# ==============================
# CONFIGURATION
# ==============================
TESTS_FOLDER = "tests"
START_INDEX = 5
NUM_TESTS_PER_SIZE = 3

SMALL_RANGE = (20, 50)
MEDIUM_RANGE = (100, 200)
LARGE_RANGE = (500, 1000)

SEED = 1234
MAX_EDGE_WEIGHT = 1000  # Maximum weight for edges

random.seed(SEED)

# ==============================
# Helper functions
# ==============================
def generate_graph(num_vertices, extra_edges_ratio=2):
    """
    Generates a connected undirected weighted graph.
    Ensures there is at least one spanning tree.
    extra_edges_ratio controls number of extra edges beyond a tree.
    """
    edges = []

    # Create a spanning tree first (guarantees connectivity)
    vertices = list(range(num_vertices))
    random.shuffle(vertices)
    for i in range(1, num_vertices):
        u = vertices[i]
        v = vertices[random.randint(0, i - 1)]
        w = random.randint(1, MAX_EDGE_WEIGHT)
        edges.append((u, v, w))

    # Add extra random edges
    max_edges = int(num_vertices * extra_edges_ratio)
    while len(edges) < max_edges:
        u, v = random.sample(range(num_vertices), 2)
        if any((u == a and v == b) or (u == b and v == a) for a, b, _ in edges):
            continue
        w = random.randint(1, MAX_EDGE_WEIGHT)
        edges.append((u, v, w))

    return edges

def prim_mst(num_vertices, edges, start_node):
    """
    Compute MST using Prim's algorithm and return:
    - List of edges (u, v) with u < v
    - Total weight
    """
    adj = [[] for _ in range(num_vertices)]
    for u, v, w in edges:
        adj[u].append((v, w))
        adj[v].append((u, w))

    key = [float('inf')] * num_vertices
    parent = [-1] * num_vertices
    in_mst = [False] * num_vertices

    key[start_node] = 0
    pq = [(0, start_node)]

    while pq:
        _, u = heapq.heappop(pq)
        if in_mst[u]:
            continue
        in_mst[u] = True
        for v, w in adj[u]:
            if not in_mst[v] and w < key[v]:
                key[v] = w
                parent[v] = u
                heapq.heappush(pq, (key[v], v))

    mst_edges = []
    total_weight = 0
    for i in range(num_vertices):
        if parent[i] != -1:
            u, v = parent[i], i
            if u > v:
                u, v = v, u
            mst_edges.append((u, v))
            total_weight += key[i]

    mst_edges.sort()
    return mst_edges, total_weight

def save_testcase(index, num_vertices, edges, start_node, mst_edges, total_weight):
    folder = os.path.join(TESTS_FOLDER, f"test{index}")
    os.makedirs(folder, exist_ok=True)

    # Input
    input_path = os.path.join(folder, "input.txt")
    with open(input_path, "w") as f:
        f.write(f"{num_vertices}\n")
        f.write(f"{len(edges)}\n")
        for u, v, w in edges:
            f.write(f"{u} {v} {w}\n")
        f.write(f"{start_node}\n")

    # Output
    output_path = os.path.join(folder, "output.txt")
    with open(output_path, "w") as f:
        for u, v in mst_edges:
            f.write(f"{u}-{v}\n")
        f.write(f"Weight of MST: {total_weight}\n")

# ==============================
# Generate tests
# ==============================
def generate_tests():
    index = START_INDEX
    size_categories = [
        ("small", SMALL_RANGE),
        ("medium", MEDIUM_RANGE),
        ("large", LARGE_RANGE),
    ]

    for category_name, (v_min, v_max) in size_categories:
        for _ in range(NUM_TESTS_PER_SIZE):
            num_vertices = random.randint(v_min, v_max)
            edges = generate_graph(num_vertices)
            start_node = random.randint(0, num_vertices - 1)
            mst_edges, total_weight = prim_mst(num_vertices, edges, start_node)
            save_testcase(index, num_vertices, edges, start_node, mst_edges, total_weight)
            print(f"Generated {category_name} test{index}: {num_vertices} vertices, {len(edges)} edges")
            index += 1

if __name__ == "__main__":
    generate_tests()

