// =================== Support Code =================
// Binary Search Tree ( BST ).
//
// - Implement each of the functions to create a working BST.
// - Do not change any of the function declarations
//   - (i.e. tree_t* bst_create() should not have additional arguments)
// - You should not have any 'printf' statements in your BST functions other than the bst_print function. 
//   - (You may consider using these printf statements to debug, but they should be removed from your final version)
// - You may add any helper functions that you think you need (if any, or otherwise for debugging)
// VFS23S
// ==================================================
#ifndef MYBST_H
#define MYBST_H

// Create a node data struct to store data within
// our BST. In our case, we will stores 'integers'
typedef struct Treenode{
    int data;               // data each node holds
    struct Treenode* leftChild; // pointer to left child (if any)
    struct Treenode* rightChild;// pointer to right child (if any)
} treenode_t;

// Our Binary Search Tree data structure
// Our BST holds a pointer to the root node in our BST.
typedef struct tree{
    unsigned int size;  // Size keeps track of how many items are in the BST.
                        // Size should be incremented when we add.
    treenode_t* source;    // source points to the root node in our BST.
} tree_t;

// Function declarations.
// When we declare the functions in the .h file
// it is a 'promise' to the compiler that the code
// for the function will be found somewhere.
//
// In our case, when we link in the my_bst.c file, then
// the implementations of the functions will be found.
tree_t* bst_create();
int bst_empty(tree_t* t);
int bst_add(tree_t* t, int item);
void bst_print(tree_t* t, int order);
int bst_sum(tree_t *t);
int bst_find(tree_t * t, int value);
unsigned int bst_size(tree_t* t);
void bst_free(tree_t* t);

#endif
