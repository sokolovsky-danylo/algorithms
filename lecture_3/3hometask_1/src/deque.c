#include "deque.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    Item        item;
    struct Node *prev;  //pointer to the previous node in the deque
    struct Node *next;  //pointer to the next node in the deque
} Node;

struct Deque {
    Node   *head;   //first element
    Node   *tail;   //last element
    size_t  size;   //number of elements  
};

static Node *node_new(Item item)   
{
    Node *n = malloc(sizeof(Node)); //allocate memory for a new node
    if (!n) {
        fprintf(stderr, "Out of memory");
        exit(EXIT_FAILURE);
    }
    n->item = item;                 //store the item in the node
    n->prev = NULL;
    n->next = NULL;
    return n;
}

DequePtr DequeInit(void)
{
    struct Deque *d = malloc(sizeof(struct Deque));     //allocate memory for the deque 
    if (!d) return NULL;

    d->head = NULL;
    d->tail = NULL;
    d->size = 0;
    return d;
}

int DequeEmpty(DequePtr deque)  //check emptyness
{
    return deque->size == 0;
}

size_t DequeSize(DequePtr deque)    //check size
{
    return deque->size;
}

void DequeAddFirst(DequePtr deque, Item item)   //add item to the front of the deque
{
    Node *n = node_new(item);

    if (DequeEmpty(deque)) {        //if deque is empty
        deque->head = n;            //set head and tail to the new node
        deque->tail = n;
    } else {                                //if not empty
        n->next          = deque->head;     //set the next pointer of the new node to the current head
        deque->head->prev = n;
        deque->head       = n;
    }
    deque->size++;
}

void DequeAddLast(DequePtr deque, Item item){       //add item to the back of the deque

    Node *n = node_new(item);

    if (DequeEmpty(deque)) {            //if deque is empty
        deque->head = n;                //set head and tail to the new node
        deque->tail = n;
    } else {                            //if not empty      
        n->prev          = deque->tail; //set the previous pointer of the new node to the current tail
        deque->tail->next = n;
        deque->tail       = n;
    }
    deque->size++;
}

Item DequeRemoveFirst(DequePtr deque) {         //remove from front
    if (DequeEmpty(deque)) {                //if deque is empty, print error and return NULL
        fprintf(stderr, "Deque is empty\n");
        return NULL;
    }

    Node *old  = deque->head;       //store the current head to return the item after deletion
    Item  item = old->item;         //store the item to return after deletion

    deque->head = old->next;            //set the head to the next node in the deque
    if (deque->head)                    //if there is a new head, set its previous pointer to NULL since it's now the first node
        deque->head->prev = NULL;       //if there is no new head, then the deque is now empty, so set tail to NULL as well
    else
        deque->tail = NULL;             //set tail to NULL since the deque is now empty

    free(old);
    deque->size--;
    return item;
}

Item DequeRemoveLast(DequePtr deque) {          //remove from back
    if (DequeEmpty(deque)) {
        fprintf(stderr, "Deque is empty\n");
        return NULL;
    }

    Node *old  = deque->tail;       //store the current tail to return the item after deletion
    Item  item = old->item;         //store the item to return after deletion

    deque->tail = old->prev;        //set the tail to the previous node in the deque
    if (deque->tail)                //if there is a new tail, set its next pointer to NULL since it's now the last node
        deque->tail->next = NULL;   //if there is no new tail, then the deque is now empty, so set head to NULL as well
    else
        deque->head = NULL;         //set head to NULL since the deque is now empty

    free(old);
    deque->size--;
    return item;
}

void DequeDestroy(DequePtr deque) {     //free all memory used by the deque, but not the items themselves since the caller owns item memory
    Node *cur = deque->head;
    while (cur) {
        Node *next = cur->next;
        free(cur);
        cur = next;
    }
    free(deque);
}