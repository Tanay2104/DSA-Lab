#include "rbt.h"
#include <vector>

class SuffixTrie {
    public:
        SuffixTrie();
        TrieNode* root;
        void insert(std::vector<int> data);
        void insert_helper(TrieNode* node, std::vector<int> data);
        TrieNode* search_word(std::vector<int> num);
        TrieNode* search_word_helper(TrieNode* node, std::vector<int> num);
        TrieNode* binary_search(RbtNode* rbt, int data);
};