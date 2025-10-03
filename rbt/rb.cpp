#include "rb.h"
using ptr = RedBlackTree::ptr;

RedBlackTree::RedBlackTree() : n_rotations(0){}

const ptr RedBlackTree::getRoot() const
{ 
	return root; 
}

ptr RedBlackTree::insert(int data)
{
	node * newnode = new node(data);
	if (!root) {
		root = newnode;
		root->color = 0;
	}
	else {
		insert(root, newnode);
	}
	return newnode;
}

// auxiliary function to perform RBT insertion of a node
// you may assume start is not nullptr
void RedBlackTree::insert(ptr start, ptr newnodePtr)
{
	 if (!start || !newnodePtr) return;
	 if (newnodePtr->data < start->data) {
		if (start->left) insert(start->left, newnodePtr);
		else {
			start->left = newnodePtr;
			newnodePtr->parent = start;
		}
	 }
	 else {
		if (start->right) insert(start->right, newnodePtr);
		else {
			start->right = newnodePtr;
			newnodePtr->parent = start;
		}
	 }
}

// Credits to Adrian Schneider
void RedBlackTree::printRBT(ptr start, const std::string& prefix, bool isLeftChild) const
{
	if (!start) return;

	std::cout << prefix;
	std::cout << (isLeftChild ? "|--" : "|__" );
	// print the value of the node
	std::cout << start->data << "(" << start->color << ")" << std::endl;
	// enter the next tree level - left and right branch
	printRBT(start->left, prefix + (isLeftChild ? "│   " : "    "), true);
	printRBT(start->right, prefix + (isLeftChild ? "│   " : "    "), false);
}

// Function performing right rotation
// of the passed node
void RedBlackTree::rightrotate(ptr loc)
{
	n_rotations +=1;
	// right rotate means anti clockwise rotation and child is the right child of parent
	bool grandparent_exists = (loc->parent->parent != nullptr);
	ptr child = loc;
	ptr parent = loc->parent;
	ptr child_left = child->left;

	parent->right = child_left;
	if (child_left != nullptr) child_left->parent = parent;
	child->left = parent;
	if (grandparent_exists) {
		bool is_parent_right_child = (parent->parent->right == parent);
		if (is_parent_right_child) {
			parent->parent->right = child;
		}
		else {
			parent->parent->left = child;
		}
		child->parent = parent->parent;
	}
	parent->parent = child;

}

// Function performing left rotation
// of the passed node
void RedBlackTree::leftrotate(ptr loc)
{
	n_rotations +=1;
	bool grandparent_exists = (loc->parent->parent != nullptr);
	ptr child = loc;
	ptr parent = loc->parent;
	ptr child_right = child->right;

	parent->left = child_right;
	child_right->parent = parent;
	child->right = parent;
	if (grandparent_exists) {
		bool is_parent_left_child = (parent->parent->left == parent);
		if (is_parent_left_child) {
			parent->parent->left = child;
		}
		else {
			parent->parent->right = child;
		}
		child->parent = parent->parent;
	}
	parent->parent = child;
}

// This function fixes violations
// caused by RBT insertion
void RedBlackTree::fixup(ptr loc)
{	
	// If parent doesn't exist, loc is root, do nothing
	if (!loc->parent) {
	loc->color = 0;
	return;
	}
	// If grandparent doesn't exist, color parent(root) black
	bool grandparent_exists = (loc->parent->parent != nullptr);
	if (!grandparent_exists) {
		loc->parent->color = 0;
		return;
	}
	// Now grandparent should exist
	ptr grandparent = loc->parent->parent;
	bool is_parent_right_child = false;
	if ((grandparent->right!=nullptr) && ((grandparent->right)==(loc->parent))) is_parent_right_child = true;
	if (is_parent_right_child) {
		bool uncle_exists = (grandparent->left != nullptr);
		if (uncle_exists && (grandparent->left->color == 1)) {
			grandparent->left->color = 0;
			loc->parent->color = 0;
			if (grandparent != root){
				grandparent->color = 1;
				if (grandparent->parent->color == 0) return;
				else if (grandparent->parent->color == 1) fixup(grandparent);
			}
			return;
		}
		else {
			bool is_path_straight = (grandparent->right->right != nullptr ? 
										(grandparent->right->right == loc)
										: false
									);
			if (is_path_straight) {
				rightrotate(loc->parent);
				loc->parent->color = 0;
				grandparent->color = 1;
				if (grandparent == root) {
					root = loc->parent;
					root->parent = nullptr;
				}
				return;
			}
			else {
				leftrotate(loc);
				rightrotate(loc);
				loc->color = 0;
				grandparent->color = 1;
				if (grandparent == root) {
					root = loc;
					root->parent = nullptr;
				}
			}
		}
	}
	else {
		bool uncle_exists = (grandparent->right != nullptr);
		if (uncle_exists && (grandparent->right->color == 1)) {
			grandparent->right->color = 0;
			loc->parent->color = 0;
			if (grandparent != root){
				grandparent->color = 1;
				if (grandparent->parent->color == 0) return;
				else if (grandparent->parent->color == 1) fixup(grandparent);
			}
			return;
		}
		else {
			bool is_path_straight = (grandparent->left->left != nullptr ?
									grandparent->left->left == loc
									: false);
			if (is_path_straight) {
				leftrotate(loc->parent);
				loc->parent->color = 0;
				grandparent->color = 1;
				if (grandparent == root) {
					root = loc->parent;
					root->parent = nullptr;
				}
				return;
			}
			else {
				rightrotate(loc);
				leftrotate(loc);
				loc->color = 0;
				grandparent->color = 1;
				if (grandparent == root) {
					root = loc;
					root->parent = nullptr;
				}
			}
		}
	}

}
// Function to print inorder traversal
// of the fixated tree
void RedBlackTree::inorder(ptr start) const
{
	if (!start)
		return;
	
	inorder(start->left);
	std::cout << start->data << " ";
	inorder(start->right);
}