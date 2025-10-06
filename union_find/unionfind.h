/*
Equality(x, y);
DisEquality(x, y);
FindSet(x) {
if (x.parent != x x.parent = FindSet(x.parent))
return x.parent;
}
MakeSet(x) {
x.parent = x
x.size = 1
}

Union(x, y) {
x = FindSet(x);
y = FindSet(y);
if (x.size < y.size) SWAP(x, y);
y.parent = x;
x.size = x.size + y.size
}

vector<Equality> E;
vector<DisEquality> D;
for x in E U D makeSet(x);
for x, y in E union(x, y);
for x, y in D if findSet(x) = findSet(y) return UNSAT
return SAT
*/
template<typename T> 
struct Node {
    T data;
    Node * parent;
    unsigned size; 
};
template<typename T> 
struct Pair {
    T t1;
    T t2;
};
template<typename T> 
using Equality  = Pair<T>;
template<typename T> 
using DiEquality  = Pair<T>;
template<typename T> 
class UnionFind {
    public:
        Node<T>* FindSet(Node<T>* x);
        Node<T>* MakeSet(T t);
        void Union(Node<T>* x, Node<T>* y);
};