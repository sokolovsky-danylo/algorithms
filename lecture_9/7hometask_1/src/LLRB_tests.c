#include "LLRB.h"
#include "BST.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void test_LLRBPut() {
    NodePtr head = NULL;

    // Keys to insert into the LLRB tree
    char keys[][2] = {"M", "J", "R", "E", "L", "P", "X", "C", "H", "S", "A"};
    int num_keys = sizeof(keys) / sizeof(keys[0]);

    // Insert keys into the LLRB tree
    for (int i = 0; i < num_keys; i++) {
        head = LLRBPut(head, keys[i], keys[i]); // key == value
    }

    // Print the tree (optional for visualization)
    // BSTPrint(head);

    // Assertions to check the structure of the tree
    assert(equal(head->key, "M")); // Root node
    assert(equal(head->left->key, "J"));
    assert(equal(head->right->key, "R"));

    assert(equal(head->left->left->key, "E"));
    assert(equal(head->left->right->key, "L"));
    assert(equal(head->right->left->key, "P"));
    assert(equal(head->right->right->key, "X"));

    assert(equal(head->left->left->left->key, "C"));
    assert(equal(head->left->left->right->key, "H"));
    assert(equal(head->right->right->left->key, "S"));

    assert(equal(head->left->left->left->left->key, "A"));

    // Check the color of connections
    assert(!isRed(head));        // "M" is black
    assert(!isRed(head->left));   // "J" is black
    assert(!isRed(head->right)); // "R" is black

    assert(isRed(head->left->left)); // "E" is red
    assert(!isRed(head->left->right)); // "L" is black

    assert(!isRed(head->right->left));   // "P" is black
    assert(!isRed(head->right->right)); // "X" is black

    assert(!isRed(head->left->left->left));   // "C" is black
    assert(!isRed(head->left->left->right)); // "H" is black

    assert(isRed(head->right->right->left)); // "S" is red

    assert(isRed(head->left->left->left->left)); // "A" is red

    // Clean up
    BSTDestroy(head);

    printf("test_LLRBPut passed.\n");
}

int main() {
    printf("LLRB Functions Test\n");
    test_LLRBPut();
    printf("\n");

    printf("LLRB vs BSTest\n");
    test_LLRBBalance();
    printf("\n");
    
    printf("LLRB Properties Test\n");
    NodePtr head = NULL;
    char keys[][2] = {"M", "J", "R", "E", "L", "P", "X", "C", "H", "S", "A"};   //keys to insert
    int num_keys = sizeof(keys) / sizeof(keys[0]);  //insert keys into the LLRB tree
    for (int i = 0; i < num_keys; i++) {            //key == value
        head = LLRBPut(head, keys[i], keys[i]);     //key == value
    }
    bool props_ok = test_LLRBProperties(head);      //check if the tree satisfies all LLRB properties
    printf("Does the tree satisfy all LLRB properties? %s\n", props_ok ? "YES" : "NO");

    BSTDestroy(head);   //clean up
    
    printf("All tests passed!\n");

    return 0;
}