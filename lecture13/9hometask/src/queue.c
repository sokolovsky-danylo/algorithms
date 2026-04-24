#include "queue.h"
#include <stdlib.h>

struct Queue {
    vertex_t *data;
    int front;
    int rear;
    int size;
    int capacity;
};

Queue* QueueInit(int capacity) {
    Queue* q = malloc(sizeof(Queue));
    q->capacity = capacity;
    q->front = 0;
    q->size = 0;
    q->rear = capacity - 1;
    q->data = malloc(q->capacity * sizeof(vertex_t));
    return q;
}

void QueueEnqueue(Queue* q, vertex_t v) {
    if (q->size == q->capacity) return;
    q->rear = (q->rear + 1) % q->capacity;
    q->data[q->rear] = v;
    q->size++;
}

vertex_t QueueDequeue(Queue* q) {
    if (q->size == 0) return -1;
    vertex_t item = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return item;
}

int QueueIsEmpty(Queue* q) {
    return (q->size == 0);
}

void QueueDestroy(Queue* q) {
    free(q->data);
    free(q);
}