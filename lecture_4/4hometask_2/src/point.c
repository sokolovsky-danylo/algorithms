#include "point.h"

#include <stdlib.h>
#include <math.h>   

PointPtr create_point(int x, int y) {                       //function to create a new point with given coordinates
    PointPtr p = (PointPtr)malloc(sizeof(Point));           //allocate memory for a new Point structure and return a pointer to it
    p->x = x;                                               //set the x and y coordinates of the point to the provided values
    p->y = y;
    return p;                                               //return the pointer to the created Point structure
}

void destroy_point(PointPtr p) {                //function to destroy a point and free the allocated memory 
    free(p);                                   
}

int compare_points(const void *a, const void *b) {  //natural order: compare by y-coordinate, then x-coordinate if y's are equal
    PointPtr pa = *(PointPtr *)a; //treat the void pointers as pointers to PointPtr and save the values they point to in pa and pb
    PointPtr pb = *(PointPtr *)b;                      
    if (pa->y != pb->y)                             //compare by y-coordinate first
        return (pa->y > pb->y) - (pa->y < pb->y);   //returns -1 if pa->y < pb->y, 0 if pa->y == pb->y, and 1 if pa->y > pb->y
    return (pa->x > pb->x) - (pa->x < pb->x);       //if y's are equal, compare by x-coordinate and return -1, 0, or 1 accordingly
}

double slope_to(PointPtr p1, PointPtr p2) {         //function to compute the slope between two points
    int dx = p2->x - p1->x;                         //calculate the difference in x and y coordinates between the two points
    int dy = p2->y - p1->y;                         

    if (dx == 0 && dy == 0) return -INFINITY;  //if both points are the same, return -infinity
    if (dx == 0)             return +INFINITY;   //if the line is vertical, return +infinity (vertical line) x is same
    if (dy == 0)             return +0.0;       //if the line is horizontal, return +0 (horizontal line) y is same

    return (double)dy / (double)dx;             //use double for precision in slope
}

static PointPtr slope_ref = NULL;

int compare_by_slope(const void *a, const void *b) {    //function to compare two points by the slope they make with a reference point
    PointPtr pa = *(PointPtr *)a;           
    PointPtr pb = *(PointPtr *)b;
    double sa = slope_to(slope_ref, pa);                       //compare the slopes and return -1, 0, or 1 accordingly
    double sb = slope_to(slope_ref, pb);                       
    if (sa < sb) return -1;                                    //if slope to pa is less than slope to pb, return -1
    if (sa > sb) return 1;                                     //if slope to pa is greater than slope to pb, return 1                     
    return 0;                                                  //if slopes are equal, return 0
}

// sets the origin point for slope comparison
void set_slope_reference(PointPtr ref) {
    slope_ref = ref;
}