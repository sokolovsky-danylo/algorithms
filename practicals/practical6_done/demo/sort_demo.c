#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"

int main() {
    Point pts_raw[] = {{0,0}, {2,0}, {1,1}, {2,2}, {1,3}, {0,2}};
    int n = 6;
    Item pts[6];
    for(int i=0; i<n; i++) pts[i] = &pts_raw[i];

    insertion_sort(pts, n);

    printf("Sorted points:\n");
    for (int i = 0; i < n; i++) {
        printf("(%d, %d)\n", pts[i]->x, pts[i]->y);
    }
    return 0;
}