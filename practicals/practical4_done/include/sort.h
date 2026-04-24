#ifndef SORT_H
#define SORT_H

#include <stddef.h>

void shell_sort(void *arr, int N, size_t size, int (*cmp)(const void *, const void *));
void exch(void *a, void *b, size_t size);

#endif