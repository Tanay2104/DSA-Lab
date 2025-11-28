template<typename T> 
struct Node {
    T data;
    Node * parent;
    unsigned size; 
};
template<typename T> 
struct Pair {
    Node<T> t1;
    Node<T> t2;
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