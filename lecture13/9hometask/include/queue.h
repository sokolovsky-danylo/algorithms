#ifndef QUEUE_H
#define QUEUE_H

#include "graph.h"

typedef struct Queue Queue; //structure declaration

Queue* QueueInit(int capacity);     //initialization of the queue with given capacity

void QueueEnqueue(Queue* q, vertex_t v);    //add element to the end
vertex_t QueueDequeue(Queue* q);            //take element from the front
int QueueIsEmpty(Queue* q);                 //check if the queue is empty
void QueueDestroy(Queue* q);                //free memory allocated for the queue

#endif