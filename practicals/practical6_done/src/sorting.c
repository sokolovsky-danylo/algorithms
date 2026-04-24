#include "sorting.h"
#include "item.h"
#include <stdlib.h>

int compare_items(Item a, Item b) {
    if (a->y != b->y) return a->y - b->y;
    return a->x - b->x;
}

void insertion_sort(Item arr[], int n) {
    for (int i = 1; i < n; i++) {
        Item key = arr[i];
        int j = i - 1;
        while (j >= 0 && compare_items(arr[j], key) > 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}