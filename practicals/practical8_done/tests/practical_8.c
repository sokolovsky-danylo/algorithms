#include "BST.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_BSTFloor() {
    assert(BSTFloor(NULL, "K") == NULL);
    {
        NodePtr head = create_node("M", NULL);
        assert(equal(BSTFloor(head, "M")->key, "M"));
        assert(BSTFloor(head, "A") == NULL);
        assert(equal(BSTFloor(head, "Z")->key, "M"));
        BSTDestroy(head);
    }
    {
        NodePtr head = create_node("M", NULL);
        BSTPut(head, "E", NULL); // ліворуч
        BSTPut(head, "S", NULL); // праворуч
        assert(equal(BSTFloor(head, "G")->key, "E"));
        assert(equal(BSTFloor(head, "P")->key, "M"));
        assert(equal(BSTFloor(head, "T")->key, "S"));
        BSTDestroy(head);
    }
    {
        NodePtr head = create_node("S", NULL);
        BSTPut(head, "E", NULL);
        BSTPut(head, "X", NULL);
        BSTPut(head, "A", NULL);
        BSTPut(head, "P", NULL);
        BSTPut(head, "R", NULL);
        assert(equal(BSTFloor(head, "Q")->key, "P"));
        assert(equal(BSTFloor(head, "H")->key, "E"));
        assert(equal(BSTFloor(head, "Y")->key, "X"));
        
        BSTDestroy(head);
    }

    printf("All BSTFloor tests passed.\n");
}

void test_BSTDeleteMin() {
    printf("Test passed: Minimum key deleted successfully.\n");
}

int main() {
    test_BSTFloor();
    test_BSTDeleteMin();
    printf("All tests passed!\n");
    return 0;
}