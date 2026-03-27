#include <stdio.h>
#include "convex_hull.h"

static void print_points(const char *label, Point pts[], int n) {   //helper function to print points with a label
    printf("%s\n", label);                                          //print the label first
    for (int i = 0; i < n; i++)                                     //loop through points and print each one
        printf("(%d, %d)\n", pts[i].x, pts[i].y);                   //print the coordinates of each point
}

int main(void) {
    Point points[] = {                                              //hardcode test from task
        {0, 0}, {2, 0}, {1, 1}, {2, 2}, {1, 3}, {0, 2}
    };
    int n = (int)(sizeof(points) / sizeof(points[0]));              //calculate length of the points array

    print_points("Points:", points, n);                             //show initial data

    Point hull[6];                                                  //array to store points in the convex hull, max size is n   
    int hull_size = 0;                                   //variable to store the number of points in the hull after we compute it
    convexHull(points, n, hull, &hull_size);                        //call the convex hull function to compute the hull points and store the result in hull array and hull_size variable

    printf("\nConvex Hull:\n");                                     //print the points in the convex hull
    for (int i = 0; i < hull_size; i++)                             //loop through the points in the hull and print each one
        printf("(%d, %d)\n", hull[i].x, hull[i].y);

    return 0;
}
