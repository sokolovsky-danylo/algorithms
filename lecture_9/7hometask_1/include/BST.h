#ifndef BST_H
#define BST_H

#include "node.h"

typedef Node* NodePtr;

NodePtr BSTPut(NodePtr head, Key key, Value val);
Value BSTGet(NodePtr head, Key key);
NodePtr BSTFloor(NodePtr head, Key key);
NodePtr BSTDelete(NodePtr head, Key key);
void BSTDestroy(NodePtr head);
int BSTSize(NodePtr head);

NodePtr BSTCeiling(NodePtr head, Key key);
int BSTRank(NodePtr head, Key key);
NodePtr BSTSelect(NodePtr root, int k);
Key BSTMin(NodePtr head);
Key BSTMax(NodePtr head);
NodePtr BSTDeleteMin(NodePtr root);
NodePtr BSTDeleteMax(NodePtr root);
void BSTPrintReverse(const NodePtr head);
void BSTPrint(const NodePtr head);

int isBST(NodePtr head);

#endif