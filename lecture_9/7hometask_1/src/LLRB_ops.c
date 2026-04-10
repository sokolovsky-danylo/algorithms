#include "LLRB_ops.h"
#include <assert.h>

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