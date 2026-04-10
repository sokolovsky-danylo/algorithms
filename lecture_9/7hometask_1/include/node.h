// include/node.h
#ifndef NODE_H
#define NODE_H

#include "item.h"
#include <stdbool.h>

#define RED true
#define BLACK false

typedef struct Node {
    Key key;
    Value val;
    struct Node *left;
    struct Node *right;
    int count;
    bool color; 
} Node;

typedef Node *NodePtr;

NodePtr createNode(Key key, Value val);
NodePtr createRBNode(Key key, Value val, bool color);
bool isRed(const NodePtr x);
void printNode(const NodePtr node);

#endif