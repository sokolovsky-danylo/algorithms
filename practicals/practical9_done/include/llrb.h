#ifndef LLRB_H
#define LLRB_H

#include <stdbool.h>

typedef const char* Key;
typedef const char* Value;

typedef struct Node* NodePtr;

NodePtr LLRBPut(NodePtr head, Key key, Value val);
void LLRBDestroy(NodePtr root);

int calculateHeight(NodePtr node);
bool isBalanced(NodePtr node);
bool test_LLRBProperties(NodePtr root);

Key LLRBGetKey(NodePtr node);
NodePtr LLRBGetLeft(NodePtr node);
NodePtr LLRBGetRight(NodePtr node);
bool LLRBIsRed(NodePtr node);

#endif // LLRB_H