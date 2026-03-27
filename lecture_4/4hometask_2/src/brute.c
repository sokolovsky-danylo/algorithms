#include <stdio.h>
#include <stdlib.h>
#include "point.h"


//complexity: O(N^4) because of the four nested loops in main.

int main() {
    int n; 
    if (scanf("%d", &n) != 1) return 1;          //read the number of points from standard input and store it in n. 
//if the input is not a valid integer, return 1 to indicate an error.         

    PointPtr *points = malloc(n * sizeof(PointPtr));      //allocate memory for an array of PointPtr to hold the points
    for (int i = 0; i < n; i++) {                       //loop to read the coordinates of each point from standard input
        int x, y;                                       //declare variables to hold the x and y coordinates of the point
        scanf("%d %d", &x, &y);                        //read the x and y coordinates from standard input
        points[i] = create_point(x, y);             //create a new point using the create_point function and store the pointer in the points array
    }


    qsort(points, n, sizeof(PointPtr), compare_points);             //sort the points in natural order. this ensures that we process points from bottom-to-top, left-to-right, which is important for consistent output and to avoid duplicates.
    for (int i = 0; i < n; i++) {                                   //loop through each point as a reference point i
        for (int j = i + 1; j < n; j++) {                           //loop for point j, ensuring j is different from i
            for (int k = j + 1; k < n; k++) {                       //loop for point k, ensuring k is different from i and j
                for (int m = k + 1; m < n; m++) {                   //loop for point m, ensuring m is different from i, j, and k
                    double s1 = slope_to(points[i], points[j]);     //calculate the slope between points i and j 
                    double s2 = slope_to(points[i], points[k]);     //calculate the slope between points i and k 
                    double s3 = slope_to(points[i], points[m]);     //calculate the slope between points i and m 

                    if (s1 == s2 && s1 == s3) {                     //if the slopes s1, s2, and s3 are all equal, it means that points i, j, k, and m are collinear.
                        printf("(%d, %d) -> (%d, %d) -> (%d, %d) -> (%d, %d)\n",    //print the collinear points in the specified format
                               points[i]->x, points[i]->y, points[j]->x, points[j]->y,    
                               points[k]->x, points[k]->y, points[m]->x, points[m]->y);
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++) destroy_point(points[i]);   //free the memory allocated for each point
    free(points);
    return 0;
}