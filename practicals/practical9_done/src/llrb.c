#include "../include/llrb.h"
#include "llrb_private.h"
#include <stdlib.h>
#include <math.h>

static NodePtr llrb_put_impl(NodePtr head, Key key, Value val) {
    if (head == NULL) {
        return createRBNode(key, val, RED);
    }
    if (less(key, head->key)) {
        head->left = llrb_put_impl(head->left, key, val);      
    } else if (greater(key, head->key)) {
        head->right = llrb_put_impl(head->right, key, val);
    } else {
        head->val = val;
    }

    if (isRed(head->right) && !isRed(head->left)) head = rotateLeft(head);
    if (isRed(head->left) && isRed(head->left->left)) head = rotateRight(head);
    if (isRed(head->left) && isRed(head->right)) flipColors(head);

    head->count = 1 + nodeSize(head->left) + nodeSize(head->right);
    return head;
}

NodePtr LLRBPut(NodePtr head, Key key, Value val) {
    NodePtr new_head = llrb_put_impl(head, key, val);
    new_head->color = BLACK;
    return new_head;
}

void LLRBDestroy(NodePtr root) {
    if (root == NULL) return;
    LLRBDestroy(root->left);
    LLRBDestroy(root->right);
    free(root);
}

int calculateHeight(NodePtr node) {
    if (node == NULL) return 0;
    int lh = calculateHeight(node->left);
    int rh = calculateHeight(node->right);
    return 1 + (lh > rh ? lh : rh);
}

static int checkHeightAndBalance(NodePtr node, bool *balanced) {
    if (node == NULL || !(*balanced)) return 0;
    int lh = checkHeightAndBalance(node->left, balanced);
    int rh = checkHeightAndBalance(node->right, balanced);
    if (abs(lh - rh) > 1) *balanced = false;
    return 1 + (lh > rh ? lh : rh);
}

bool isBalanced(NodePtr node) {
    bool bal = true;
    checkHeightAndBalance(node, &bal);
    return bal;
}

static int checkBlackBalance(NodePtr node) {            
    if (node == NULL) return 0;
    int lh = checkBlackBalance(node->left);
    int rh = checkBlackBalance(node->right);
    if (lh == -1 || rh == -1 || lh != rh) return -1;        
    return isRed(node) ? lh : lh + 1;
}

static bool checkLLRB(NodePtr n) {     
    if (n == NULL) return true;
    if (isRed(n->right)) return false;
    if (isRed(n) && isRed(n->left)) return false;
    return checkLLRB(n->left) && checkLLRB(n->right);
}

bool test_LLRBProperties(NodePtr root) {
    if (root == NULL) return true;
    if (isRed(root)) return false;
    return checkLLRB(root) && (checkBlackBalance(root) != -1); 
}