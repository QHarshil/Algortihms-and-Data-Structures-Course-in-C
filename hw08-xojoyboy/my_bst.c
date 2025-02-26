// VFS23S
// Include our header file for our my_bst.c
//
#include "my_bst.h"

#include <stdio.h>
#include <stdlib.h>

// Complete all the following functions
// Do not change the function signatures or the header file
// You may include helper functions as needed
// make sure to include your tests in bst_tests.c

// Creates a BST
// Returns a pointer to a newly created BST.
// The BST should be initialized with data on the heap.
// The BST fields should also be initialized to default values(i.e. size=0).
tree_t *bst_create() {
    tree_t *new_tree = malloc(sizeof(tree_t));
    if (new_tree == NULL) {
        return NULL; // Memory allocation failed
    }
    new_tree->size = 0;
    new_tree->source = NULL;
    return new_tree;
}

// BST Empty
// Check if the BST is empty
// Returns 1 if true (The BST is completely empty)
// Returns 0 if false (the BST has at least one element)
int bst_empty(tree_t *t) {
    if (t == NULL || t->source == NULL) {
        return 1;
    }
    return 0;
}


// Adds a new node containing item to the BST
// The item is added in the correct position in the BST.
//  - If the data is less than the current node we traverse left
//  - otherwise we traverse right.
// The bst_function returns '1' upon success
//  - bst_add should increment the 'size' of our BST.
// Returns a -1 if the operation fails.
//      (i.e. the memory allocation for a new node failed).
// Your implementation should should run in O(log(n)) time.
//  - A recursive implementation is required.
static int bst_add_recursive(treenode_t **node, int item) {
    if (*node == NULL) {
        *node = malloc(sizeof(treenode_t));
        if (*node == NULL) return -1; // Memory allocation failed
        (*node)->data = item;
        (*node)->leftChild = NULL;
        (*node)->rightChild = NULL;
        return 1;
    } else if (item < (*node)->data) {
        return bst_add_recursive(&((*node)->leftChild), item);
    } else {
        return bst_add_recursive(&((*node)->rightChild), item);
    }
}

int bst_add(tree_t *t, int item) {
    if (t == NULL) return -1; // Tree is not initialized
    int result = bst_add_recursive(&(t->source), item);
    if (result == 1) t->size++;
    return result;
}


// Prints the tree in ascending order if order = 0, otherwise prints in descending order.
// For NULL tree (i.e., when t == NULL) -- print "(NULL)".
// It should run in O(n) time.
// A recursive implementation is required. 
static void bst_print_recursive(treenode_t *node, int order) {
    if (node == NULL) return;
    if (order == 0) {
        bst_print_recursive(node->leftChild, order);
        printf("%d ", node->data);
        bst_print_recursive(node->rightChild, order);
    } else {
        bst_print_recursive(node->rightChild, order);
        printf("%d ", node->data);
        bst_print_recursive(node->leftChild, order);
    }
}

void bst_print(tree_t *t, int order) {
    if (t == NULL || t->source == NULL) {
        printf("(NULL)\n");
        return;
    }
    bst_print_recursive(t->source, order);
    printf("\n");
}

// Returns the sum of all the nodes in the bst.
// exits the program for a NULL tree. 
// It should run in O(n) time.
// A recursive implementation is required.
static int bst_sum_recursive(treenode_t *node) {
    if (node == NULL) return 0;
    return node->data + bst_sum_recursive(node->leftChild) + bst_sum_recursive(node->rightChild);
}

int bst_sum(tree_t *t) {
    if (t == NULL || t->source == NULL) {
        exit(EXIT_FAILURE); // Handle NULL tree
    }
    return bst_sum_recursive(t->source);
}



// Returns 1 if value is found in the tree, 0 otherwise. 
// For NULL tree it exists the program. 
// It should run in O(log(n)) time.
static int bst_find_recursive(treenode_t *node, int value) {
    if (node == NULL) return 0;
    if (node->data == value) return 1;
    else if (value < node->data) return bst_find_recursive(node->leftChild, value);
    else return bst_find_recursive(node->rightChild, value);
}

int bst_find(tree_t *t, int value) {
    if (t == NULL || t->source == NULL) {
        return 0; // Return 0 to indicate value not found or invalid input
    }
    return bst_find_recursive(t->source, value);
}

// Returns the size of the BST
// A BST that is NULL exits the program.
// (i.e. A NULL BST cannot return the size)
unsigned int bst_size(tree_t *t) {
    if (t == NULL) {
        return 0; // Return 0 for size of an uninitialized tree
    }
    return t->size;
}

// Free BST
// Removes a BST and ALL of its elements from memory.
// This should be called before the program terminates.
static void bst_free_recursive(treenode_t *node) {
    if (node != NULL) {
        bst_free_recursive(node->leftChild);
        bst_free_recursive(node->rightChild);
        free(node);
    }
}

void bst_free(tree_t *t) {
    if (t != NULL) {
        bst_free_recursive(t->source);
        free(t);
    }
}

