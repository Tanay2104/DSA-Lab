#ifndef TWO_THREE_FOUR_H
#define TWO_THREE_FOUR_H

#include <string>
#include <iostream>

// =============================
// Red-Black Tree node
// =============================
struct node
{
    int d;          // data
    int c;          // 1 = red, 0 = black
    struct node *p; // parent
    struct node *r; // right child
    struct node *l; // left child
};

// =============================
// Red-Black Tree wrapper
// =============================
class RedBlackTree
{
    node *root; // root of the RB tree

public:
    RedBlackTree();

    // Accessors
    node *getRoot();
    void setRoot(node *newroot);

    // BST insert helper
    node *insert(node *trav, node *temp);

    // Pretty print
    void printRBT(const std::string &prefix, bool isLeft);

    // Rotations
    void rightrotate(node *temp);
    void leftrotate(node *temp);

    // Fix RB violations
    void fixup(node *pt);

    // Inorder traversal
    void inorder(node *trav);
};

// =============================
// 2-3-4 Tree node (converted from RB tree)
// =============================
struct BigNode
{
    int A, B, C;              // data keys (default -1)
    BigNode *L, *M1, *M2, *R; // children

    BigNode();
};

// =============================
// TwoThreeFourTree wrapper
// =============================
class TwoThreeFourTree
{
public:
    TwoThreeFourTree();
    void insert(int key);
    BigNode *convert();

    RedBlackTree *tree;
};

// =============================
// Utility function to print 2-3-4 tree in-order
// =============================
void TTF(BigNode *root);

#endif
