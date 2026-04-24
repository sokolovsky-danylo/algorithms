#include "hash_table.h"
#include "hash_code.h"
#include <stdlib.h>

struct HashTable {
    Key *keys;
    Item *items;
    bool *occupied;
    int M;
    int N;
    long long total_displacement;
};

HashTablePtr HashTableInit(int M) {
    HashTablePtr ht = malloc(sizeof(struct HashTable));
    ht->M = M;
    ht->N = 0;
    ht->total_displacement = 0;
    ht->keys = malloc(M * sizeof(Key));
    ht->items = malloc(M * sizeof(Item));
    ht->occupied = calloc(M, sizeof(bool));
    return ht;
}

int HashTablePut(HashTablePtr ht, Key key, Item item) {
    int h = (hashCodeInt(key) & 0x7FFFFFFF) % ht->M;
    int displacement = 0;
    
    int i = h;
    while (ht->occupied[i]) {
        i = (i + 1) % ht->M;
        displacement++;
        if (displacement >= ht->M) return -1;
    }
    
    ht->keys[i] = key;
    ht->items[i] = item;
    ht->occupied[i] = true;
    ht->N++;
    ht->total_displacement += displacement;
    
    return displacement;
}

double HashTableGetAverageDisplacement(HashTablePtr ht) {
    if (ht->N == 0) return 0;
    return (double)ht->total_displacement / ht->N;
}

void HashTableDestroy(HashTablePtr ht) {
    free(ht->keys);
    free(ht->items);
    free(ht->occupied);
    free(ht);
}