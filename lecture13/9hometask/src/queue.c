#include "queue.h"
#include <stdlib.h>

struct Queue {
    vertex_t *data;     //array to hold the queue elements
    int front;          //index of the front element
    int rear;           //index of the rear element
    int size;           //current size of the queue
    int capacity;       //maximum capacity of the queue
};

Queue* QueueInit(int capacity) {        
    Queue* q = malloc(sizeof(Queue));   //allocate memory for the queue structure
    q->capacity = capacity;             //set the capacity
    q->front = 0;                       //initialize front index    
    q->size = 0;                        //initialize size
    q->rear = capacity - 1;             //rear starts at the end of the array
    q->data = malloc(q->capacity * sizeof(vertex_t));   //allocate memory for the queue data array
    return q;
}

void QueueEnqueue(Queue* q, vertex_t v) {       //add element to the end of the queue
    if (q->size == q->capacity) return;         //if the queue is full, do nothing
    q->rear = (q->rear + 1) % q->capacity;      //move rear index to the next position
    q->data[q->rear] = v;                       //add the new element at the rear
    q->size++;                                  //increment the size of the queue
}

vertex_t QueueDequeue(Queue* q) {               //take element from the front of the queue
    if (q->size == 0) return -1;                //if the queue is empty return -1
    vertex_t item = q->data[q->front];          //store the front element to return
    q->front = (q->front + 1) % q->capacity;    //move front index to the next position
    q->size--;                                  //decrement the size of the queue     
    return item;
}

int QueueIsEmpty(Queue* q) {
    return (q->size == 0);
}

void QueueDestroy(Queue* q) {
    free(q->data);
    free(q);
}