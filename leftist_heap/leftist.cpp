#include "leftist.h"

// Initialize an instance of LeftistNode
LeftistNode::LeftistNode(int key, LeftistNode *lt, LeftistNode *rt, int np)
{
    // Write your code below this line ----------------------------------------------------------------
    this->key = key;
    this->left = lt;
    this->right = rt;
    this->npl = np;
}

// Implement a default constructor for a empty LeftistHeap
LeftistHeap::LeftistHeap()
{
    // Write your code below this line ----------------------------------------------------------------

}

// Implement a destructor for LeftistHeap
// All nodes should be properly deleted to avoid memory leaks
LeftistHeap::~LeftistHeap()
{
    // Write your code below this line ----------------------------------------------------------------
    makeEmpty();
    return;
}

void LeftistHeap::merge(LeftistHeap &rhs)
{
    if (this == &rhs)
        return;
    root = merge(root, rhs.root);
    rhs.root = nullptr;
}

// Implement the merge function that takes roots of two LeftistHeaps and merges them into one returns the root of merged heap
LeftistNode *LeftistHeap::merge(LeftistNode *h1, LeftistNode *h2)
{
    // Write your code below this line ----------------------------------------------------------------
    if(!h1) return h2;
    if(!h2) return h1;

    if(h1->key > h2->key) {
        std::swap(h1, h2);
    }
    h1->right = merge(h1->right, h2);
    LeftistNode* l = h1->left;
    LeftistNode* r = h1->right;
    h1->npl = std::min((l?l->npl:-1), (r?r->npl:-1)) + 1;
    if (!l || l->npl < r->npl)
    {
        swapChildren(h1);
    }
    return h1;
}

// Implement a function to swap the children of a node (Exchange the left and right children of the provided node)
// Ensure the left child becomes the right child and vice versa.
void LeftistHeap::swapChildren(LeftistNode *t)
{
    // Write your code below this line ----------------------------------------------------------------
    LeftistNode* temp = t->left;
    t->left = t->right;
    t->right = temp;
}

// Implement a insertion function to insert a new key into the heap.
void LeftistHeap::insert(int &x)
{
    // Write your code below this line ----------------------------------------------------------------
    LeftistNode* newNode = new LeftistNode(x);
    root = merge(root, newNode);
}

// Implement this function to retrieve the smallest key in the heap.
int LeftistHeap::findMin() const
{
    // Write your code below this line ----------------------------------------------------------------
    return root->key;
}

// Delete minimum function: Remove and return the smallest key from the heap.
void LeftistHeap::deleteMin(int &minItem)
{
    // Write your code below this line ----------------------------------------------------------------
    LeftistNode* todel = root;
    minItem = root->key;
    root = merge(root->left, root->right);
    delete todel;
}

// Check if the heap is empty
bool LeftistHeap::isEmpty() const
{
    // Write your code below this line ----------------------------------------------------------------
    return root==nullptr;
}

void LeftistHeap::makeEmpty()
{ // no need to change here
    makeEmpty(root);
}

// Implement a helper function for makeEmpty that delete all nodes starting from the given node.
void LeftistHeap::makeEmpty(LeftistNode *t)
{
    // Write your code below this line ----------------------------------------------------------------
    if(!t) return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
}
