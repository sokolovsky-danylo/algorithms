#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stddef.h>
#include "item.h"

typedef struct PriorityQueue *PriorityQueuePtr;

PriorityQueuePtr PQInit(int capacity);
void PQInsert(PriorityQueuePtr pq, Item item);
Item PQDelMax(PriorityQueuePtr pq);
int PQIsEmpty(PriorityQueuePtr pq);
void PQDestroy(PriorityQueuePtr pq);

void generic_heapsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));

#endif