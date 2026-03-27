#include "sort.h"
#include <string.h>
#include <stdlib.h>

#define ELEM(arr, i, size) ((char *)(arr) + (size_t)(i) * (size))
//macro to calculate memory adress of i-th element  

void exch(void *a, void *b, size_t size) {  //swap function
    char tmp[size];                         //buffer to hold one element during swap
    memcpy(tmp, a,   size);                 //copy a to tmp
    memcpy(a,   b,   size);                 //copy b to a
    memcpy(b,   tmp, size);                 //copy tmp (original a) to b
}

void insertion_sort(void *arr, int N, size_t size,
                    int (*cmp)(const void *, const void *)) {
    for (int i = 1; i < N; i++) {                                       //cycle starts from 1 because we compare with previous element
        for (int j = i; j > 0; j--) {                                   //look at the left elements  
            if (cmp(ELEM(arr, j, size), ELEM(arr, j - 1, size)) < 0) {  //if current element is less than the previous one
                exch(ELEM(arr, j, size), ELEM(arr, j - 1, size), size); //swap current and previous element
            } else {                                                    //if current element is greater or equal to the previous one
                break;                                                  //stop inner loop and move to the next element in the outer loop
            }
        }
    }
}

void selection_sort(void *arr, int N, size_t size,
                    int (*cmp)(const void *, const void *)) {
    for (int i = 0; i < N - 1; i++) {                                    //cycle through all elements except the last one
        int min = i;                                                     //assume first element is the minimum
        for (int j = i + 1; j < N; j++) {                                //look at the right elements        
            if (cmp(ELEM(arr, j, size), ELEM(arr, min, size)) < 0) {     //if current element is less than the minimum found so far
                min = j;                                                 //update minimum index
            }
        }
        if (min != i) {                                                  //if minimum index is different from the current index  
            exch(ELEM(arr, i, size), ELEM(arr, min, size), size);        //swap current element with the minimum element found
        }
    }
}

void shell_sort(void *arr, int N, size_t size,
                int (*cmp)(const void *, const void *)) {
    int h = 1;                                                            //initial gap size
    while (h < N / 3) {                                                   //calculate the maximum gap size using Knuth's sequence
        h = 3 * h + 1;                                                    //update gap size to the next value in the sequence
    }

    while (h >= 1) {                                                       //while gap size is greater than or equal to 1
        for (int i = h; i < N; i++) {                                      //cycle through elements starting from index h
            for (int j = i; j >= h; j -= h) {                                   //look at the elements that are h positions apart
                if (cmp(ELEM(arr, j, size), ELEM(arr, j - h, size)) < 0) {      //if current element is less than the element h positions before it
                    exch(ELEM(arr, j, size), ELEM(arr, j - h, size), size);     //swap current element with the element h positions before it
                } else {
                    break;
                }
            }
        }
        h = h / 3;                                                          //reduce gap size to the next value in the sequence     
    }
}