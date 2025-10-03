#include "heap.h"
#include <iostream>
void Heap::expand() {
    // std::cout << "Expanding array" << std::endl;
    int new_size = max_size*2;
    int * tmp = new int[new_size];
    for (int i=0; i < new_size; i++) {
        tmp[i] = array[i];
    }
    delete array;
    array = tmp;
    max_size = new_size;
}

int Heap::maximum() {
    return array[0];
}
void Heap::insert(int key) {
    if (N==max_size) {
        Heap::expand();
    }
    // std::cout << "N < size" << std::endl;
    array[N] = key;
    // std::cout << "First element: " << array[0] << std::endl;
    int idx = N;
    while (idx > 0 && array[parent(idx)] < array[idx]) {
        // std::cout << "Initially a=" << array[parent(idx)] << " and b=" << array[idx] << std::endl;
        Heap::my_swap(array[parent(idx)], array[idx]);
        // std::cout << "Finally a=" << array[parent(idx)] << " and b=" << array[idx] << std::endl;
        idx = parent(idx);
    }
    // std::cout << "Key " << key << " inserted at idx " << idx << std::endl;
    N++;
    // std::cout << get_size() << std::endl;
    // std::cout << "Printing array... during insertion\n";
    
    // for (int i = 0; i < N; i++) {
    //     std::cout << array[i] << " ";
    // }
    // std::cout << std::endl;
}
int Heap::parent(int idx) {
    // If a node has idx i, left child has 2i + 1, right child has 2i+2
    // If N is even(that is, odd number of items in heap) then N+1 is odd, therefore parent is (N/2) - 1
    // If N is odd, parent is (N-1)/2
    if (idx == 0) return 0;
    if (idx%2 == 0) return (idx/2) - 1;
    else return (idx-1)/2;
}
void Heap::heapify(int key, int * a) {
    int left_child = 2*key + 1;
    int right_child = 2*key + 2;
    if (key >= N) return;
    // std::cout << "Within bounds" << std::endl;
    int lc = INT32_MIN;
    int rc = INT32_MIN;
    if (left_child >= N && right_child >= N) return;
    if (left_child < N) {
        lc = a[left_child];
    }
    if (right_child < N) {
        rc = a[right_child];
    }
    int max_child = (lc > rc) ? left_child : right_child;
    if (array[max_child] <= array[key]) return;
    Heap::my_swap(array[key], array[max_child]);
    heapify(max_child, &array[0]);
}

int Heap::delete_max() {
    // std::cout << "Previously max element " << array[0] << " deleted" << std::endl;
    Heap::my_swap(array[0], array[N-1]);
    N--;
    // std::cout << "Swapped" << std::endl;
    Heap::heapify(0, array);
   
    // std::cout << "Printing array... after deletion\n";
    
    // for (int i = 0; i < N; i++) {
    //     std::cout << array[i] << " ";
    // }
    // std::cout << std::endl;
   
    return array[N];
}

void Heap::build_heap(int * a, int size) {
    for (int i = size - 1; i >= 0; i--) {
        // std::cout << "array["<<i<<"] = " << a[i] << std::endl;
        Heap::insert(a[i]);
        Heap::heapify(i, array);
    }
}

void Heap::my_swap(int& a, int & b) {
    
    int c = a;
    int d = b;
    a = d;
    b = c;
}