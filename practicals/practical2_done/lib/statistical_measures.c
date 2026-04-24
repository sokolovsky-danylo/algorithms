#include "statistical_measures.h"
#include <math.h>

double mean(double* experiments, int n) {
    if (n <= 0) return 0.0;
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += experiments[i];
    }
    return sum / n;
}

double stddev(double* experiments, int n) {
    if (n <= 1) return 0.0;
    double avg = mean(experiments, n);
    double sum_sq_diff = 0.0;
    for (int i = 0; i < n; i++) {
        sum_sq_diff += pow(experiments[i] - avg, 2);
    }
    return sqrt(sum_sq_diff / (n - 1));
}

void confidence_interval(double* experiments, int n, double* ci) {
    if (n <= 0) return;
    double avg = mean(experiments, n);
    double s = stddev(experiments, n);
    double margin = (1.96 * s) / sqrt(n);
    ci[0] = avg - margin;
    ci[1] = avg + margin;
}