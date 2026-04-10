#include "LLRB.h"
#include "LLRB_ops.h"
#include "BST.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

NodePtr llrb_put_impl(NodePtr head, Key key, Value val) {
    // identical to BSTPut()
    if (head == NULL) {                         //if we reach a null position in the tree, create a new red node
        // --- ToDo: Create a new RED node ---
        return createRBNode(key, val, RED);     // new nodes are red by default
    }
    if (less(key, head->key)) {                                //go left if key is smaller than current node's key
        head->left = llrb_put_impl(head->left, key, val);      
    } else if (greater(key, head->key)) {                       //go right if key is greater than current node's key
        head->right = llrb_put_impl(head->right, key, val);
    } else {
        head->val = val;                //if keys are equal, update the value
    }
    // --- ToDo: Fix right-leaning red links ---
    if (isRed(head->right) && !isRed(head->left)) head = rotateLeft(head);
    //if there is a red right link and no red left link, rotate left to fix the right-leaning red link

    // --- ToDo: Fix two consecutive left-leaning red links ---
    if (isRed(head->left) && isRed(head->left->left)) head = rotateRight(head);
    //if there are two consecutive left-leaning red links, rotate right to fix them

    // --- ToDo: Split temporary 4-node ---
    if (isRed(head->left) && isRed(head->right)) flipColors(head);
    //if both left and right links are red, flip colors to split the temporary 4-node

    // identical to BSTPut()
    head->count = 1 + BSTSize(head->left) + BSTSize(head->right); //update count variable after insertion

    // Optional debug assertion: right-leaning reds shouldn't exist
    assert(!isRed(head->right));
    return head;
}

NodePtr LLRBPut(NodePtr head, Key key, Value val) {     //public function of LLRBPut
    NodePtr new_head = llrb_put_impl(head, key, val);   //call the main function
    // --- ToDo: Root must always be black ---
    new_head->color = BLACK;                            //ensure the root is always black
    return new_head;
}

static int checkHeightAndBalance(NodePtr node, bool *balanced) {
    if (node == NULL || !(*balanced)) return 0;                     //if we reach the end of the tree or already found imbalance, return height 0
    int lh = checkHeightAndBalance(node->left, balanced);           //check left subtree and get its height
    int rh = checkHeightAndBalance(node->right, balanced);          //check right subtree and get its height
    if (abs(lh - rh) > 1) *balanced = false;             //if the height difference is greater than 1, mark as unbalanced   
    return 1 + (lh > rh ? lh : rh);     //return height of the current node as 1 + max of left and right subtree heights
}

    bool isBalanced(NodePtr node) {
    bool bal = true;            //balanced by default
    checkHeightAndBalance(node, &bal);      //bal false if we find any imbalance in the tree
    return bal;
}

static int checkBlackBalance(NodePtr node) {            
    if (node == NULL) return 0;                 //if we reach the end of the tree, return black height 0
    int lh = checkBlackBalance(node->left);     //check left subtree and get its black height
    int rh = checkBlackBalance(node->right);    //check right subtree and get its black height
    if (lh == -1 || rh == -1 || lh != rh) return -1;        
        //if we find any imbalance in black heights, return -1 to indicate failure
    return isRed(node) ? lh : lh + 1;   //
}

static bool checkLLRB(NodePtr n) {     
    if (n == NULL) return true;                 //if we reach the end of the tree, return true (base case)
    if (isRed(n->right)) return false;            // no red right links
    if (isRed(n) && isRed(n->left)) return false; // no consecutive reds
    return checkLLRB(n->left) && checkLLRB(n->right);   // recursively check left and right subtrees
}

bool test_LLRBProperties(NodePtr root) {        //check properties
    if (root == NULL) return true;              //if the tree is empty, it satisfies all properties
    if (isRed(root)) return false;              //the root must be black
    return checkLLRB(root) && (checkBlackBalance(root) != -1); 
    //roots must be black, no red links, equal black height on all paths, and no consecutive red links
}

void test_LLRBBalance() {
    NodePtr bst = NULL, llrb = NULL;        //create empty trees
    char* keys[] = {"A","B","C","D","E","F","G","H","I","J"};       //keys to insert
    for (int i = 0; i < 10; i++) {                  //insert keys into both trees
        bst  = BSTPut(bst,   keys[i], keys[i]);     //key == value
        llrb = LLRBPut(llrb, keys[i], keys[i]);     //key == value
    }
    printf("BST Balanced: %s | LLRB Balanced: %s\n",    
           isBalanced(bst)  ? "YES" : "NO",
           isBalanced(llrb) ? "YES" : "NO");
    BSTDestroy(bst);
    BSTDestroy(llrb);
}