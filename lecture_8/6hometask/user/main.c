#include "BST.h"
#include <assert.h>
#include <stdio.h>

void test_BSTCeiling() {                            //test the BSTCeiling function with various cases to ensure it correctly finds the smallest key greater than or equal to the given key, including edge cases where the ceiling does not exist
    NodePtr head = NULL;                            //start with an empty tree and check that the ceiling of any key is NULL
    assert(BSTCeiling(head, "A") == NULL);          //check that the ceiling of "A" in an empty tree is NULL

    head = create_node("M", NULL);                  //create a tree with a single node "M" and check that the ceiling of "M" is "M", the ceiling of a smaller key is "M", and the ceiling of a larger key is NULL
    assert(equal(BSTCeiling(head, "A")->key, "M")); //check that the ceiling of "A" is "M"
    assert(BSTCeiling(head, "Z") == NULL);          //check that the ceiling of "Z" is NULL

    BSTPut(head, "F", NULL);                            //add a smaller key "F" and check that the ceiling of "E" is "F", the ceiling of "F" is "F", and the ceiling of "G" is "M"
    assert(equal(BSTCeiling(head, "C")->key, "F"));     //check that the ceiling of "C" is "F"

    BSTDestroy(head);                                   //destroy the tree and create a new tree with a single node "M" to check that the ceiling of a smaller key is "M" and the ceiling of a larger key is NULL
    head = create_node("M", NULL);                      //create a new tree with a single node "M"
    BSTPut(head, "T", NULL);                            //add a larger key "T" and check that the ceiling of "G" is "M", the ceiling of "M" is "M", and the ceiling of "P" is "T"
    assert(equal(BSTCeiling(head, "P")->key, "T"));     //check that the ceiling of "P" is "T"

    BSTDestroy(head);                                   //destroy the tree and create a new tree with a single node "M" to check that the ceiling of a smaller key is "M" and the ceiling of a larger key is NULL
    head = create_node("M", NULL);                      //create a new tree with a single node "M"
    BSTPut(head, "J", NULL);                            //add a smaller key "J" and check that the ceiling of "G" is "J", the ceiling of "J" is "J", and the ceiling of "K" is "M"
    BSTPut(head, "F", NULL);                            //add a smaller key "F" and check that the ceiling of "E" is "F", the ceiling of "F" is "F", and the ceiling of "G" is "J"
    assert(equal(BSTCeiling(head, "E")->key, "F"));     //check that the ceiling of "E" is "F"

    BSTDestroy(head);                               //destroy the tree and create a new tree with a single node "M" to check that the ceiling of a smaller key is "M" and the ceiling of a larger key is NULL   
    head = create_node("M", NULL);                  //create a new tree with a single node "M"
    BSTPut(head, "P", NULL);                        //add a larger key "P" and check that the ceiling of "G" is "M", the ceiling of "M" is "M", and the ceiling of "K" is "M"
    BSTPut(head, "T", NULL);                        //add a larger key "T" and check that the ceiling of "G" is "M", the ceiling of "M" is "M", the ceiling of "P" is "P", and the ceiling of "S" is "T"
    assert(equal(BSTCeiling(head, "S")->key, "T")); //check that the ceiling of "S" is "T"

    BSTDestroy(head);                               //destroy the tree and create a new tree with a single node "M" to check that the ceiling of a smaller key is "M" and the ceiling of a larger key is NULL
    head = create_node("M", NULL);                  //create a new tree with a single node "M"
    BSTPut(head, "F", NULL);                        //add a smaller key "F" and check that the ceiling of "E" is "F", the ceiling of "F" is "F", and the ceiling of "G" is "M"
    BSTPut(head, "T", NULL);                        //add a larger key "T" and check that the ceiling of "G" is "M", the ceiling of "M" is "M", and the ceiling of "P" is "T"
    assert(equal(BSTCeiling(head, "G")->key, "M")); //check that the ceiling of "G" is "M"

    BSTDestroy(head);                               //destroy the tree and create a new tree with a single node "M" to check that the ceiling of a smaller key is "M" and the ceiling of a larger key is NULL
    head = create_node("M", NULL);                  //create a new tree with a single node "M"
    BSTPut(head, "P", NULL);                        //add a larger key "P" and check that the ceiling of "G" is "M", the ceiling of "M" is "M", and the ceiling of "K" is "M"
    BSTPut(head, "T", NULL);                        //add a larger key "T" and check that the ceiling of "G" is "M", the ceiling of "M" is "M", the ceiling of "P" is "P", and the ceiling of "S" is "T"
    BSTPut(head, "W", NULL);                        //add a larger key "W" and check that the ceiling of "G" is "M", the ceiling of "M" is "M", the ceiling of "P" is "P", the ceiling of "S" is "T", and the ceiling of "U" is "W"
    assert(equal(BSTCeiling(head, "U")->key, "W")); //check that the ceiling of "U" is "W"

    BSTDestroy(head);                               //destroy the tree and create a new tree with a single node "M" to check that the ceiling of a smaller key is "M" and the ceiling of a larger key is NULL
    head = create_node("M", NULL);                  //create a new tree with a single node "M"
    BSTPut(head, "J", NULL);                        //add a smaller key "J" and check that the ceiling of "G" is "J", the ceiling of "J" is "J", and the ceiling of "K" is "M"
    BSTPut(head, "F", NULL);                        //add a smaller key "F" and check that the ceiling of "E" is "F", the ceiling of "F" is "F", and the ceiling of "G" is "J"
    BSTPut(head, "C", NULL);                        //add a smaller key "C" and check that the ceiling of "B" is "C", the ceiling of "C" is "C", and the ceiling of "D" is "F"
    assert(equal(BSTCeiling(head, "B")->key, "C")); //check that the ceiling of "B" is "C"

    BSTDestroy(head);                               //destroy the tree and create a new tree with a single node "M" to check that the ceiling of a smaller key is "M" and the ceiling of a larger key is NULL
    head = create_node("M", NULL);                  //create a new tree with a single node "M"
    BSTPut(head, "T", NULL);                        //add a larger key "T" and check that the ceiling of "G" is "M", the ceiling of "M" is "M", and the ceiling of "P" is "T"
    BSTPut(head, "F", NULL);                        //add a smaller key "F" and check that the ceiling of "E" is "F", the ceiling of "F" is "F", and the ceiling of "G" is "M"
    BSTPut(head, "J", NULL);                        //add a smaller key "J" and check that the ceiling of "G" is "J", the ceiling of "J" is "J", and the ceiling of "K" is "M"
    BSTPut(head, "H", NULL);                        //add a smaller key "H" and check that the ceiling of "G" is "H", the ceiling of "H" is "H", and the ceiling of "I" is "J"
    assert(equal(BSTCeiling(head, "G")->key, "H")); //check that the ceiling of "G" is "H"

    BSTDestroy(head);                               //destroy the tree and create a new tree with a single node "M" to check that the ceiling of a smaller key is "M" and the ceiling of a larger key is NULL
    printf("ceiling exact cases passed\n");         //check that the ceiling function correctly finds the ceiling of keys that are present in the tree, as well as keys that are not present but have a ceiling in the tree, and keys that do not have a ceiling in the tree 
}

void test_BSTMinMax() {                         //test the BSTMin and BSTMax functions with various cases to ensure they correctly find the minimum and maximum keys in the BST, including edge cases where the tree is empty or has only one node
    NodePtr head = NULL;                        //start with an empty tree and check that the minimum and maximum keys are NULL
    assert(BSTMin(head) == NULL);               //check that the minimum key in an empty tree is NULL
    assert(BSTMax(head) == NULL);               //check that the maximum key in an empty tree is NULL

    head = create_node("M", NULL);              //create a tree with a single node "M" and check that the minimum and maximum keys are "M"
    assert(equal(BSTMin(head), "M"));           //check that the minimum key is "M"
    assert(equal(BSTMax(head), "M"));           //check that the maximum key is "M"

    BSTPut(head, "E", NULL);                    //add a smaller key "E" and check that the minimum key is "E" and the maximum key is still "M"
    BSTPut(head, "A", NULL);                    //add a smaller key "A" and check that the minimum key is "A" and the maximum key is still "M"
    assert(equal(BSTMin(head), "A"));           //check that the minimum key is "A"
    assert(equal(BSTMax(head), "M"));           //check that the maximum key is still "M"

    BSTPut(head, "S", NULL);                    //add a larger key "S" and check that the minimum key is still "A" and the maximum key is "S"
    BSTPut(head, "X", NULL);                    //add a larger key "X" and check that the minimum key is still "A" and the maximum key is "X"
    assert(equal(BSTMax(head), "X"));           //check that the maximum key is "X"

    BSTDestroy(head);                           //destroy the tree and create a new tree with a single node "M" to check that the minimum and maximum keys are "M"
    printf("min max tests passed\n");           //destroy the tree and create a new tree with a single node "M" to check that the minimum and maximum keys are "M"
}

void test_BSTRankSelect() {             //test the BSTRank and BSTSelect functions with various cases to ensure they correctly compute the rank of keys and select keys by rank, including edge cases where the tree is empty or has only one node  
    NodePtr head = NULL;                //start with an empty tree and check that the rank of any key is 0 and selecting any rank returns NULL
    assert(BSTRank(head, "A") == 0);        //check that the rank of "A" in an empty tree is 0
    assert(BSTSelect(head, 0) == NULL);     //check that selecting rank 0 in an empty tree returns NULL

    head = create_node("S", NULL);          //create a tree with a single node "S" and check that the rank of "S" is 0, the rank of a smaller key is 0, the rank of a larger key is 1, selecting rank 0 returns "S", and selecting rank 1 returns NULL
    BSTPut(head, "E", NULL);                //add a smaller key "E" and check that the rank of "E" is 0, the rank of "S" is 1, the rank of a larger key is 2, selecting rank 0 returns "E", and selecting rank 1 returns "S"
    BSTPut(head, "X", NULL);
    BSTPut(head, "A", NULL);
    BSTPut(head, "R", NULL);
    BSTPut(head, "C", NULL);
    BSTPut(head, "H", NULL);

    assert(BSTRank(head, "A") == 0);            //check that the rank of "A" is 0
    assert(BSTRank(head, "E") == 2);
    assert(BSTRank(head, "S") == 5); 
    assert(BSTRank(head, "Z") == 7); 

    assert(equal(BSTSelect(head, 0)->key, "A"));        //check that selecting rank 0 returns "A"
    assert(equal(BSTSelect(head, 2)->key, "E"));        //check that selecting rank 2 returns "E"
    assert(equal(BSTSelect(head, 5)->key, "S"));        //check that selecting rank 5 returns "S"

    BSTDestroy(head);                               //destroy the tree and create a new tree with a single node "S" to check that the rank of "S" is 0, the rank of a smaller key is 0, the rank of a larger key is 1, selecting rank 0 returns "S", and selecting rank 1 returns NULL
    printf("rank select tests passed\n");           //destroy the tree and create a new tree with a single node "S" to check that the rank of "S" is 0, the rank of a smaller key is 0, the rank of a larger key is 1, selecting rank 0 returns "S", and selecting rank 1 returns NULL
}

void test_BSTDeleteMax() {                          //test the BSTDeleteMax function with various cases to ensure it correctly deletes the maximum key from the BST, including edge cases where the tree is empty or has only one node
    NodePtr head = NULL;                            //start with an empty tree and check that deleting the maximum key returns NULL
    assert(BSTDeleteMax(head) == NULL);             //check that deleting the maximum key from an empty tree returns NULL

    head = create_node("M", NULL);                  //create a tree with a single node "M" and check that deleting the maximum key returns NULL and the tree becomes empty
    head = BSTDeleteMax(head);                      //delete the maximum key from the tree and check that the tree becomes empty
    assert(head == NULL);                           //check that the tree is now empty

    head = create_node("M", NULL);                  //create a new tree with a single node "M" and check that deleting the maximum key returns NULL and the tree becomes empty
    BSTPut(head, "E", NULL);                        //add a smaller key "E" and check that deleting the maximum key returns NULL and the tree becomes empty
    BSTPut(head, "A", NULL);                        //add a smaller key "A" and check that deleting the maximum key returns NULL and the tree becomes empty
    head = BSTDeleteMax(head);                      //delete the maximum key from the tree and check that the maximum key "M" is deleted and the new maximum key is "E"
    assert(equal(BSTMax(head), "E"));               //check that the new maximum key is "E"
    
    BSTPut(head, "S", NULL);                    //add a larger key "S" and check that deleting the maximum key returns NULL and the tree becomes empty
    BSTPut(head, "X", NULL);                    //add a larger key "X" and check that deleting the maximum key returns NULL and the tree becomes empty
    head = BSTDeleteMax(head);                  //delete the maximum key from the tree and check that the maximum key "X" is deleted and the new maximum key is "S"
    assert(equal(BSTMax(head), "S"));           //check the max key is s

    BSTDestroy(head);                               //destroy the tree and create a new tree with a single node "M" to check that deleting the maximum key returns NULL and the tree becomes empty
    printf("delete max tests passed\n");            //destroy the tree and create a new tree with a single node "M" to check that deleting the maximum key returns NULL and the tree becomes empty
}

void test_isBST() {                                  //test the isBST function with various cases to ensure it correctly checks if a tree is a binary search tree, including edge cases where the tree is empty or has only one node, and cases where the tree is not a BST due to incorrect key placements
    NodePtr head = create_node("M", NULL);           //create a tree with a single node "M" and check that it is a BST
    BSTPut(head, "E", NULL);                        //add a smaller key "E" and check that the tree is still a BST
    BSTPut(head, "S", NULL);                    //add a larger key "S" and check that the tree is still a BST   
    assert(isBST(head) == 1);                   //check that the tree is a BST

    head->left->key = "Z";                      //manually change the left child's key to "Z" which is greater than "M" to check that the tree is no longer a BST
    assert(isBST(head) == 0);                   //check that the tree is no longer a BST

    head->left->key = "E";                      //change the left child's key back to "E" to restore the BST property, and then manually change the right child's key to "A" which is less than "M" to check that the tree is no longer a BST

    BSTDestroy(head);                       //destroy the tree and create a new tree with a single node "M" to check that it is a BST, and then manually change the left child's key to "Z" which is greater than "M" to check that the tree is no longer a BST
    printf("is bst tests passed\n");        // destroy the tree and create a new tree with a single node "M" to check that it is a BST, and then manually change the left child's key to "Z" which is greater than "M" to check that the tree is no longer a BST
}

int main() {
    test_BSTCeiling();
    test_BSTMinMax();
    test_BSTRankSelect();
    test_BSTDeleteMax();
    test_isBST();
    
    printf("all tests passed\n");
    return 0;
}