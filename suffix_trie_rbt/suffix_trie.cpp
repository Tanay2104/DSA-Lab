#include "suffix_trie.hpp"


SuffixTrie::SuffixTrie() {
    root = new TrieNode;
}
void SuffixTrie::insert(std::vector<int> data) {
   insert_helper(root, data);
}

void SuffixTrie::insert_helper(TrieNode* root, std::vector<int> data) {
   TrieNode* found_node = search_word(data);
   if (found_node == nullptr) {
        root->children->insert(data[0]);
   }
   insert_helper(found_node, data);
}


TrieNode* SuffixTrie::search_word(std::vector<int> num) {
    return search_word_helper(root, num) ;
}

TrieNode* SuffixTrie::search_word_helper(TrieNode* node, std::vector<int> num) {
}


TrieNode* SuffixTrie::binary_search(RbtNode* rbt_node, int data) {
   int middle_data = rbt.kth_min(rbt, getSize(rbt)/2);
}
