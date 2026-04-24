#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "item.h"

typedef struct HashTable *HashTablePtr;

HashTablePtr HashTableInit(int M);
int HashTablePut(HashTablePtr ht, Key key, Item item);
double HashTableGetAverageDisplacement(HashTablePtr ht);
void HashTableDestroy(HashTablePtr ht);

#endif