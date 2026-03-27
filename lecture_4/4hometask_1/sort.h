#ifndef SORT_H
#define SORT_H

#include <stddef.h>


void exch(void *a, void *b, size_t size); //function to swap to elements of any byte size
/*arr - pointer to the first element of the array
N - number of elements
size - size of each element in bytes
cmp - comparator function*/


void insertion_sort(void *arr, int N, size_t size,
                    int (*cmp)(const void *, const void *));    //insertion sort function
/*arr - pointer to the first element of the array
N - number of elements
size - size of each element in bytes
cmp - comparator function*/


void selection_sort(void *arr, int N, size_t size,
                    int (*cmp)(const void *, const void *));    //selection sort function
/*arr - pointer to the first element of the array
N - number of elements
size - size of each element in bytes
cmp - comparator function*/


void shell_sort(void *arr, int N, size_t size,
                int (*cmp)(const void *, const void *));        //shell sort function
/*arr - pointer to the first element of the array
N - number of elements
size - size of each element in bytes
cmp - comparator function*/


#endif /* SORT_H */