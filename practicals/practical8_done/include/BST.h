#ifndef BST_H
#define BST_H

#include "node.h"

typedef Node* NodePtr;

NodePtr BSTPut(NodePtr head, Key key, Value val);
Value BSTGet(NodePtr head, Key key);

NodePtr BSTFloor(NodePtr head, Key key);

int BSTSize(NodePtr head);

NodePtr *BSTNodes(NodePtr head, int *arraySize);
void BSTIterate(NodePtr head, void (*func)(NodePtr));

NodePtr BSTDeleteMin(NodePtr root);
NodePtr BSTDelete(NodePtr head, Key key);

void BSTPrint(NodePtr x);

void BSTDestroy(NodePtr head);

#endif