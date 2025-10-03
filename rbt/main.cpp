#include "rb.h"

int main(int argc, char* argv[])
{
	// int n; std :: cin >> n;
	// assert (n < 10000 && n >= 0);
    unsigned long long n = std::stoull(argv[1]);
    
    // unsigned long long n = 500;
    // unsigned long long n = (unsigned long long)(*argv[1]);
    RedBlackTree tree;

	for ( unsigned long long i = 1; i <= n; i++) {
		// allocating memory to the node and initializing:
		// 1. color as red
		// 2. parent, left and right pointers as NULL
		// 3. data as i-th value in the array

		// calling function that performs rbt insertion of
		// this newly created node
		auto newnodePtr = tree.insert(i);

		// calling function to preserve properties of rb
		// tree
		tree.fixup(newnodePtr);
        std::cout << tree.n_rotations << std::endl;
	}
	// tree.printRBT(tree.getRoot());

	return 0;
}
