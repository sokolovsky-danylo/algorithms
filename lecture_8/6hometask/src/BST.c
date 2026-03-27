#include "BST.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>

int BSTSize(NodePtr head) {                             //gets size of the BST
    if (head == NULL) return 0;                         //base case: empty tree has size 0
    return head->count;                                 //returns count variable
}

Value BSTGet(NodePtr head, Key key) {                   //search for value 
    NodePtr x = head;                                   //start at the root
    while (x != NULL) {                                 //loop till end
        if (less(key, x->key)) x = x->left;             //go left if key is smaller than current node's key
        else if (greater(key, x->key)) x = x->right;    //go right if key is greater than current node's key
        else return x->val;                             //if keys are equal, return the value
    }
    return NULL;
}

NodePtr BSTPut(NodePtr head, Key key, Value val) {              //insert key-value pair into the BST
    if (head == NULL) return create_node(key, val);             //make a new node if we reach a null position in the tree
    if (less(key, head->key)) head->left = BSTPut(head->left, key, val);        //go left if key is smaller than current node's key
    else if (greater(key, head->key)) head->right = BSTPut(head->right, key, val);      //go right if key is greater than current node's key
    else head->val = val;                                       //if keys are equal, update the value
    head->count = 1 + BSTSize(head->left) + BSTSize(head->right);       //update count variable after insertion
    return head;                                                //return the (possibly new) head of the subtree
}

NodePtr BSTFloor(NodePtr head, Key key) {                       //find floor of the key in the BST
    if (head == NULL) return NULL;                              //if we reach the end of the tree, return NULL
    if (equal(key, head->key)) return head;                     //if keys are equal, return the current node as the floor
    if (less(key, head->key)) return BSTFloor(head->left, key); //go left if key is smaller than current node's key
    NodePtr t = BSTFloor(head->right, key);                     //go right if key is greater than current node's key, and store the result in t
    if (t != NULL) return t;                                    //if we found a floor in the right subtree, return it
    return head;
}

NodePtr BSTCeiling(NodePtr head, Key key) {                             //find ceiling of the key in the BST
    if (head == NULL) return NULL;                                      //if we reach the end of the tree, return NULL
    if (equal(key, head->key)) return head;                             //if keys are equal, return the current node as the ceiling
    if (greater(key, head->key)) return BSTCeiling(head->right, key);   //go right if key is greater than current node's key
    NodePtr t = BSTCeiling(head->left, key);                            //go left if key is smaller than current node's key, and store the result in t
    if (t != NULL) return t;                                            //if we found a ceiling in the left subtree, return it
    return head;
}

int BSTRank(NodePtr head, Key key) {                                    //find the rank of the key in the BST (number of keys less than the given key)
    if (head == NULL) return 0;                                         //if we reach the end of the tree, return 0
    if (less(key, head->key)) return BSTRank(head->left, key);          //go left if key is smaller than current node's key
    else if (greater(key, head->key)) return 1 + BSTSize(head->left) + BSTRank(head->right, key);   //if key is greater than current node's key, return 1 (for the current node) + size of left subtree + rank in the right subtree
    else return BSTSize(head->left);                    //if keys are equal, return the size of the left subtree, which is the number of keys less than the given key   
}

NodePtr BSTSelect(NodePtr root, int k) {                         //find kth smallest key in the BST (the key with rank k)
    if (root == NULL) return NULL;                               //if we reach the end of the tree, return NULL
    int t = BSTSize(root->left);                                 //size of left subtree gives us the rank of the current node
    if (t > k) return BSTSelect(root->left, k);                 //if k is less than the rank of the current node, go left
    else if (t < k) return BSTSelect(root->right, k - t - 1);   //if k is greater than the rank of the current node, go right and adjust k to account for the nodes we are skipping
    else return root;
}

Key BSTMin(NodePtr head) {                                 //find minimum key in the BST
    if (head == NULL) return NULL;                        //if we reach the end of the tree, return NULL
    while (head->left != NULL) head = head->left;         //keep going left until we find the minimum key
    return head->key;                                     //return the minimum key
}

Key BSTMax(NodePtr head) {                              //find maximum key in the BST
    if (head == NULL) return NULL;                      //if we reach the end of the tree, return NULL
    while (head->right != NULL) head = head->right;     //keep going right until we find the maximum key
    return head->key;                                   //return the maximum key       
}

NodePtr BSTDeleteMin(NodePtr root) {                    //delete the minimum key in the BST
    if (root == NULL) return NULL;                      //if we reach the end of the tree, return NULL
    if (root->left == NULL) {                           //if there is no left child, then the current node is the minimum, so we need to delete it and return its right child to be connected to the parent
        NodePtr t = root->right;                        //store the right child to return after deletion
        free(root);                                     //free the current node
        return t;                                       //return the right child to be connected to the parent
    }
    root->left = BSTDeleteMin(root->left);                          //if there is a left child, recursively delete the minimum in the left subtree
    root->count = 1 + BSTSize(root->left) + BSTSize(root->right);   //update count variable after deletion
    return root;
}

NodePtr BSTDeleteMax(NodePtr root) {                //delete the maximum key in the BST
    if (root == NULL) return NULL;                  //if we reach the end of the tree, return NULL
    if (root->right == NULL) {                      //if there is no right child, then the current node is the maximum, so we need to delete it and return its left child to be connected to the parent
        NodePtr t = root->left;                     //store the left child to return after deletion
        free(root);                                 //free the current node
        return t;                                   //return the left child to be connected to the parent
    }   
    root->right = BSTDeleteMax(root->right);                        //if there is a right child, recursively delete the maximum in the right subtree
    root->count = 1 + BSTSize(root->left) + BSTSize(root->right);   //update count variable after deletion
    return root;
}

NodePtr BSTDelete(NodePtr head, Key key) {                          //delete the key from the BST
    if (head == NULL) return NULL;                                  //if we reach the end of the tree, return NULL
    if (less(key, head->key)) head->left = BSTDelete(head->left, key);              //go left if key is smaller than current node's key
    else if (greater(key, head->key)) head->right = BSTDelete(head->right, key);    //go right if key is greater than current node's key
    else {
        if (head->right == NULL) {                   //if there is no right child, then we can replace the current node with its left child
            NodePtr t = head->left;                  //store the left child to return after deletion
            free(head);                              //free the current node
            return t;                                //return the left child to be connected to the parent       
        }
        if (head->left == NULL) {                    //if there is no left child, then we can replace the current node with its right child
            NodePtr t = head->right;                //store the right child to return after deletion
            free(head);                             //free the current node
            return t;       
        }
        NodePtr t = head;                                   //if there are two children, we need to find the minimum in the right subtree to replace the current node, and then delete that minimum node from the right subtree
        NodePtr min_n = t->right;                           //find the minimum node in the right subtree
        while (min_n->left != NULL) min_n = min_n->left;    //keep going left until we find the minimum node
        head = min_n;                                       //replace the current node with the minimum node from the right subtree
        head->right = BSTDeleteMin(t->right);               //delete the minimum node from the right subtree and connect the right child of the minimum node to the current node
        head->left = t->left;                               //connect the left child of the original node to the current node
        free(t);
    }
    head->count = 1 + BSTSize(head->left) + BSTSize(head->right);   //update count variable after deletion
    return head;        
}

void BSTDestroy(NodePtr head) {                             //destroy the BST and free all memory
    if (head == NULL) return;                               //base case: if we reach the end of the tree, return
    BSTDestroy(head->left);                                 //recursively destroy the left subtree
    BSTDestroy(head->right);                                //recursively destroy the right subtree
    free(head);                                             //free the current node after destroying its subtrees
}   

void BSTPrintReverse(const NodePtr head) {                  //print the keys in reverse order (largest to smallest) by doing a reverse in-order traversal of the BST
    if (head == NULL) return;                               //base case: if we reach the end of the tree, return
    BSTPrintReverse(head->right);                           //first visit the right subtree to print larger keys first
    printf("%s ", head->key);                               //then print the current node's key               
    BSTPrintReverse(head->left);                            //finally visit the left subtree to print smaller keys last
}

void BSTPrint(const NodePtr head) {                         //print the keys in order (smallest to largest) by doing an in-order traversal of the BST
    if (head == NULL) return;                               //base case: if we reach the end of the tree, return
    BSTPrint(head->left);                                   //first visit the left subtree to print smaller keys first
    printf("%s ", head->key);                               //then print the current node's key        
    BSTPrint(head->right);                                  //finally visit the right subtree to print larger keys last
}

int isBSTUtil(NodePtr node, Key min_key, Key max_key) {                 //utility function to check if the tree is a BST by ensuring that all keys in the left subtree are less than the current node's key, and all keys in the right subtree are greater than the current node's key, while also checking that the keys are within the specified min and max bounds
    if (node == NULL) return 1; //if we reach the end of the tree, return true (base case)
    if (min_key != NULL && (less(node->key, min_key) || equal(node->key, min_key))) return 0;     
    //if the current node's key is less than or equal to the minimum key, return false  
    if (max_key != NULL && (greater(node->key, max_key) || equal(node->key, max_key))) return 0;
    //if the current node's key is greater than or equal to the maximum key, return false
    return isBSTUtil(node->left, min_key, node->key) && isBSTUtil(node->right, node->key, max_key);
    //recursively check the left subtree with the current node's key as the new maximum, and the right subtree with the current node's key as the new minimum, and return true if both subtrees are BSTs
}

int isBST(NodePtr head) {                   //check if the tree is a BST by calling the utility function with no initial bounds
    return isBSTUtil(head, NULL, NULL);     //call the utility function with no initial bounds to check if the tree is a BST
}