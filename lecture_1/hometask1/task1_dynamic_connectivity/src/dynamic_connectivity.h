#ifndef DYNAMIC_CONNECTIVITY_H
#define DYNAMIC_CONNECTIVITY_H

#include <stdbool.h>

#define CAPACITY 100000//1


typedef struct {
    int id[CAPACITY];   
    int sz[CAPACITY];  
} DynamicConnectivity;


void init_dynamic_connectivity(DynamicConnectivity* dc, int n);


int root(DynamicConnectivity* dc, int i);


bool connected(DynamicConnectivity* dc, int p, int q);


void add_union(DynamicConnectivity* dc, int p, int q);

#endif // DYNAMIC_CONNECTIVITY_H
