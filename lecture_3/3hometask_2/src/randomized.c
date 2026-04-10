#include "randomized.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INITIAL_CAPACITY 8

struct RandomizedQueue {
    Item   *items;      
    size_t  size;       //stored
    size_t  capacity;   //can be stored without resizing
};

static void seed_once(void)
{
    static int seeded = 0;      //static to ensure that we random only once
    if (!seeded) {                  
        srand((unsigned)time(NULL));    
        seeded = 1;
    }
}

static void resize(RandomizedQueuePtr rq, size_t new_cap)       //resize function
{
    Item *new_items = realloc(rq->items, new_cap * sizeof(Item));   
    if (!new_items) {
        fprintf(stderr, "Out of memory\n");
        exit(EXIT_FAILURE);
    }
    rq->items    = new_items;   //to ensure we dont lose pointer to the items if realloc fails
    rq->capacity = new_cap;
}

RandomizedQueuePtr RandomizedQueueInit(void)    //create the queue
{
    seed_once();        //randomize

    struct RandomizedQueue *rq = malloc(sizeof(struct RandomizedQueue));    //allocate memory for the queue
    if (!rq) return NULL;

    rq->items = malloc(INITIAL_CAPACITY * sizeof(Item));        //allocate memory for the items array
    if (!rq->items) { free(rq); return NULL; }                  //if allocation fails, free the queue and return NULL

    rq->size     = 0;                                           //initially the queue is empty, so size is 0
    rq->capacity = INITIAL_CAPACITY;
    return rq;
}

bool RandomizedQueueEmpty(RandomizedQueuePtr rq)    //check if the queue is empty
{
    return rq->size == 0;
}

size_t RandomizedQueueSize(RandomizedQueuePtr rq)   //check size of the queue
{
    return rq->size;
}

void RandomizedQueueEnqueue(RandomizedQueuePtr rq, Item item)   //add item to the queue
{
    if (rq->size == rq->capacity)               //if more than possible
        resize(rq, rq->capacity * 2);           //doublye the capacity

    rq->items[rq->size++] = item;               //add the item to the end of the array and increment size
}

Item RandomizedQueueDequeue(RandomizedQueuePtr rq)
{
    if (RandomizedQueueEmpty(rq)) {     //if the queue is empty, print error and return NULL
        fprintf(stderr, "Empty queue\n");
        return NULL;
    }

    size_t idx  = (size_t)rand() % rq->size;    //random index from 0 to size-1
    Item   item = rq->items[idx];               //save the item

    rq->items[idx] = rq->items[rq->size - 1];   //overwrite with last
    rq->size--;                                 //minus size

    if (rq->size > 0 &&                         //dont shrink to 0 capacity
        rq->size == rq->capacity / 4 &&         //only shrink at 25% capacity to avoid thrashing
        rq->capacity / 2 >= INITIAL_CAPACITY)   //dont go below initial capacity
    {
        resize(rq, rq->capacity / 2);          
    }

    return item;
}

void RandomizedQueueDestroy(RandomizedQueuePtr rq)
{
    free(rq->items);
    free(rq);
}