#include "priority_queue.h"
#include <string.h>

static void swap(char *a, char *b, size_t size) {
    char tmp;
    while (size--) { tmp = *a; *a++ = *b; *b++ = tmp; }
}

static void generic_sink(char *base, int k, int n, size_t size, int (*compar)(const void *, const void *)) {
    while (2*k + 1 < n) {
        int j = 2*k + 1;
        if (j + 1 < n && compar(base + j*size, base + (j+1)*size) < 0) j++;
        if (compar(base + k*size, base + j*size) >= 0) break;
        swap(base + k*size, base + j*size, size);
        k = j;
    }
}

void generic_heapsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *)) {
    if (nmemb < 2) return;
    int n = (int)nmemb;
    char *b = (char *)base;

    for (int k = n/2 - 1; k >= 0; k--)
        generic_sink(b, k, n, size, compar);

    while (n > 1) {
        swap(b, b + (n-1)*size, size);
        generic_sink(b, 0, --n, size, compar);
    }
}