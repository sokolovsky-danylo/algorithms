#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void run_simulation(int M, int target_N) {
    HashTablePtr ht = HashTableInit(M);
    for (int i = 0; i < target_N; i++) {
        Key preferred_spot = rand() % M;
        HashTablePut(ht, preferred_spot, NULL);
    }
    
    double avg = HashTableGetAverageDisplacement(ht);
    printf("m = %d, cars = %d (%.1f%%)\n", M, target_N, (double)target_N/M*100);
    printf("result average: %.4f\n", avg);
    
    if (target_N == M / 2) {
        printf("theory (half-full): ~1.5\n");
    } else if (target_N == M) {
        double theory = sqrt(M * M_PI / 8.0);
        printf("theory (full): sqrt(PI * M / 8) = %.4f\n", theory);
    }
    printf("--------------------------------------\n");
    
    HashTableDestroy(ht);
}

int main() {
    srand(time(NULL));
    int M = 4000; // Достатньо велике значення для точності
    
    printf("Knuth's Parking Problem Simulation\n\n");
    
    // Тест 1: Напівзаповнена вулиця
    run_simulation(M, M / 2);
    
    // Тест 2: Повна вулиця
    run_simulation(M, M);
    
    return 0;
}