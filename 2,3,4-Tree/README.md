Mr KG, finds red-black trees very pointless and unnecessarily difficult. 
Hence, he turns his attention to 2-3-4 trees. 
Our job, in this part of the lab, is to show Mr. KG that red-black trees are just as powerful as 2-3-4 trees.

So, what is a 2-3-4 tree?
A 2-3-4 tree (also called a 2-4 tree) is a self-balancing data structure.
The numbers mean a tree where every node with children (internal node) has either 
two, three, or four child nodes:

- 2-node has one data element, and if internal, has two child nodes;
- 3-node has two data elements, and if internal, has three child nodes;
- 4-node has three data elements, and if internal, has four child nodes;

The key properties we consider are as follows:
Every node (leaf or internal) is a 2-node, 3-node or a 4-node, and holds one, two, or three data elements, respectively.
All leaves are at the same depth (the bottom level). (Path from root to any leaf is of same length)
All data is kept in sorted order (within a node as well as in the entire tree), much like a binary search tree

This would be a good time to think about how insertions (and if you're feeling bold, deletions) happen in 2-3-4 trees.
Some of you may think, at this stage, that 2-3-4 trees are more organised than red black trees
while others may believe red black trees have a colourful edge to them (no pun intended).

But here is the key idea we will explore.
2-3-4 trees are isomorphic to red–black trees, meaning that they are EQUIVALENT data structures. 
(What does even equivalence of data structures mean?)
In other words, for every 2-3-4 tree, there exists at least one and at most one red–black tree 
with data elements in the same order. 
Moreover, insertion and deletion operations on 2–3–4 trees that cause node expansions, 
splits and merges are equivalent to the color-flipping and rotations in red–black trees.

This mind blowing result allows us to implement one as the other. 
Hence, instead of implementing a 2-3-4 tree from scratch, which is quite difficult,
let us exploit the idea that red black trees are equivalent to 2-3-4 trees
and the fact that we have an implementation of red black trees (cue part 1),
and implement a 2-3-4 tree as a red black tree.

The previous part of the lab has been reused here. 
Reuse your (hopefully) working implementation of red black trees to make a 2-3-4 tree.
The 2-3-4 tree class has an insert, convert and the constructor to be implemented only
while the only data member is a red-black tree. 

The insert function inserts an element into our 2-3-4 tree, such that all properties above are satisfied
The convert function returns the structural 2-3-4 tree where every node is either a 2-node,3-node or 4-node.

Hence, for all practical and theoretical purposes,
can we use red black trees and 2-3-4 trees interchangeably?

More Reading Material: https://azrael.digipen.edu/~mmead/www/Courses/CS280/Trees-Mapping2-3-4IntoRB.html# Make Commands

```
make             # Build and Run Tests
make build       # Build
make runtests    # Run Tests
make clean       # Clean Temporary Files
```
Please read Makefile to understand the above commands!

# VS Code interface

You can open this folder in VS Code. The problem folder is configured 
to enable debugging.

After opening the folder, click on Run > Start Debugging or press F5.
This will run your program on input ./test/test1/input.txt.
You may place breakpoints to pause the program at any desired location.

You can modify "./.vscode/launch.json" to run any test of your choice.

In some labs, there may be multiple binaries, and you may need to modify 
the binary name in the ./.vscode/settings.json file.

```
    "problem": "<binary>",
```

# General Instructions

- Read all .h and .cpp files before starting.
- Do not include any additional header files.
- Do not modify files other than the specified files. Any other changes 
  will not be considered during evaluation.
- You are expected to submit an efficient implementation. Inefficient 
  solutions will lose marks.

