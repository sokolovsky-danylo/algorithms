#include "priority_queue.h"
#include <stdlib.h>
#include <assert.h>

struct PriorityQueue {
    Item *items;
    int size;
    int capacity;
};

PriorityQueuePtr PQInit(int capacity) {
    PriorityQueuePtr pq = malloc(sizeof(struct PriorityQueue));
    pq->items = malloc(capacity * sizeof(Item));
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

static void swim(Item *a, int k) {
    while (k > 0 && less(a[(k-1)/2], a[k])) {
        exch(a[k], a[(k-1)/2]);
        k = (k-1)/2;
    }
}

static void sink(Item *a, int k, int n) {
    while (2*k + 1 < n) {
        int j = 2*k + 1;
        if (j + 1 < n && less(a[j], a[j+1])) j++;
        if (!less(a[k], a[j])) break;
        exch(a[k], a[j]);
        k = j;
    }
}

void PQInsert(PriorityQueuePtr pq, Item item) {
    assert(pq->size < pq->capacity);
    pq->items[pq->size] = item;
    swim(pq->items, pq->size++);
}

Item PQDelMax(PriorityQueuePtr pq) {
    if (pq->size == 0) return NULL;
    Item max = pq->items[0];
    exch(pq->items[0], pq->items[--pq->size]);
    sink(pq->items, 0, pq->size);
    return max;
}

int PQIsEmpty(PriorityQueuePtr pq) { return pq->size == 0; }
void PQDestroy(PriorityQueuePtr pq) { free(pq->items); free(pq); }