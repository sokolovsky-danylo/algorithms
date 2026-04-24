#include "../include/llrb.h"
#include <stdio.h>

int main() {
    printf("LLRB Tree Demo \n");
    NodePtr tree = NULL;
    
    const char* keys[] = {"M", "J", "R", "E", "L", "P", "X", "C", "H", "S", "A"};
    int num_keys = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < num_keys; i++) {
        tree = LLRBPut(tree, keys[i], keys[i]);
    }

    printf("tree Height: %d\n", calculateHeight(tree));
    printf("is balanced O(N): %s\n", isBalanced(tree) ? "YES" : "NO");
    printf("LLRB properties valid: %s\n", test_LLRBProperties(tree) ? "YES" : "NO");

    LLRBDestroy(tree);
    return 0;
}