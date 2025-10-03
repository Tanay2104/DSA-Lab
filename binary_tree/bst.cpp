#include "bst.h"
template <typename T, typename K>
T* BST<T, K>::minimum(TreeNode<T, K> * node = root) {
    while (node != nullptr && node->left != nullptr) {
        node = node -> left;
    }
    return (node -> left) -> data;
}

template <typename T, typename K>
T* BST<T, K>::maximum(TreeNode<T, K> * node = root) {
    while (node != nullptr && node->right != nullptr) {
        node = node -> right;
    }
    return (node -> right) -> data;
}

template <typename T, typename K>
TreeNode<T, K>*BST<T, K>::search(K* key) {
    TreeNode<T, K> * n = root;
    while (n != nullptr) {
        if (n->key == key) break
        if (n->key > key) n = n->left;
        else (n->key ) n = n->right;
    }
    return n;
}

template <typename T, typename K>
TreeNode<T, K>* BST<T, K>::successor(TreeNode<T, K>* n = root) {
    if (n->right != nullptr) return BST<T, K>::minimum(n->right);
    while (n->parent != nullptr && 
        (n->parent)->right == n) {
            n = n->parent;
        }
    return n->parent;
}


template <typename T, typename K>
TreeNode<T, K>* BST<T, K>::predecessor(TreeNode<T, K>* n = root) {
    if (n->left != nullptr) return BST<T, K>::maximum(n->right);
    while (n->parent != nullptr && 
        (n->parent)->left == n) {
            n = n->parent;
        }
    return n->parent;
}

template <typename T, typename K>
void BST<T, K>::insert(K * key, T * data) {
    TreeNode<T, K> * node = new TreeNode<T, K>; // Making a new node from (key, data)
    node -> key = key
    node -> data = data
    BST<T, K>::insert(node);
}

template <typename T, typename K>
void BST<T, K>::insert(TreeNode<T, K>* node) {
    TreeNode<T, K> * x = root;
    TreeNode<T, K> * y;
    while (x != nullptr) {
        y = x;
        if ((x->key) > (node->key))
            x = x -> left;
        else 
            x = x -> right;
    }
    if (y == nullptr)
        root = node;
    if ((y->key) > (node->key)) 
        y->left = node;
    else 
        y->right = node;

    node->parent = y;
}

template <typename T, typename K>
void BST<T, K>::delete_node(TreeNode<T, K>* node) {
    TreeNode<T, K>* y;
    y = ((node->left==nullptr) || (node->right==nullptr)) ? node : BST<T, K>::successor(node);

    if (y != node) {
        node->key = y->key;
        node->data = y->data;
    }
    TreeNode<T, K>* x = (y->left == nullptr) ? y->right : y->left;

    if (x != nullptr) 
        x->parent = y->parent;
    
    if (y->parent == nullptr)
        root = x
    else {
        if ((y->parent)->left == y)
            (y->parent)->left = x;
        else 
            (y->parent)->right = x;
    }
}

template <typename T, typename K>
void BST<T, K>::delete_key(K*key) {
    TreeNode<T, K> node =  BST<T, K>::search(key);
    delete_node(node);
}

template <typename T, typename K>
std::vector<std::vector<T>> BST<T, K>::print(TreeNode<T, K>* node = root) {
    unsigned long long height =  BST<T, K>::get_height(root);
    unsigned long long m = height + 1;
    unsigned long long n = pow(2, height + 1) - 1;
    std::vector<std::vector<T>> tree (m, std::vector<int>(n, 0));
    fill(node, 0, n/2, m - 2, tree);
    return tree;
}

template <typename T, typename K>
void fill(TreeNode<T, K>* node,int lvl, int m ,int n, std::vector<std::vector<T>> & tree)
    {
        if(!node) return;
        tree[lvl][m]=to_string(a->val);
        if(node->left) fill(node->left,lvl+1, m - (1<<n),n-1,v);
        if(node->right) fill(node->right,lvl+1, m + (1<<n),n-1,v);
    }

template <typename T, typename K>
unsigned long long BST<T, K>::get_height(TreeNode<T, K>* node = root) {
    if (!node) return 0;
    else if (!node->left && !node->right) return 0;
    else return max(BST<T, K>::get_height(node->left), BST<T, K>::get_height(node->right)) + 1;
}