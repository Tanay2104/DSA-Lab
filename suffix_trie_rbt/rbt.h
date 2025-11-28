#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <cassert>

// #define CHAR_TO_INT(c) (int(c) - int('0'));
// #define INT_TO_CHAR(i) (char(i + '0'))
// Structure to represent each
// RbtNode in a red-black tree
struct TrieNode {
    RedBlackTree * children;
    int data;
    TrieNode(int data) : data(data) {}
    TrieNode() : data(0) {}
};
struct RbtNode {
    TrieNode* trie_node;
	unsigned short color; // 1-red, 0-black
    // RbtNode* suffix_link;
	RbtNode* parent; // parent
	RbtNode* right; // right-child
	RbtNode* left; // left child
    RbtNode(int data): color(1), parent(nullptr), right(nullptr), left(nullptr) {
        trie_node = new TrieNode(data);
    }
};

class RedBlackTree
{
    // global root for the entire tree
    RbtNode* root = nullptr;
   
   

public:
    int size;
    // unsigned long long n_rotations;
    typedef RbtNode* ptr;
    void destroyTree(ptr RbtNode);

    // Constructor and destructors
    RedBlackTree();
    ~RedBlackTree();
    const int getSize(ptr RbtNode) const;

    // Helper Update Functions
    const ptr getRoot() const;


    // function to perform BST insertion of a RbtNode.
    // returns a pointer to the newly inserted RbtNode
    ptr insert(int data);

    // auxiliary function to insert a RbtNode
    // start is the root of the tree/subtree in which
    // the RbtNode (pointed to my newnodePtr) is to be inserted
    void insert(ptr start, ptr newnodePtr);

    // Credits to Adrian Schneider
    // Function to pretty print the tree
    void printRBT(ptr start, const std::string& prefix="", bool isLeftChild=false) const;

    // Function performing right rotation
    // of the passed RbtNode
    void rightrotate(ptr loc);

    // Function performing left rotation
    // of the passed RbtNode
    void leftrotate(ptr loc);

    // This function fixes violations
    // caused by BST insertion
    void fixup(ptr loc);

    // Function to print inorder traversal
    // of the fixated tree
   //  void print_inorder(ptr start) const;
    // TrieNode** inorder_array() const;
    // void inorder_fill(ptr start, TrieNode* & current_pos) const;
    RbtNode* operator[] (int idx);
    RbtNode* kth_min(RbtNode* RbtNode, int idx);
};