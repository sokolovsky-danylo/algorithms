#include "llrb_private.h"
#include <stdlib.h>
#include <string.h>

NodePtr createRBNode(Key key, Value val, bool color) {
    NodePtr node = (NodePtr)malloc(sizeof(struct Node));
    node->key = key; 
    node->val = val;
    node->left = NULL; 
    node->right = NULL;
    node->count = 1; 
    node->color = color;
    return node;
}

bool isRed(const NodePtr x) {
    if (x == NULL) return false;
    return x->color == RED;
}

NodePtr rotateLeft(NodePtr h) {
    NodePtr x = h->right;
    h->right = x->left;
    x->left = h;
    x->color = h->color;
    h->color = RED;
    return x;
}

NodePtr rotateRight(NodePtr h) {
    NodePtr x = h->left;
    h->left = x->right;
    x->right = h;
    x->color = h->color;
    h->color = RED;
    return x;
}

void flipColors(NodePtr h) {
    h->color = RED;
    h->left->color = BLACK;
    h->right->color = BLACK;
}

int nodeSize(NodePtr x) {
    if (x == NULL) return 0;
    return x->count;
}

bool less(Key a, Key b) { 
    return strcmp(a, b) < 0; }
bool greater(Key a, Key b) { 
    return strcmp(a, b) > 0; }
bool equal(Key a, Key b) { 
    return strcmp(a, b) == 0; }

Key LLRBGetKey(NodePtr node) { 
    return node ? node->key : NULL; }
NodePtr LLRBGetLeft(NodePtr node) { 
    return node ? node->left : NULL; }
NodePtr LLRBGetRight(NodePtr node) { 
    return node ? node->right : NULL; }
bool LLRBIsRed(NodePtr node) { 
    return isRed(node); }