#include "node.h"
#include <stdlib.h>
#include <stdio.h>

NodePtr createNode(Key key, Value val) {
    NodePtr node = (NodePtr)malloc(sizeof(Node));
    node->key = key; node->val = val;
    node->left = NULL; node->right = NULL;
    node->count = 1; node->color = BLACK;
    return node;
}

NodePtr createRBNode(Key key, Value val, bool color) {
    NodePtr node = createNode(key, val);
    node->color = color;
    return node;
}

bool isRed(const NodePtr x) {
    if (x == NULL) return false;
    return x->color == RED;
}

void printNode(const NodePtr node) {
    if (node != NULL) printf("%s ", node->key);
}