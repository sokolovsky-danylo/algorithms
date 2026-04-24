#ifndef LLRB_PRIVATE_H
#define LLRB_PRIVATE_H

#include "../include/llrb.h"

#define RED true
#define BLACK false

struct Node {
    Key key;
    Value val;
    struct Node *left;
    struct Node *right;
    int count;
    bool color; 
};

NodePtr rotateLeft(NodePtr h);
NodePtr rotateRight(NodePtr h);
void flipColors(NodePtr h);
bool isRed(const NodePtr x);
NodePtr createRBNode(Key key, Value val, bool color);
int nodeSize(NodePtr x);

bool less(Key a, Key b);
bool greater(Key a, Key b);
bool equal(Key a, Key b);

#endif // LLRB_PRIVATE_H