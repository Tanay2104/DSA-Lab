// main.cpp
#include <iostream>
#include <vector>
#include <queue>      // For std::priority_queue (the reference implementation)
#include <cstdlib>    // For rand()
#include <ctime>      // For time()
#include <stdexcept>
#include <string>

#include "heap.h"

// --- Test Configuration ---
const int NUM_TEST_CASES = 100;
const int HEAP_SIZE = 500;
const int MAX_OPERATIONS = 2000;
const int MAX_VALUE = 10000;

// --- Helper Function for Reporting ---
void print_result(const std::string& test_name, bool success) {
    if (success) {
        std::cout << "[PASS] " << test_name << std::endl;
    } else {
        std::cout << "[FAIL] " << test_name << std::endl;
    }
}

// --- Comparison Function ---
// Compares your heap with the standard priority_queue.
// Note: This function is destructive; it empties both heaps to compare them.
bool compare_heaps(Heap& my_heap, std::priority_queue<int>& std_pq) {
    if (my_heap.get_size() != (int)std_pq.size()) {
        std::cerr << "  [ERROR] Size mismatch! Your heap size: " << my_heap.get_size() 
                  << ", std::priority_queue size: " << std_pq.size() << std::endl;
        return false;
    }

    while (!my_heap.is_empty()) {
        int my_max = -1;
        int std_max = -1;

        try {
            // std::cout << "trying..." << std::endl;
            my_max = my_heap.delete_max();
            std_max = std_pq.top();
            std_pq.pop();
        } catch (...) {
             std::cerr << "  [ERROR] An exception was thrown during heap extraction." << std::endl;
             return false;
        }


        if (my_max != std_max) {
            std::cerr << "  [ERROR] Mismatch during extraction! Your max: " << my_max
                      << ", Expected max: " << std_max << std::endl;
            return false;
        }
    }
    return true;
}


int main() {
    srand(time(0)); // Seed random number generator

    std::cout << "Starting Heap Implementation Test Suite..." << std::endl;
    std::cout << "==========================================" << std::endl;

    bool all_tests_passed = true;

    // --- Test 1: Testing `insert` functionality ---
    bool insert_ok = true;
    for (int i = 0; i < NUM_TEST_CASES; ++i) {
        Heap my_heap;
        // std::cout << "Heap initialised successfully" << std::endl;
        std::priority_queue<int> std_pq;
        
        for (int j = 0; j < HEAP_SIZE; ++j) {
            int val = rand() % MAX_VALUE;
            my_heap.insert(val);
            std_pq.push(val);
        }
        // std::cout << "Insertions completed successfully" << std::endl;
        if (!compare_heaps(my_heap, std_pq)) {
            std::cerr << "-> Test case " << i << " failed for insert." << std::endl;
            insert_ok = false;
            break;
        }
    }
    print_result("Test 1: Insert Operations", insert_ok);
    if (!insert_ok) all_tests_passed = false;


    // --- Test 2: Testing `build_heap` functionality ---
    // NOTE: This test assumes `build_heap` is intended to populate the heap's internal array.
    bool build_heap_ok = true;
    for (int i = 0; i < NUM_TEST_CASES; ++i) {
        std::vector<int> data;
        for (int j = 0; j < HEAP_SIZE; ++j) {
            data.push_back(rand() % MAX_VALUE);
        }

        Heap my_heap;
        // The test calls your function as is.
        my_heap.build_heap(data.data(), data.size());

        // The reference heap is built from the same data.
        std::priority_queue<int> std_pq(data.begin(), data.end());

        if (!compare_heaps(my_heap, std_pq)) {
            std::cerr << "-> Test case " << i << " failed for build_heap." << std::endl;
            build_heap_ok = false;
            break;
        }
    }
    print_result("Test 2: Build Heap Operations", build_heap_ok);
    if (!build_heap_ok) all_tests_passed = false;


    // --- Test 3: Mixed Operations (Stress Test) ---
    bool mixed_op_ok = true;
    for (int i = 0; i < NUM_TEST_CASES; ++i) {
        Heap my_heap;
        std::priority_queue<int> std_pq;
        bool current_test_failed = false;

        for (int j = 0; j < MAX_OPERATIONS; ++j) {
            int op = rand() % 3; // 2/3 chance of insert, 1/3 chance of delete

            if (op < 2 || std_pq.empty()) { // Insert operation
                int val = rand() % MAX_VALUE;
                my_heap.insert(val);
                std_pq.push(val);
            } else { // Delete operation
                try {
                    int my_max = my_heap.maximum();
                    int std_max = std_pq.top();
                    if(my_max != std_max) {
                        std::cerr << "  [ERROR] Mismatch on maximum() before delete! Your max: " << my_max
                                  << ", Expected max: " << std_max << std::endl;
                        current_test_failed = true;
                        break;
                    }
                    my_heap.delete_max();
                    std_pq.pop();
                } catch (const std::exception& e) {
                    std::cerr << "  [ERROR] Your heap threw an exception on delete/max when it was not empty: " << e.what() << std::endl;
                    current_test_failed = true;
                    break;
                } catch (...) {
                    std::cerr << "  [ERROR] Your heap threw an unknown exception on delete/max when it was not empty." << std::endl;
                    current_test_failed = true;
                    break;
                }
            }
        }

        if (current_test_failed) {
            mixed_op_ok = false;
            break;
        }

        // Final comparison after all operations
        if (!compare_heaps(my_heap, std_pq)) {
            std::cerr << "-> Test case " << i << " failed for mixed operations during final verification." << std::endl;
            mixed_op_ok = false;
            break;
        }
    }
    print_result("Test 3: Mixed Insert/Delete Stress Test", mixed_op_ok);
    if (!mixed_op_ok) all_tests_passed = false;


    std::cout << "==========================================" << std::endl;
    if (all_tests_passed) {
        std::cout << "All tests passed successfully!" << std::endl;
    } else {
        std::cout << "One or more test suites failed. Please review the output above." << std::endl;
    }

    return 0;
}