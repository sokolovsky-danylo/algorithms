#include "sort.h"
#include <string.h>

#define ELEM(arr, i, size) ((char *)(arr) + (size_t)(i) * (size))

void exch(void *a, void *b, size_t size) {
    char tmp[size];
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
}

void shell_sort(void *arr, int N, size_t size, int (*cmp)(const void *, const void *)) {
    int h = 1;
    while (h < N / 3) h = 3 * h + 1;

    while (h >= 1) {
        for (int i = h; i < N; i++) {
            for (int j = i; j >= h; j -= h) {
                if (cmp(ELEM(arr, j, size), ELEM(arr, j - h, size)) < 0) {
                    exch(ELEM(arr, j, size), ELEM(arr, j - h, size), size);
                } else {
                    break;
                }
            }
        }
        h /= 3;
    }
}