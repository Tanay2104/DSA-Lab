/*
Impelement a templated Binary Search Tree with the following functions: 
mimimum, maximum, successor, predecessor, search, insert, delete, print tree
*/
#include <iostream>
#include <vector>
#define sqrt_5 2.2360679775

template <typename T, typename K>
struct  TreeNode{
    T* data;
    K* key;
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right; 
};
template<typename T, typename K> // T is for data, K is for key
class BST {
    TreeNode<T, K> * root;
    unsigned long long get_height(TreeNode<T, K>* node = root);
public:
    BST(); // Default constructor, does nothing
    BST(T * data); // Constructor which initialises the root with the given data. We prefer this method.
    BST(TreeNode<T> * node); // A secondary constructor which initialises the root directly through the given node

    T* minimum(TreeNode<T, K>* node = root); // Done
    T* maximum(TreeNode<T, K>* node = root); // Done
    TreeNode<T, K>* successor(TreeNode<T, K>* node = root); // Done
    TreeNode<T, K>* predecessor(TreeNode<T, K>* node = root); // Done
    TreeNode<T, K>* search(K * key); // Done
    void delete_node(TreeNode<T, K>* node);
    void delete_key(K* key);
    void insert(K * key, T * data); // Done for inserting a single node
    void insert(TreeNode<T, K>* node); // Done For inserting a subtree
    std::vector<std::vector<T>> print(TreeNode<T, K>* node = root); // For printing the tree in a clear visual format
};