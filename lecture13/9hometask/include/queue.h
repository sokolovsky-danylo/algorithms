#ifndef QUEUE_H
#define QUEUE_H

#include "graph.h"

typedef struct Queue Queue;

Queue* QueueInit(int capacity);
void QueueEnqueue(Queue* q, vertex_t v);
vertex_t QueueDequeue(Queue* q);
int QueueIsEmpty(Queue* q);
void QueueDestroy(Queue* q);

#endif