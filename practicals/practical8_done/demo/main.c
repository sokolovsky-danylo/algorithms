#include "BST.h"
#include <stdio.h>

int main() {
    BSTPtr root = NULL;
    root = BSTPut(root, "S", NULL);
    root = BSTPut(root, "E", NULL);
    root = BSTPut(root, "A", NULL);
    root = BSTPut(root, "R", NULL);
    root = BSTPut(root, "C", NULL);
    root = BSTPut(root, "H", NULL);

    printf("Min: %s\n", BSTMin(root));
    printf("Max: %s\n", BSTMax(root));
    printf("Reverse order: ");
    BSTPrintReverse(root);
    printf("\nRank of 'R': %d\n", BSTRank(root, "R"));
    
    printf("isBST: %s\n", isBST(root) ? "Yes" : "No");

    BSTDestroy(root);
    return 0;
}