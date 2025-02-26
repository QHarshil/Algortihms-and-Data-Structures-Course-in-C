// You must submit this test file with your code implementation.
// include all tests that you used to test your binary search tree implementation
// Compile this assignment with: gcc -Wall -g bst_tests.c my_bst.c -o tests
// This is a great assignment to practice debugging.
// Run with: gdb ./tests --tui
// Then type 'start'
// Then type 'next' or 'n' and enter
// See the GDB debugging video for more information

#include <stdio.h>
#include <stdlib.h>

#include "my_bst.h"

// Write more tests here to test your implementation.
// We will use our own test suite (i.e. replacing this file)
// in order to test your implementation from my_bst.

// Testing allocation
int unitTest1()
{
    int result;
    tree_t *testBST = bst_create();
    if (testBST != NULL)
    {
        result = 1;
    }
    else
    {
        result = 0;
    }
    bst_free(testBST);
    return result;
}

// Add and find a node
int unitTest2()
{
    int result;
    tree_t *testBST = bst_create();
    bst_add(testBST, 78);
    result = bst_find(testBST, 78);
    bst_free(testBST);
    return result;
}

// Sums the nodes in a BST
int unitTest3()
{
    int result;
    tree_t *testBST = bst_create();
    bst_add(testBST, 5);
    result = bst_sum(testBST);
    bst_free(testBST);

    if (result == 5)
    {
        return 1;
    }
    return 0;
}

// Testing if the tree is empty after creation
int unitTest4() {
    tree_t *testBST = bst_create();
    int result = bst_empty(testBST) == 1;
    bst_free(testBST);
    return result;
}

// Testing addition and size increment
int unitTest5() {
    tree_t *testBST = bst_create();
    for (int i = 1; i <= 100; ++i) {
        bst_add(testBST, i);
    }
    int result = (bst_size(testBST) == 100);
    bst_free(testBST);
    return result;
}

// Testing sum of the elements
int unitTest6() {
    tree_t *testBST = bst_create();
    int expected_sum = 0;
    for (int i = 1; i <= 50; ++i) {
        bst_add(testBST, i);
        expected_sum += i;
    }
    int result = (bst_sum(testBST) == expected_sum);
    bst_free(testBST);
    return result;
}

// Testing find functionality
int unitTest7() {
    tree_t *testBST = bst_create();
    bst_add(testBST, 20);
    bst_add(testBST, 30);
    bst_add(testBST, 10);
    int result = (bst_find(testBST, 20) && bst_find(testBST, 30) && !bst_find(testBST, 99));
    bst_free(testBST);
    return result;
}

// Test tree structure and printing order
int unitTest8() {
    tree_t *testBST = bst_create();
    bst_add(testBST, 50);
    bst_add(testBST, 30);
    bst_add(testBST, 70);
    bst_add(testBST, 20);
    bst_add(testBST, 40);
    bst_add(testBST, 60);
    bst_add(testBST, 80);
    printf("Tree should print in ascending order:\n");
    bst_print(testBST, 0);  // Should print 20 30 40 50 60 70 80
    printf("Tree should print in descending order:\n");
    bst_print(testBST, 1);  // Should print 80 70 60 50 40 30 20
    int result = 1; 
    bst_free(testBST);
    return result;
}

// Test handling of NULL tree input for various functions
int unitTest9() {
    int result = 1;
    result &= bst_empty(NULL) == 1; // Should return 1, as NULL tree is empty
    result &= bst_size(NULL) == 0;  // Should handle NULL safely
    result &= bst_find(NULL, 10) == 0; // Should return 0 as value cannot be found in NULL tree
    return result;
}

int unitTest10() {
    tree_t *testBST = bst_create();
    for (int i = 1; i <= 100; i++) {
        bst_add(testBST, i);
    }
    int result = bst_find(testBST, 1) && bst_find(testBST, 50) && bst_find(testBST, 100) && !bst_find(testBST, 101);
    bst_free(testBST);
    return result;
}

int unitTest11() {
    tree_t *testBST = bst_create();
    for (int i = 1; i <= 100; i++) {
        bst_add(testBST, i);
    }
    int result = (bst_size(testBST) == 100);
    bst_free(testBST);
    return result;
}

int unitTest12() {
    tree_t *testBST = bst_create();
    int expected_sum = 0;
    for (int i = 0; i < 50; i++) {
        bst_add(testBST, i);
        expected_sum += i;
    }
    int result = (bst_sum(testBST) == expected_sum);
    bst_free(testBST);
    return result;
}

int unitTest13() {
    tree_t *testBST = bst_create();
    int expected_sum = 0;
    for (int i = 49; i >= 0; i--) {
        bst_add(testBST, i);
        expected_sum += i;
    }
    int result = (bst_sum(testBST) == expected_sum);
    bst_free(testBST);
    return result;
}

int unitTest14() {
    tree_t *testBST = bst_create();
    for (int i = 1; i <= 50; i++) { // Sequential addition creates a linked list shape
        bst_add(testBST, i);
    }
    int result = (bst_sum(testBST) == 1275 && bst_size(testBST) == 50); // Sum of first 50 natural numbers
    bst_print(testBST, 0); // Visual check
    bst_free(testBST);
    return result;
}

int unitTest15() {
    tree_t *testBST = bst_create();
    bst_add(testBST, 50);
    for (int i = 1; i <= 25; i++) {
        bst_add(testBST, i);  // Left side of V
        bst_add(testBST, 50 + i); // Right side of V
    }
    int result = (bst_size(testBST) == 51); // Check size for correctness
    bst_print(testBST, 0); // Visual check
    bst_free(testBST);
    return result;
}

int unitTest16() {
    tree_t *testBST = bst_create();
    // Inserting in an order that tends to balance the tree
    int nums[] = {30, 15, 45, 10, 20, 40, 50, 5, 12, 18, 25, 35, 42, 48, 55};
    int expected_sum = 0;
    for (int i = 0; i < sizeof(nums) / sizeof(nums[0]); i++) {
        bst_add(testBST, nums[i]);
        expected_sum += nums[i];
    }
    int result = (bst_sum(testBST) == expected_sum && bst_size(testBST) == 15);
    bst_print(testBST, 0); // Visual check for balance and structure
    bst_free(testBST);
    return result;
}

int unitTest17() {
    int result = 1;
    result &= (bst_empty(NULL) == 1); // Should be considered empty
    result &= (bst_size(NULL) == 0);  // NULL tree has size 0
    result &= (bst_find(NULL, 10) == 0); // No value can be found in a NULL tree
    result &= (bst_sum(NULL) == 0); // Sum of NULL tree should be safely handled, if modified to not exit
    return result;
}

// added new tests
int (*unitTests[])(void) = {
    unitTest1,
    unitTest2,
    unitTest3,
    unitTest4,
    unitTest5,
    unitTest6,
    unitTest7,
    unitTest8,
    unitTest9,
    unitTest10,
    unitTest11,
    unitTest12,
    unitTest13,
    unitTest14,
    unitTest15,
    unitTest16,
    unitTest17,
    NULL};

// ====================================================
// ================== Program Entry ===================
// ====================================================
int main() {
    unsigned int testsPassed = 0;
    int counter = 0;

    // Loop through the unit test function pointers until a NULL pointer is encountered
    while (unitTests[counter] != NULL) {
        printf("========unitTest %d========\n", counter + 1); 
        if (1 == unitTests[counter]()) { 
            printf("passed test\n");
            testsPassed++;
        } else {
            printf("failed test, missing functionality, or incorrect test\n");
        }
        counter++;
    }

    printf("%d of %d tests passed\n", testsPassed, counter);

    return 0;
}
