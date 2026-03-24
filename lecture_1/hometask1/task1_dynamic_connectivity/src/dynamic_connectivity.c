#include "dynamic_connectivity.h"

void init_dynamic_connectivity(DynamicConnectivity* dc, int n) {
    for (int i = 0; i < n; i++){
        dc->id[i] = i;  //each element initialy refers to itself
        dc->sz[i] = 1;  //initially each tree has size of 1j
    }
}

int root(DynamicConnectivity* dc, int i) {
    while(i!= dc->id[i]){
        dc->id[i]= dc->id[dc->id[i]]; //point to grandparent (halving the path)
        i = dc->id[i];
    }
    return i;
}

bool connected(DynamicConnectivity* dc, int p, int q) {
    return root(dc, p) == root(dc, q);
}

void add_union(DynamicConnectivity* dc, int p, int q) {
    int root_p = root(dc,p);
    int root_q = root(dc,q);

    if (root_p == root_q) return;

    if(dc->sz[root_q] < dc->sz[root_p]) { //if pbranch size is bigger than q
        dc->id[root_p] = root_q;    //p index becomes q index
        dc->sz[root_q] += dc->sz[root_p];    //refresh size info 
    }
    else {
        dc->id[root_q] = root_p;
        dc->sz[root_p] += dc->sz[root_q];
    }

}