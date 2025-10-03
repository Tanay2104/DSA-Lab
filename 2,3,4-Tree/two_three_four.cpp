#include "two_three_four.h"
// Fill in the missing functions

// -----------------------------
// BigNode constructor
// -----------------------------
BigNode::BigNode()
{
    A = -1;
    B = -1;
    C = -1;
    L = M1 = M2 = R = nullptr;
}
RedBlackTree::RedBlackTree()
{
    root = nullptr;
}

struct node *RedBlackTree::getRoot()
{
    return root;
};

void RedBlackTree::setRoot(node *newroot)
{
    root = newroot;
}

// function to perform RBT insertion of a node
node *RedBlackTree::insert(node *start,
                           node *newnodePtr)
{
    // If the tree is empty,
    // return a new node

    // Otherwise recur down the tree
	if(start->d > newnodePtr->d) {
		if(!start->l) {
			start->l = newnodePtr;
			newnodePtr->p = start;
		}
		else {
			insert(start->l, newnodePtr);
		}
	}
	else{
		if(!start->r) {
			start->r = newnodePtr;
			newnodePtr->p = start;
		}
		else {
			insert(start->r, newnodePtr);
		}
	}
    // Return the (unchanged) node pointer
    return newnodePtr;
}

// Helper for pretty printing (internal; not in header)
// Credits to Adrian Schneider
static void printRBTHelper(node *n, const std::string &prefix, bool isLeft)
{
    if (!n)
        return;
    std::cout << prefix;
    std::cout << (isLeft ? "|--" : "|__");
    std::cout << n->d << "(" << (n->c == 0 ? "B" : "R") << ")" << std::endl;
    printRBTHelper(n->l, prefix + (isLeft ? "│   " : "    "), true);
    printRBTHelper(n->r, prefix + (isLeft ? "│   " : "    "), false);
}

void RedBlackTree::printRBT(const std::string &prefix, bool isLeft)
{
    // public wrapper prints from root; ignore args and use root for consistency
    (void)prefix;
    (void)isLeft;
    printRBTHelper(root, "", true);
}

void RedBlackTree::rightrotate(node *temp)
{
	/*
	takes 	temp				c
			/		--->	 \
		   c				 temp
		   */
	node *parent = temp->p;
	node *c = temp->l;

	temp->l = c->r;
	if(temp->l){
		temp->l->p = temp;
	}
	temp->p = c;
	c->p = parent;
	c->r = temp;

	int temp_clr = temp->c;
	temp->c = c->c;
	c->c = temp_clr;
	
	if(temp == root) {
		root = c;
		c->c = 0;
	}
	if(parent) {
		if(parent->l == temp) {
			parent->l = c;
		}
		else {
			parent->r = c;
		}
	}
}

void RedBlackTree::leftrotate(node *temp)
{
	/*
	takes 	temp				 c
			  \	   --->	 	/
			   c		  temp
	*/
	node *parent = temp->p;
	node *c = temp->r;
	temp->r = c->l;
	if(temp->r){
		temp->r->p = temp;
	}
	temp->p = c;
	c->p = parent;
	c->l = temp;

	int temp_clr = temp->c;
	temp->c = c->c;
	c->c = temp_clr;

	if(temp == root) {
		root = c;
		c->c = 0;
	}
	if(parent) {
		if(parent->l == temp) {
			parent->l = c;
		}
		else {
			parent->r = c;
		}
	}
}

void RedBlackTree::fixup(node *pt)
{
	// black node
	if(!pt->c) {
		return;
	}
	// red root case
	if(pt == getRoot()) {
		pt->c = 0;
		return;
	}

	node* parent = pt->p;
	// black parent
	if(!parent || !parent->c){
		return;
	}
	
	node* grp = parent->p;
	node* unc = (grp->l == parent ? grp->r : grp->l);
	// red uncle
	if(unc && unc->c) {
		unc->c = 0;
		parent->c = 0;
		grp->c = 1;
		fixup(grp);
		return;
	}

	if(grp->l == parent) {
		/*
				grp					grp
				/					/
			parent      or 		parent
			  /						\
			node					node
		*/
		if(parent->l != pt) {
			leftrotate(parent);
		}
		rightrotate(grp);
	}
	else {
		if(parent->r != pt) {
			rightrotate(parent);
		}
		leftrotate(grp);
	}
}

void RedBlackTree::inorder(node *trav)
{ // Function to print inorder traversal of the fixated tree, no changes needed here keep it as it is
    if (!trav)
        return;
    inorder(trav->l);
    std::cout << trav->d << " ";
    inorder(trav->r);
}

TwoThreeFourTree::TwoThreeFourTree()
{ // no change needed here
    tree = new RedBlackTree();
}

void TwoThreeFourTree::insert(int key)
{
    // create new node here then insert and then fix
    node *newnodePtr = new node;
    newnodePtr->d = key;
	newnodePtr->l = nullptr;
	newnodePtr->r = nullptr;
	if (!tree->getRoot()) {
		newnodePtr->c = 0; // set root color as black
		tree->setRoot(newnodePtr);
		return;
	}
	tree->insert(tree->getRoot(), newnodePtr);
    tree->fixup(newnodePtr);
}

// just a forward declaration
static BigNode *Convert(node *root);

BigNode *TwoThreeFourTree::convert()
{
    return Convert(tree->getRoot());
}

static BigNode *Convert(node *root)
{ // Convert RB to 2-3-4 BigNode structure
    if(!root) {
        return nullptr;
    }
    BigNode *newNode = new BigNode;
    newNode->B = root->d;
    if(root->l && root->l->c) {
        newNode->A = root->l->d;
        newNode->L = Convert(root->l->l);
        newNode->M1 = Convert(root->l->r);
    }
    else {
        newNode->M1 = Convert(root->l);
    }

    if(root->r && root->r->c) {
        newNode->C = root->r->d;
        newNode->R = Convert(root->r->r);
        newNode->M2 = Convert(root->r->l);
    }
    else {
        newNode->M2 = Convert(root->r);
    }

	return newNode;
}

void TTF(BigNode *root)
{
    if (!root)
        return;
    if (root->L)
        TTF(root->L);
    if (root->A != -1)
        std::cout << root->A << " ";
    if (root->M1)
        TTF(root->M1);
    if (root->B != -1)
        std::cout << root->B << " ";
    if (root->M2)
        TTF(root->M2);
    if (root->C != -1)
        std::cout << root->C << " ";
    if (root->R)
        TTF(root->R);

}
