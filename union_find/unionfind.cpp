#include "unionfind.h"

template <typename T>
Node<T>* UnionFind<T>::FindSet(Node<T> * x) {
    if (x->parent != x) x->parent = FindSet(x->parent);
    return x->parent;
}

template <typename T>
Node<T>* UnionFind<T>::MakeSet(T x) {
    Node* new_node = new Node;
    new_node->data = x;
    new_node->parent = new_node;
    new_node.size = 1;
    return new_node;
}

template <typename T>
void UnionFind<T>::Union(Node<T>* x, Node<T>* y) {
    x = FindSet(x);
    y = FindSet(y);
    if (x->size < y->size) std::swap(x, y);
    y->parent = x;
    x->size = x->size + y->size;
}