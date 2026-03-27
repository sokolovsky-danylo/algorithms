#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

typedef struct {
    int x;
    int y;
} Point;

double getAngle(Point p0, Point p); //function calculates angle between starting point p0 and some p


int ccw(Point a, Point b, Point c);     //function to check left turn, right turn, or collinear


int compare_points(const void *a, const void *b);   //function to sort points by y-coordinate, and by x-coordinate if y's are equal

int compare_by_polar_angle(const void *a, const void *b);   //function to sort points by polar angle with respect to p0_anchor, and by distance if angles are equal



void quicksort_points(Point arr[], int n);      //function to sort points using quicksort algorithm

                     
void mergesort_points(Point arr[], int n);      //function to sort points using mergesort algorithm


void convexHull(Point points[], int n, Point hull[], int *hull_size);       //main function

#endif 
