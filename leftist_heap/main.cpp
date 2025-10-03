#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cassert>
#include <iomanip>

#include "leftist.h"

using namespace std;

// ************************************************************
// DO NOT CHANGE ANYTHING IN THIS FILE EXCEPT main AND runTestCases()

class HeapPrinter
{
public:
    void printHeap(const LeftistHeap &heap) const;

private:
    void printHeap(const LeftistNode *node, const std::string &prefix, bool isLeft) const;
};


void HeapPrinter::printHeap(const LeftistHeap &heap) const
{
    printHeap(heap.getRoot(), "", true);
}

// This function prints the HEAP using ASCII characters using the
// format:
//
//   root
//       |-- left child
//       \-- right child
//
// where the left and right heaps are printed recursively in
// the same format.
//
// You may use this for debugging purposes.
//
void HeapPrinter::printHeap(const LeftistNode *node, const std::string &prefix, bool isLeft) const
{
    if (node != nullptr)
    {
        std::cout << prefix;

        std::cout << (isLeft ? "|-- " : "\\-- ");
        std::cout << node->key << std::endl;

        std::string childPrefix = prefix + (isLeft ? "|   " : "    ");

        printHeap(node->left, childPrefix, true);
        printHeap(node->right, childPrefix, false);
    }
}


bool checkMinHeap(const LeftistNode *node)
{
    if (node == nullptr)
        return true;
    bool leftOk = (node->left == nullptr) || (node->left->key >= node->key);
    bool rightOk = (node->right == nullptr) || (node->right->key >= node->key);
    if (!leftOk || !rightOk)
    {
        cout << "Heap property violated at node with key " << node->key << endl;
    }
    return leftOk && rightOk && checkMinHeap(node->left) && checkMinHeap(node->right);
}

int getNullPathLength(const LeftistNode *node)
{
    if (node == nullptr)
        return -1;
    else
        return node->npl;
}

bool checkNPLProperty(const LeftistNode *node)
{
    if (node == nullptr)
        return true;

    int leftNPL = getNullPathLength(node->left);
    int rightNPL = getNullPathLength(node->right);
    if (leftNPL < rightNPL)
    {
        cout << "NPL violation at node with key " << node->key << endl;
        return false;
    }
    return checkNPLProperty(node->left) && checkNPLProperty(node->right) && (node->npl == min(leftNPL, rightNPL) + 1);
}

bool testLeftistHeap(const LeftistHeap &heap)
{
    const LeftistNode *root = heap.getRoot();
    if (root == nullptr)
        return true;

    bool isMinHeap = checkMinHeap(root);
    bool validNPL = checkNPLProperty(root);

    return isMinHeap && validNPL;
}

void runTestCases()
{
    // runTestCases operate on testcases which merge the heaps and print the merged by deleting mins.
    LeftistHeap heap1, heap2;
    string line;

    // skip the leftover newline from mode line
    if (line.empty() && cin.peek() == '\n')
    {
        cin.ignore();
    }

    // read heap1 from line 2
    if (!getline(cin, line) || line.empty())
    {
        cerr << "No input for first heap (line 2)!" << endl;
        return;
    }
    {
        stringstream ss(line);
        int x;
        while (ss >> x)
        {
            heap1.insert(x);
            if (!testLeftistHeap(heap1))
            {
                cout << "Heap1 invalid after insertion of " << x << endl;
                return;
            }
        }
    }

    // read heap2 from line 3
    if (!getline(cin, line) || line.empty())
    {
        cerr << "No input for second heap (line 3)!" << endl;
        return;
    }
    {
        stringstream ss(line);
        int x;
        while (ss >> x)
        {
            heap2.insert(x);
            if (!testLeftistHeap(heap2))
            {
                cout << "Heap2 invalid after insertion of " << x << endl;
                return;
            }
        }
    }

    // merge heaps
    heap1.merge(heap2);
    if (!testLeftistHeap(heap1))
    {
        cout << "Merged heap invalid!" << endl;
        return;
    }

    // delete all elements to show sorted order
    while (!heap1.isEmpty())
    {
        int minItem;
        heap1.deleteMin(minItem);
        cout << minItem << " ";
        if (!testLeftistHeap(heap1))
        {
            cout << "\nHeap invalid after deletion!" << endl;
            return;
        }
    }
    cout << endl;
}

void interactiveMode()
{
    // there are some testcases which checks for other leftistHeap functions like print heap, merge, insert and deletemin explicitly.
    HeapPrinter printer;
    LeftistHeap heap1, heap2;
    string command;
    while (true)
    {
        cout << "-> ";
        getline(cin, command);

        vector<string> args;
        stringstream ss(command);
        string token;
        while (ss >> token)
            args.push_back(token);

        if (args.empty())
            continue;
        if (args[0] == "INSERT")
        {
            if (args.size() < 3)
            {
                cout << "Usage: INSERT <heap number (1 or 2)> <value>" << endl;
                continue;
            }
            int heapNumber = stoi(args[1]);
            int value = stoi(args[2]);

            if (heapNumber == 1)
            {
                heap1.insert(value);
                cout << "Inserted " << value << " into Heap1" << endl;
            }
            else if (heapNumber == 2)
            {
                heap2.insert(value);
                cout << "Inserted " << value << " into Heap2" << endl;
            }
            else
            {
                cout << "Invalid heap number! Use 1 or 2." << endl;
            }
        }
        else if (args[0] == "MERGE")
        {
            heap1.merge(heap2);
            cout << "Heap2 merged to Heap1 and Heap2 is empty!" << endl;
        }
        else if (args[0] == "PRINT")
        {
            if (args.size() < 2)
            {
                cout << "Error: Please specify which heap to print (1 or 2)." << endl;
                continue;
            }
            cout << endl;
            int choice = stoi(args[1]);

            if (choice == 1)
                printer.printHeap(heap1);
            else if (choice == 2)
                printer.printHeap(heap2);
            else
                cout << "Invalid choice!" << endl;
        }
        else if (args[0] == "EMPTY")
        {
            if (args.size() < 2)
            {
                cout << "Error: Usage is EMPTY <heap number (1 or 2)>" << endl;
                continue;
            }

            int heapNumber = stoi(args[1]);

            if (heapNumber == 1)
            {
                heap1.makeEmpty();
                cout << "Heap1 emptied!" << endl;
            }
            else if (heapNumber == 2)
            {
                heap2.makeEmpty();
                cout << "Heap2 emptied!" << endl;
            }
            else
            {
                cout << "Invalid heap number! Use 1 or 2." << endl;
            }
        }
        else if (args[0] == "DELETEMIN")
        {
            int minItem;
            heap1.deleteMin(minItem);
            cout << "Deleted minimum element: " << minItem << endl;
        }
        else if (args[0] == "QUIT")
        {
            break;
        }
        else
        {
            cout << "Invalid command!" << endl;
        }
    }
}

int main(int argc, char **argv) {
    char mode = '0';
    if( argc >= 2 ) {
      if( argv[1][0] == '1' ) {
        cout << "Entering in the interactive mode:\n";
        mode = '1';
      }else if (freopen(argv[1], "r", stdin) == nullptr) {
        std::cerr << "Error: Could not open input file " << argv[1] << std::endl;
        cout<<"Give mode of operation:\n 0 for interactive testing \n"
          "<file> for feeding testcases via file \n" << endl;
        return 1;
      }
    }

    if (mode == '0')
    {
        int testCase = 0;
        cin >> testCase;
        if (testCase == 1)
            interactiveMode();
        else
            runTestCases();
    }
    else if (mode == '1')
    {
        interactiveMode();
    }
    else
    {
        cout << "Invalid mode!" << endl;
    }

    return 0;
}
