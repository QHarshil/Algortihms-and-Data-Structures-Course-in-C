// Compile this assignment with: gcc -g -Wall main.c -o main
// Use this file to implement testing for your
// doubly linked list implementation
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free
#include <string.h>

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_dll.h"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory. 0x7E7



// ====================================================
// ================== Program Entry ===================
// ====================================================
int main(){
    team_t * team = create_team();
    
    // you can add tests here, but it's easier to add
    // tests to the dll_tests.c file
	    
    return 0;
}
