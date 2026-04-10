// include/LLRB.h

#ifndef LLRB_H
#define LLRB_H

#include "node.h" // From hometask 6
#include <stdbool.h>

// From 9practical_code/LLRB.h
NodePtr LLRBPut(NodePtr head, Key key, Value val);

// From algorithms_home_task_7.pdf (Task 1)
bool test_LLRBProperties(NodePtr root);
void test_LLRBBalance();

// From algorithms_home_task_7.pdf (Task 2 Dependency / Additional Task)
bool isBalanced(NodePtr node);

#endif