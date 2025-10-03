# Leftist Heaps

PLEASE READ THIS FILE CAREFULLY!

## PROBLEM STATEMENT

Implement LeftistHeap that supports the following operations:

- Insert a key into the heap.
- Merge two heaps into one.
- Delete the minimum key from the heap.
- Check if the heap is empty.
- Make the heap empty.
- Retrieve the minimum key from the heap.
- Additionally, you need to maintain the leftist heap property after each operation.

Heap Property: For every node, the key of the parent is less than or equal to the keys of its children.
Leftist Property: The null path length (NPL) of the left child is always greater than or equal to the NPL of the right child.

Ensure that there are no memory leaks (nodes not deleted). You will be penalized otherwise.
Also, deleting a node does not automatically delete its children. Keep this in mind.

READ MORE ABOUT IT IN THE "LH.pdf"!

### YOU HAVE TO ONLY WRITE CODE IN "leftist.cpp"!

## SAMPLE TESTCASES
Some testcases are provided for you to check if your implementation of different class method are correct.
You can also access the interactive mode to check your implementation on custom testcases.
### Testcases can be checked by `make`.
Interactive mode can be accessed by `make interactive`.

## INTERACTIVE MODE

The interactive mode allows you to interact with two Leftist Heaps (heap1 and heap2) using a series of commands. The mode lets you load data into heaps, merge them, print them, empty them, delete the minimum element, and more. Below is a guide on how to use each command.

### Usage - `make interactive`
or after make ./leftist 1

- INSERT heap_number value

  > INSERT value into heap. You must specify which heap to insert the value in providing either 1 or 2.
  > Example: INSERT 1 10
  
- MERGE

  > Merges heap2 into heap1. After merging, heap2 is empty.
  > Example: MERGE

- PRINT <heap_number>

  > Prints the structure of the specified heap (either heap1 or heap2).
  > You must specify which heap to print by providing either 1 or 2.
  > Example: PRINT 1

- EMPTY <heap_number>

  > Empties the specified heap (heap1 or heap2).
  > You need to provide the heap number as either 1 or 2.
  > Example: EMPTY 1

- DELETEMIN

  > Deletes the minimum element from heap1.
  > After deletion, the minimum value is printed.
  > Example: DELETEMIN

- QUIT

  > Exits the interactive mode.
  > Example: QUIT

## TIME COMPLEXITY

You are expected to implement the Leftist Heap so that it adheres to the following time complexity characteristics:

- INSERT:

  > Average Time Complexity: 𝑂(log n)

- MERGE:

  > Time Complexity: 𝑂(log n)

- DELETEMIN:

  > Average Time Complexity: 𝑂(log n)

- FINDMIN:

  > Time Complexity: 𝑂(1)

- EMPTY:

  > Time Complexity: 𝑂(n)
# Make Commands

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

