#include "bst.h"
#include <string>

using std::cin, std::cout, std::string, std::endl;
int main() {
    // cout << "Enter a data type for KEYS and VALUES, space seperated: ";
    string key_type;
    string value_type;
    cin >> key_type >> value_type;
    cout << endl;
    BST<char, int> tree;
    while (true) {
        cout << "Enter action: ";
        char action;
        std::cin >> action;
        cout << endl;
        if (action=='i') {
            // action key value
            int * key_add = new int;
            char * value_add = new char;
            cin >> *key_add >> *value_add;
            tree.insert(key_add, value_add);
            cout << "Node inserted" << endl;
        }
        if (action=='d') {
            int key;
            cin >> key;
            tree.delete_key(&key);
            cout << "Node deleted" << endl;

        }
        if (action=='f') {
            int key;
            cin >> key;
            TreeNode<char, int>* node = tree.search(&key);
            if (node != nullptr) {
                cout << "Found value " << node->data << " at key " << node->key << endl;
            }
            else cout << "Not found" << endl; 
        }
        if (action=='p') {
            std::vector<std::vector<char>> tree_print  = tree.print();
        }
    }
}