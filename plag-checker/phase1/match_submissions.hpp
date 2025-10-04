#include <array>
#include <iostream>
#include <span>
#include <vector>
#include <cmath>
#include "trie.h"
// -----------------------------------------------------------------------------

// You are free to add any STL includes above this comment, below the --line--.
// DO NOT add "using namespace std;" or include any other files/libraries.
// Also DO NOT add the include "bits/stdc++.h"

// OPTIONAL: Add your helper functions and data structures here

std::array<int, 5> match_submissions(std::vector<int> &submission1, 
                                    std::vector<int> &submission2) {
    // TODO: Write your code here
    std::array<int, 5> result = {0, 0, 0, 0, 0};
    SuffixTrie trie;
    trie.makeTrie(submission2);
    trie.addSuffixLinks();
    std::cout << "Successfuly made trie" << std::endl;

    for (int i=0; i < submission1.size() - 10; i++) {
        for (int j=10; j <= 20; j++) {
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
            trie.find(substr, m);
            result[1] += m;
        }
    }
    return result; // dummy return
    // End TODO
}
