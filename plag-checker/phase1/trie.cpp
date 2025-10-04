#include "trie.h"
#include <iostream>

SuffixTrie::SuffixTrie() {
    root = new TrieNode(0);
    root_suffix = new TrieNode(-1);
    // root->suffix_link = root;
}

SuffixTrie::~SuffixTrie() {
    delete_helper(root);
}
void SuffixTrie::delete_helper(TrieNode* node) {
    for (TrieNode* child : node->children) 
        delete_helper(child);
    delete node;
}

void SuffixTrie::insert(std::vector<int> data) {
    std::vector<int> going_num;
    int match_count = 0;
    TrieNode* found_node = search_word(root, data, going_num, match_count, false);
    if (found_node && going_num == data) return;  // Already there;
    else {
        int diff = data.size() - going_num.size();
        for (int i = 0; i < diff; i++) {
            TrieNode* new_node = new TrieNode(data[going_num.size() + i]);
            std::cout << "New node with data: " << new_node->data << std::endl;
            // new_node->suffix_link = found_node->suffix_link->children[0];
            found_node->children.push_back(new_node);
            found_node = new_node;
        }
    }
}
bool SuffixTrie::find(std::vector<int> data, int& m) {
    std::vector<int> going_num;
   // int match_count = 0;
    TrieNode* found_node = search_word(root, data, going_num, m, true); 
    if (found_node && going_num == data) {
        // std::cout << "DEBUG: find match count=" << m << std::endl;
        return true;
    }
    return false;
}

TrieNode* SuffixTrie::search_word(TrieNode* node, std::vector<int> num, std::vector<int>& going_num, int& match_count, bool match) {
    std::sort(node->children.begin(), node->children.end(), [](TrieNode* a, TrieNode* b) {
                                        return (a->data < b->data);
                                        });
    TrieNode* found_node = binary_search(node->children, num[0]);
    if (found_node == nullptr) return node;
    going_num.push_back(found_node->data);
    if (!(found_node->seen) && match==true) {
        // std::cout << "DEBUG: Match count = " << match_count << " for node " << found_node->data << std::endl;
        found_node->seen = true;
        found_node->suffix_link->seen = true;
        match_count++;
       
    }
    // match_count++;
   
    if (num.size() == 1) {
        
        return found_node;
    }

    else {
        std::vector<int> new_num;
        for (int i=1; i < num.size(); i++) new_num.push_back(num[i]);
        return search_word(found_node, new_num, going_num, match_count, match);
    }
}

TrieNode* SuffixTrie::binary_search(std::vector<TrieNode*> nodes, int data) {
    if (nodes.size() == 0) return nullptr;
    int middle_element = nodes[nodes.size()/2]->data;
    if (nodes.size() == 1 && nodes[0]->data != data) return nullptr;
    if (middle_element == data) return  nodes[nodes.size()/2];
    else if (middle_element > data) {
        std::vector<TrieNode*> new_vector;
        for (int i=0; i < nodes.size()/2; i++) {
            new_vector.push_back(nodes[i]);
        }
        return binary_search(new_vector, data);
    }
    else {
        std::vector<TrieNode*> new_vector;
        for (int i=nodes.size()/2 + 1; i < nodes.size(); i++) {
            new_vector.push_back(nodes[i]);
        }
        return binary_search(new_vector, data);
    }
}

bool SuffixTrie::isLast(TrieNode* node, int data) {
    for (TrieNode* child: node->children) {
        if (child != nullptr && child->data == data) return false;
    }
    return true;
}

void SuffixTrie::makeTrie(std::vector<int> text) {
    for (int i=0; i < text.size(); i++) {
        std::vector<int> suffix(text.begin()+i, text.end());
        insert(suffix);
    }
}

void SuffixTrie::addSuffixLinks() {
    std::queue<TrieNode*> queue;
    queue.push(root);
    root->suffix_link = root_suffix;
    while (!queue.empty()) {
        TrieNode* current_node = queue.front();
        queue.pop();
        for (TrieNode* child: current_node->children) {
            TrieNode* found_suffix_link =  binary_search(current_node->suffix_link->children, child->data);
            child->suffix_link = found_suffix_link != nullptr ? found_suffix_link : nullptr;
            queue.push(child);
        }
    }
}