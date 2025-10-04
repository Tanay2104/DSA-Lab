#include <vector>
#include <algorithm>
#include <queue>

struct TrieNode {
    std::vector<TrieNode*> children;
    int data;
    bool seen;
    TrieNode* suffix_link;
    TrieNode(int d) : data(d) {}
};

class SuffixTrie {
    public:
        TrieNode* root;
        TrieNode* root_suffix;

        SuffixTrie();
        ~SuffixTrie();
        void insert(std::vector<int> data);
        // void insert_helper(TrieNode* node, std::vector<int> data);
        // TrieNode* search_word(std::vector<int> num,  std::vector<int>& going_num);
        bool find(std::vector<int> num, int& m);
        TrieNode* search_word(TrieNode* node, std::vector<int> num,  std::vector<int>& going_num, int& match_count, bool match);
        TrieNode* binary_search(std::vector<TrieNode*> nodes, int data);
        void delete_helper(TrieNode* node);
        bool isLast(TrieNode* node, int data);
        void makeTrie(std::vector<int> text);
        void addSuffixLinks();
};