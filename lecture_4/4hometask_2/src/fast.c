#include <stdio.h>
#include <stdlib.h>
#include "point.h"

//complexity: O(N^2 log N) because of the two nested loops and the sorting step inside the outer loop.

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 1;                        //read the number of points from standard input and store it in n. if the input is not a valid integer, return 1 to indicate an error.

    PointPtr *points = malloc(n * sizeof(PointPtr));           //allocate memory for an array of PointPtr to hold the points
    PointPtr *others = malloc((n - 1) * sizeof(PointPtr));     //allocate memory for an array of PointPtr to hold the other points

    for (int i = 0; i < n; i++) {                              //loop to read the coordinates of each point from standard input
        int x, y;
        scanf("%d %d", &x, &y);
        points[i] = create_point(x, y);                        //create a new point using the create_point function and store the pointer in the points array
    }

    for (int i = 0; i < n; i++) {                               //loop through each point as a reference point i
        set_slope_reference(points[i]);                               //set the current point as the reference point for slope comparison
        int count = 0;                                   
        for (int j = 0; j < n; j++) {
            if (i != j) others[count++] = points[j];        //if the current point j is not the reference point i, add it to the others array and increment the count
        }

        qsort(others, n - 1, sizeof(PointPtr), compare_by_slope);       //sort the other points based on the slope they make with the reference point using the qsort function and the compare_by_slope comparator

        for (int j = 0; j < n - 2; ) {              //loop through the sorted other points to find groups of points with the same slope to the reference point
            int k = j + 1;                          //initialize k to the next index after j
            double slope1 = slope_to(points[i], others[j]);                   //calculate the slope from the reference point to the current point at index j and store it in slope1
            while (k < n - 1 && slope_to(points[i], others[k]) == slope1) {     //while the slope from the reference point to the point at index k is equal to slope1, increment k to find all points with the same slope
                k++;           
            }

            if (k - j >= 3) {     //if k - j is greater than or equal to 3,
            //it means we have found at least 3 points that are collinear with the reference point

                printf("(%d, %d)", points[i]->x, points[i]->y); //print the reference point in the specified format
                for (int m = j; m < k; m++) {          
                    printf(" -> (%d, %d)", others[m]->x, others[m]->y);
                }
                printf("\n");
            }
            j = k;
        }
    }

    for (int i = 0; i < n; i++) destroy_point(points[i]);   //free the memory allocated for each point
    free(points);
    free(others);
    return 0;
}