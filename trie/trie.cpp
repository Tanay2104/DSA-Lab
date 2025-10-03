#include "trie.h"
#include <iostream>
TrieNode* my_search(struct TrieNode *root, std::string key);
Trie::Trie()
{
	root = NULL;
}

// Returns new trie node (initialized to NULLs)
struct TrieNode* Trie::getNode(void)
{
	TrieNode* new_trie_node = new TrieNode;
	new_trie_node->isWordEnd = false;
	return new_trie_node;
}

// If not present, inserts key into trie. If the
// key is prefix of trie node, just marks leaf node
void Trie::insert(struct TrieNode* root, const std::string key)
{
	// std::cout << "Current key to be inserted = " << key << std::endl;
	if (key.empty()) {
		// std::cout << "Empty string char: " << char(key[0]) << std::endl;
		return;
	}
	
	int idx = CHAR_TO_INDEX(key[0]);
	TrieNode* word_node = root->children[idx];
	if (!word_node) {
		word_node = getNode();
		root->children[idx] = word_node;
		// std::cout << "Word node pointer " << word_node << std::endl;
	}
	if (key.substr(1).empty()) {
		// std::cout << "Inserted key: " << key << std::endl;
		word_node->isWordEnd = true;
	}
	// std::cout << "Checking is last node: " << isLastNode(root) << std::endl;
	insert(word_node, key.substr(1));
}
bool Trie::search(struct TrieNode *root, std::string key)
{
	// std::cout << "Checking is last node: " << isLastNode(root) << std::endl;
	// std::cout << "Searching key " << key << std::endl;

	// key is empty;
	if (key.empty()) {
		// std::cout << "Key is empty" << std::endl;
		return true;
	}

	int idx = CHAR_TO_INDEX(key[0]);
	// key = key.substr(1);
	TrieNode* word_node = root->children[idx];
	if (word_node == nullptr) 
		return false;
	if (key.substr(1).empty()) {
		if (word_node->isWordEnd == true) {
			// std::cout << "Found key ending alphabet " << key[0];
			return true;
		}
			
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
	if (!search(root, query)) return 0;
	TrieNode* found_node = my_search(root, query);
	if (isLastNode(found_node) && found_node->isWordEnd == true) return -1;
	std::cout << query << std::endl;
	suggestionsRec(found_node, query);
	return 1;
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