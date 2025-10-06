#include "unionfind.h"

template <typename T>
Node<T>* UnionFind<T>::FindSet(Node<T> * x) {
    if (x->parent != x) x->parent = FindSet(x->parent);
    return x->parent;
}

template <typename T>
Node<T>* UnionFind<T>::MakeSet(T x) {
    x->parent = x;
    x.size = 1;
}

template <typename T>
void UnionFind<T>::Union(Node<T>* x, Node<T>* y) {
    x = FindSet(x);
    y = FindSet(y);
    if (x->size < y->size) std::swap(x, y);
    y->parent = x;
    x->size = x->size + y->size;
}