#include "trie.h"
#include <iostream>
int main(){
    // std::vector<int> text = {12, 34, 12, 245, 12, 323, 4345, 22, 1, 22, 12, 22, 12};
    // std::vector<int> text = {12, 34, 12, 245, 12, 323, 4345, 12};
    std::vector<int> submission1 = {12, 34, 31, 53, 23, 45, 56, 23, 12, 45, 23};
    std::vector<int> submission2 = {53, 332, 31, 53, 23, 45, 56, 23, 12, 45, 19};

    SuffixTrie trie;
    trie.makeTrie(submission2);
    trie.addSuffixLinks();
    // for (int i=0; i < text.size(); i++) {
    //     std::cout << "Testing suffix: ";
    //     std::vector<int> suffix(text.begin() + i, text.end());
    //     for (int j=0; j < suffix.size(); j++) std::cout << suffix[j] << " ";
    //     std::cout << std::endl;
    //     int m = 0;
    //     if (trie.find(suffix, m)) {
    //         std::cout << "Suffix found ";
            
    //         //std::vector<int> going_num;
    //         // TrieNode* n = trie.search_word(trie.root, suffix, going_num, m);
    //         std::cout << "Match count = " << m << std::endl;
    //     }
    //     else std::cout << "Suffix not found" << std::endl;
    // }
    int total_count = 0;

    for (int i=0; i < submission1.size() - 3; i++) {
        for (int j=3; j <= 7; j++) {
            std::vector<int> substr;
            if (j >= submission1.size() - i) {
                substr = std::vector<int>(submission1.begin() + i, submission1.end());
            }
            else {
                substr = std::vector<int>(submission1.begin() + i, submission1.begin() + i + j);
            }
            // for (int k: substr) 
            //     std::cout << k << ' ';
            //  std::cout << std::endl;
            int m = 0;
            if (trie.find(substr, m)) {
                std::cout << "Substring found ";
                std::cout << "Match count = " << m << std::endl;
                std::cout << "Matching substring: ";
                for (int i: substr) 
                    std::cout << i << ' ';
                total_count+=m;
                std::cout << std::endl;
            }
            else std::cout << "Substring not found" << std::endl;
                
        }
    }
    std::cout << "Total Matching count: " << total_count << std::endl;
}