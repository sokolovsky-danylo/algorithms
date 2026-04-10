#include "node.h"
#include <stdlib.h>

Node *create_node(Key key, Value val) {                 //function to create a new node
    Node *new_node = (Node *)malloc(sizeof(Node));      //allocate memory for the new node
    if (!new_node) return NULL;                         //if memory allocation fails, return NULL
    new_node->key = key;                                //set the key of the new node
    new_node->val = val;                                //set the value of the new node     
    new_node->left = NULL;                              //initialize left and right children to NULL   
    new_node->right = NULL;                             //initialize left and right children to NULL
    new_node->count = 1;                                //initialize count variable to 1 for the new node
    return new_node;                                //return the pointer to the new node    
}