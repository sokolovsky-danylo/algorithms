#include "union_find.h"

bool connected__quick_find(const int* id, int p, int q) {
    return id[p] == id[q];
}

void union__quick_find(int* id, int n, int p, int q) {
    int pid = id[p];
    int qid = id[q];
    for (int i = 0; i < n; i++) {
        if (id[i] == pid) {
            id[i] = qid;
        }
    }
}

int root__quick_union(const int* id, int i) {
    while (i != id[i]) {
        i = id[i];
    }
    return i;
}

bool connected__quick_union(const int* id, int p, int q) {
    return root__quick_union(id, p) == root__quick_union(id, q);
}

void union__quick_union(int* id, int p, int q) {
    int root_p = root__quick_union(id, p);
    int root_q = root__quick_union(id, q);
    id[root_p] = root_q;
}

void union__weighted_quick_union(int* id, int* sz, int p, int q) {
    int root_p = root__quick_union(id, p);
    int root_q = root__quick_union(id, q);
    if (root_p == root_q) return;
    
    if (sz[root_p] < sz[root_q]) {
        id[root_p] = root_q;
        sz[root_q] += sz[root_p];
    } else {
        id[root_q] = root_p;
        sz[root_p] += sz[root_q];
    }
}

int root__quick_union_path_compression(int* id, int i) {
    while (i != id[i]) {
        id[i] = id[id[i]];
        i = id[i];
    }
    return i;
}