#include "trie.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
Trie::Trie()
{
	root = NULL;
}
TrieNode* my_search(struct TrieNode *root, std::string key);
// Returns new trie node (initialized to NULLs)
struct TrieNode* Trie::getNode(void)
{

	TrieNode* new_node = new TrieNode;
	if (!root) root = new_node;
	new_node->isWordEnd = false;
	return new_node;
}

// If not present, inserts key into trie. If the
// key is prefix of trie node, just marks leaf node
void Trie::insert(struct TrieNode* root, const std::string key)
{
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
std::vector<std::string> Trie::suggestionsRec(struct TrieNode* root,
					std::string currPrefix)
{
	// found a std::string in Trie with the given prefix
	std::vector<std::string> max_strings;
	for (int i=0; i < ALPHABET_SIZE; i++) {
		if (root->children[i] != nullptr) {
			if (root->children[i]->isWordEnd)
				// std::cout << currPrefix + char(int('a') + i) << std::endl;
				max_strings.push_back(currPrefix + char(int('a') + i));
				// if (count_map[s1] > count_map[s_max]) s_max = s1;
			for (auto s: suggestionsRec(root->children[i], currPrefix + char(int('a') + i))) {
				max_strings.push_back(s);
			}
			// if (count_map[s1] > count_map[s_max]) s_max = s1;
		}
	}
	// std::cout << "Chosen max count string: " << s_max << std::endl;
	return max_strings;
}

// print suggestions for given query prefix.
int Trie::printAutoSuggestions(TrieNode* root, const std::string query)
{
	std::queue<std::string> all_words;
	int i=0;
	// std::cout << "Old query: " << query << std::endl;
	for (int j=0; j < query.length(); j++) {
		// std::cout << "query[" << j << "]= " << query[j] << " ";
		if (query[j] == ' ' || query[j] == '#'){
			// std::cout << "Substr: " << query.substr(i, j-i) << " at j=" << j << std::endl;
			all_words.push(query.substr(i, j-i));
			i = j+1;
		}
	}  

	while (all_words.size() > 2) {
		all_words.pop();
	}
	std::string word_1= all_words.front();
	all_words.pop();
	std::string word_2=all_words.front();
	all_words.pop();
	
	// std::cout << "New query: " << word_1word_2 << std::endl;


	// std::cout << "lovecats present ? " << search(root,  std::string("lovecats\n")) << std::endl;
	TrieNode* found_node = my_search(root, word_1+word_2);
	if (found_node == nullptr){
		// std::cout << "Query not found!" << std::endl;
		return 0;
	}
	// std::cout << "Query found!" << std::endl;
	if (isLastNode(found_node) && found_node->isWordEnd == true) return -1;
	// std::cout << query << std::endl;
	std::vector<std::string> max_strings =  suggestionsRec(found_node, word_1+word_2);
	std::sort(max_strings.begin(), max_strings.end(), [this](std::string s1, std::string s2) {
		return this->count_map[s1] >= this->count_map[s2];
	});
	int max_occurence = count_map[max_strings[0]];
	while (count_map[max_strings.back()] < max_occurence) max_strings.pop_back();

	for (auto s: max_strings) {
		s = s.substr(word_1.length());
		std::cout << s << std::endl;
	}	
	
	return 1;
}

// Process the file "lorem.txt" to insert the words in lorem.txt and store the relevant context as needed.
void Trie::processContext()
{
	// root = getNode();
	std::ifstream lorem;
	lorem.open("lorem.txt");
	std::string word_1;
	std::string word_2;
	if (lorem >> word_1) {
		while (lorem >> word_2) {
			// std::cout << "Processed word: " << word_1+word_2 << std::endl;
			// std::cout << "Root address: " << root;
			count_map[word_1+word_2]++;
			insert(root, word_1+word_2);
			// std::cout << "Inserted word: " << word_1+word_2 << std::endl;
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
		// std::cout << "Found query ending with " << key << std::endl;
		return word_node;
	}
	return my_search(word_node, key.substr(1));
}