#ifndef RANDOMIZED_QUEUE_H
#define RANDOMIZED_QUEUE_H

#include <stddef.h>
#include <stdbool.h>

typedef void* Item;

/// Define a pointer type for the RandomizedQueue structure
typedef struct RandomizedQueue* RandomizedQueuePtr;

// Initialize an empty randomized queue
RandomizedQueuePtr RandomizedQueueInit();

// Check if the randomized queue is empty
bool RandomizedQueueEmpty(RandomizedQueuePtr rq);

// Return the number of items in the randomized queue
size_t RandomizedQueueSize(RandomizedQueuePtr rq);

// Add an item to the randomized queue
void RandomizedQueueEnqueue(RandomizedQueuePtr rq, Item item);

// Remove and return a random item from the randomized queue
Item RandomizedQueueDequeue(RandomizedQueuePtr rq);

// Destroy the randomized queue and free memory
void RandomizedQueueDestroy(RandomizedQueuePtr rq);

#endif /* RANDOMIZED_QUEUE_H */