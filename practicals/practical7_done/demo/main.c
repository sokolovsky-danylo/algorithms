#include "priority_queue.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    char *arr[] = {"S", "O", "R", "T", "E", "X", "A", "M", "P", "L", "E"};
    int n = sizeof(arr) / sizeof(arr[0]);

    generic_heapsort(arr, n, sizeof(char *), compare_strings);

    printf("sorted array: ");
    for (int i = 0; i < n; i++) printf("%s ", arr[i]);
    printf("\n");

    char *expected[] = {"A", "E", "E", "L", "M", "O", "P", "R", "S", "T", "X"};
    for (int i = 0; i < n; i++) assert(strcmp(arr[i], expected[i]) == 0);
    
    printf("heapsort 0-index test passed!\n");
    return 0;
}