#!/usr/bin/env python3
import os
import random
import subprocess

# ==============================
# CONFIGURATION
# ==============================
TESTS_FOLDER = "tests"
START_INDEX = 6
NUM_TESTS_PER_SIZE = 5  # additional acyclic tests
SMALL_RANGE = (5, 15)
SEED = 1234
EXECUTABLE = "./all-topological"  # compiled program that produces topological sort

random.seed(SEED)

# ==============================
# Utility functions
# ==============================
def generate_dag(n_vertices, max_edges_factor=2):
    """Generate a random DAG."""
    edges = set()
    max_edges = n_vertices * max_edges_factor
    vertices = list(range(1, n_vertices + 1))
    
    while len(edges) < max_edges:
        u = random.choice(vertices)
        v = random.choice(vertices)
        if u != v and (u, v) not in edges and (v, u) not in edges:
            if u < v:  # ensures acyclicity
                edges.add((u, v))
    return list(edges)

def generate_cyclic_graph(n_vertices):
    """Generate a graph with a single cycle."""
    edges = []
    for i in range(1, n_vertices):
        edges.append((i, i+1))
    # add a cycle: last -> first
    edges.append((n_vertices, 1))
    return edges

def write_test(test_dir, n, edges):
    os.makedirs(test_dir, exist_ok=True)
    input_file = os.path.join(test_dir, "input.txt")
    with open(input_file, "w") as f:
        f.write(f"{n}\n")
        f.write(f"{len(edges)}\n")
        for u, v in edges:
            f.write(f"{u} {v}\n")
    return input_file

def generate_output(input_file, output_file):
    """Run the program to generate output.txt."""
    with open(output_file, "w") as f:
        subprocess.run([EXECUTABLE], stdin=open(input_file), stdout=f)

# ==============================
# Main function
# ==============================
def create_tests():
    os.makedirs(TESTS_FOLDER, exist_ok=True)
    
    index = START_INDEX

    for size_name, size_range in [("small", SMALL_RANGE)]:
        # 1 cyclic test
        n_cyclic = random.randint(*size_range)
        edges = generate_cyclic_graph(n_cyclic)
        test_dir = os.path.join(TESTS_FOLDER, f"test{index}")
        input_file = write_test(test_dir, n_cyclic, edges)
        output_file = os.path.join(test_dir, "output.txt")
        generate_output(input_file, output_file)
        print(f"Generated {size_name} cyclic test {index}: V={n_cyclic}, E={len(edges)}")
        index += 1

        # additional acyclic tests
        for _ in range(NUM_TESTS_PER_SIZE):
            n = random.randint(*size_range)
            edges = generate_dag(n)
            test_dir = os.path.join(TESTS_FOLDER, f"test{index}")
            input_file = write_test(test_dir, n, edges)
            output_file = os.path.join(test_dir, "output.txt")
            generate_output(input_file, output_file)
            print(f"Generated {size_name} acyclic test {index}: V={n}, E={len(edges)}")
            index += 1

if __name__ == "__main__":
    create_tests()
