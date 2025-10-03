#include "trie.h"
#include <iostream>
#include <fstream>
#include <stack>

Trie::Trie()
{
	root = NULL;
}
TrieNode* my_search(struct TrieNode *root, std::string key);
// Returns new trie node (initialized to NULLs)
struct TrieNode* Trie::getNode(void)
{
	TrieNode* new_node = new TrieNode;
	new_node->isWordEnd = false;
	return new_node;
}

// If not present, inserts key into trie. If the
// key is prefix of trie node, just marks leaf node
void Trie::insert(struct TrieNode* root, const std::string key)
{

	
}

bool Trie::search(struct TrieNode *root, std::string key)
{
	if (key.empty()) return true;
	int idx = CHAR_TO_INDEX(key[0]);
	TrieNode* word_node = root->children[idx];
	if (word_node == nullptr) 
		return false;
	if (key.substr(1).empty()) {
		if (word_node->isWordEnd == true)
			return true;
		else
			return false;
	}
	return search(word_node, key.substr(1));
}

// Returns 0 if current node has a child
// If all children are NULL, return 1.
bool Trie::isLastNode(struct TrieNode* root)
{
	for (int i=0; i < ALPHABET_SIZE; i++) {
		if (root->children[i] != nullptr) return 0;
	}
	return 1;
}

// Recursive function to print auto-suggestions for given
// node.
void Trie::suggestionsRec(struct TrieNode* root,
					std::string currPrefix)
{
	// found a std::string in Trie with the given prefix
	for (int i=0; i < ALPHABET_SIZE; i++) {
		if (root->children[i] != nullptr) {
			if (root->children[i]->isWordEnd)
				std::cout << currPrefix + char(int('a') + i) << std::endl;
			suggestionsRec(root->children[i], currPrefix + char(int('a') + i));
		}
	}
}

// print suggestions for given query prefix.
int Trie::printAutoSuggestions(TrieNode* root, const std::string query)
{
	std::stack<std::string> all_words;
	int i=0;
	std::cout << "Old query: " << query << std::endl;
	for (int j=0; j < query.length(); j++) {
		if (query[j] == ' '){
			std::cout << "Substr: " << query.substr(i, j-i) << " at j=" << j << std::endl;
			all_words.push(query.substr(i, j-i));
			i = j+1;
		}
	}  
	std::string word_1word_2;
	word_1word_2 = all_words.top();
	all_words.pop();
	word_1word_2 += all_words.top();
	all_words.pop();
	std::cout << "New query: " << word_1word_2 << std::endl;


	if (!search(root, word_1word_2)) return 0;
	TrieNode* found_node = my_search(root, word_1word_2);
	if (isLastNode(found_node) && found_node->isWordEnd == true) return -1;
	// std::cout << query << std::endl;
	suggestionsRec(found_node, word_1word_2);
	return 1;
}

// Process the file "lorem.txt" to insert the words in lorem.txt and store the relevant context as needed.
void Trie::processContext()
{
	std::ifstream lorem;
	lorem.open("lorem.txt");
	std::string word_1;
	std::string word_2;
	if (lorem >> word_1) {
		while (lorem >> word_2) {
			//std::cout << word_1+word_2 << std::endl;
			insert(root, word_1+word_2);
			word_1 = word_2;
		}
	}
}

TrieNode* my_search(struct TrieNode *root, std::string key)
{
	// std::cout << "Checking is last node: " << isLastNode(root) << std::endl;
	// std::cout << "Searching key " << key << std::endl;

	// key is empty;
	if (key.empty()) {
		// std::cout << "Key is empty" << std::endl;
		return nullptr;
	}

	int idx = CHAR_TO_INDEX(key[0]);
	// key = key.substr(1);
	TrieNode* word_node = root->children[idx];
	if (word_node == nullptr) 
		return nullptr;
	if (key.substr(1).empty()) {
		return word_node;
	}
	return my_search(word_node, key.substr(1));
}