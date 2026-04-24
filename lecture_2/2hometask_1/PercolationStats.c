#include "PercolationStats.h" 
#include "percolation.h"      
#include <stdio.h>            
#include <stdlib.h>           
#include <math.h>             
#include <time.h>

PercolationStats* create_percolation_stats(int grid_size, int experiments) {
    PercolationStats* ps = (PercolationStats*)malloc(sizeof(PercolationStats)); //allocate memmory for structure
    ps->n = grid_size; //save size
    ps->T = experiments; //save number of experiments

    ps->thresholds = (double*)malloc(experiments * sizeof(double)); //allocate memory for results

    return ps;
}

void destroy_percolation_stats(PercolationStats* ps){
    if (ps != NULL) {   //programm may crash if freeing the 
        if (ps->thresholds != NULL) {
            free(ps->thresholds);
        }
        free(ps);   
    }   
}   

double mean_percolation_threshold(PercolationStats* ps) {
    double sum = 0.0;
    for (int i = 0; i < ps->T; i++) {   //sum all results
        sum += ps->thresholds[i];
    }

    return sum / ps->T; //devide by experiments
}


double stddev_percolation_threshold(PercolationStats* ps) {
    if (ps->T <= 1) return 0.0;

    double mean = mean_percolation_threshold(ps);
    double sum_diff = 0.0;

    for (int i = 0; i < ps->T; i++) {
        sum_diff += pow(ps->thresholds[i] - mean, 2);
    }

    return sqrt(sum_diff / (ps->T - 1));


}

void run_experiments(PercolationStats* ps) {
    srand(time(NULL));
    for (int t = 0; t < ps->T; t++) {   //cycle by quantity of experiments
        Percolation* pc = create_percolation(ps->n);    //create mesh
        while (!percolates(pc)) {   //run until percolates
            int i = rand() % ps->n;     
            int j = rand() % ps->n;
            if (!is_opened(pc, i, j)) {
                open_coordinate(pc, i, j);  //if unopened - open
            }
        }
    double opened = (double)get_opened_count(pc);   //write down how many opened we have
    double total = (double)(ps->n * ps->n);         //write down how many at all
    ps->thresholds[t] = opened / total;

    destroy_percolation(pc);
    }
} 

void print_statistics(PercolationStats* ps) {
    double mean = mean_percolation_threshold(ps);
    double stddev = stddev_percolation_threshold(ps);
    double confidence_err = (1.96 * stddev) / sqrt(ps->T);
    
    printf("Mean percolation threshold: %.10f\n", mean); //середній поріг
    printf("Standard deviation: %.10f\n", stddev);  //стандартне відхилення
    printf("95%% confidence interval: [%.10f, %.10f]\n", mean - confidence_err, mean + confidence_err);
}
