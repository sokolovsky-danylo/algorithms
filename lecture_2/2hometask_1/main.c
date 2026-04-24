#include <stdio.h>
#include <stdlib.h> 
#include "PercolationStats.h"

//gcc -o percolation_simulation percolationStats.c PercolationStats.c percolation.c -lm
// values[0] = "./percolation_simulation"
// values[1] = "200"
// values[2] = "100"
int main(int count, char* values[]) {

    if (count != 3) {       //we need 3 elements, program, n and t
        printf("Usage: %s <grid_size> <experiments>\n", values[0]);
        return 1; // Возвращаем код ошибки
    }

    // turn text to value
    int n = atoi(values[1]); //size
    int t = atoi(values[2]); //experiments

    //allocate memmory for our structure
    PercolationStats* ps = create_percolation_stats(n, t);

    //start simulation
    run_experiments(ps);

    //print results
    print_statistics(ps);

    //clean memmory
    destroy_percolation_stats(ps);

    return 0; 
}