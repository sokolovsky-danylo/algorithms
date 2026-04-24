#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

bool connected__quick_find(const int* id, int p, int q);
void union__quick_find(int* id, int n, int p, int q);

int root__quick_union(const int* id, int i);
bool connected__quick_union(const int* id, int p, int q);
void union__quick_union(int* id, int p, int q);

void union__weighted_quick_union(int* id, int* sz, int p, int q);
int root__quick_union_path_compression(int* id, int i);

#ifdef __cplusplus
}
#endif

#endif // UNION_FIND_H