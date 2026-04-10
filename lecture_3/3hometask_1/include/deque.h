#ifndef DEQUE_H
#define DEQUE_H

#include <stddef.h>

typedef void* Item;

typedef struct Deque* DequePtr;

DequePtr DequeInit(void);

int DequeEmpty(DequePtr deque);

size_t DequeSize(DequePtr deque);

void DequeAddFirst(DequePtr deque, Item item);

void DequeAddLast(DequePtr deque, Item item);

Item DequeRemoveFirst(DequePtr deque);

Item DequeRemoveLast(DequePtr deque);

void DequeDestroy(DequePtr deque);

#endif /* DEQUE_H */