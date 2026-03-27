#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "sort.h"

int compare_int_ascending(const void *a, const void *b) {      //comparator function for integers in ascending order
    int x = *(const int *)a;               //treat the void pointers as pointers to int and save the values they point to in x and y
    int y = *(const int *)b;
    return (x > y) - (x < y);               //returns -1 if x < y, 0 if x == y, and 1 if x > y
}


typedef void (*SortFn)(void *, int, size_t,                       
                       int (*)(const void *, const void *));    //type definition 


static double measure_ms(SortFn fn, const int *src, int N) {    //function to measure the time without modifying the original array
    int *copy = malloc((size_t)N * sizeof(int));       //allocate memory for a copy of the original array
    if (!copy) {                                       //if memory allocation fails, return -1.0 to indicate an error
        return -1.0;
    }
    memcpy(copy, src, (size_t)N * sizeof(int));         //copy the original array into the newly allocated memory

    clock_t start = clock();                            //record the start time before sorting
    fn(copy, N, sizeof(int), compare_int_ascending);    //call the sorting function on the copy of the array
    clock_t end = clock();                              //record the end time after sorting

    free(copy);                                          //free the allocated memory for the copy of the array
    return (double)(end - start) / CLOCKS_PER_SEC * 1000.0;     //calculate elapsed time in milliseconds
}


static void print_row(const char *name, SortFn fn,  
                      int *arrays[], const int sizes[], int num_sizes) {        //prints one row of results  
    printf("%-18s", name);          //algorithm name  
    for (int s = 0; s < num_sizes; s++) {    //go through all the sizes and print the time for each size 
        double ms = measure_ms(fn, arrays[s], sizes[s]);    //run the timer
        printf(" %10.3f", ms);          //print the time in milliseconds with 3 decimal places
    }
    printf("\n");
}

int main(void) {
    srand(17);      //seed the random number generator for reproducibility

    const int sizes[]  = {100, 1000, 10000, 100000};    //array of sizes to test
    const int NUM      = (int)(sizeof(sizes) / sizeof(sizes[0]));       //number of sizes to test, calculated from the sizes array

    const char *names[] = {"insertion_sort", "selection_sort", "shell_sort"};   //array of algorithm names for printing results
    SortFn      fns[]   = { insertion_sort,   selection_sort,   shell_sort };   //array of function pointers corresponding to the sorting algorithms

    int *rand_arrays[4];    //array of pointers to hold the random arrays for each size
    for (int s = 0; s < NUM; s++) {         //allocate memory for each random array and fill it with random integers
        rand_arrays[s] = malloc((size_t)sizes[s] * sizeof(int));        //allocate memory for the random array of the current size
        for (int i = 0; i < sizes[s]; i++)          //fill the array with random integers between 0 and 999999
            rand_arrays[s][i] = rand() % 1000000;           //generate a random integer and assign it to the current position in the array
    }

    int *sorted_arrays[4];                                         //array of pointers to hold the already sorted arrays for each size     
    for (int s = 0; s < NUM; s++) {                                 //allocate memory for each sorted array and fill it with sorted integers
        sorted_arrays[s] = malloc((size_t)sizes[s] * sizeof(int));  //allocate memory for the sorted array of the current size
        for (int i = 0; i < sizes[s]; i++)                          //fill the array with sorted integers from 0 to sizes[s]-1
            sorted_arrays[s][i] = i;                                //assign the value of i to the current position in the array, creating a sorted array
    }

    printf("Random input (ms)\n");
    printf("%-18s %10s %10s %10s %10s\n", "Algorithm", "N=100", "N=1000", "N=10000", "N=100000");
    printf("-----------------------------------------------------------\n");

    for (int f = 0; f < 3; f++)                             //go through each sorting algorithm and print the results for random input
        print_row(names[f], fns[f], rand_arrays, sizes, NUM);   //print the results for the current sorting algorithm using the random arrays

    printf("\nAlready-sorted input (ms)\n");
    printf("%-18s %10s %10s %10s %10s\n", "Algorithm", "N=100", "N=1000", "N=10000", "N=100000");
    printf("-----------------------------------------------------------\n");

    for (int f = 0; f < 3; f++)
        print_row(names[f], fns[f], sorted_arrays, sizes, NUM); 

    for (int s = 0; s < NUM; s++) {     //free the allocated memory for the random and sorted arrays
        free(rand_arrays[s]);
        free(sorted_arrays[s]);
    }

    return 0;
}