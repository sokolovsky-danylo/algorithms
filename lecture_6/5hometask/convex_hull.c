#include "convex_hull.h"

#include <math.h>   //for atan2
#include <stdlib.h> //for malloc, free, rand
#include <string.h>   //for memcpy


static Point p0_anchor; //global variable


double getAngle(Point p0, Point p) {        //function calculates angle between starting point p0 and some p
    return atan2((double)(p.y - p0.y), (double)(p.x - p0.x));   
    //calculates the direction from p0 to p by measuring how far up and how 
    //far right p is, then converting that into angle.
}

int ccw(Point a, Point b, Point c) {      //function takes 3 points and determins the turn direction 
    long long area2 = (long long)(b.x - a.x) * (c.y - a.y)         //long long to prevent int overflow
                    - (long long)(b.y - a.y) * (c.x - a.x);
    if (area2 < 0) return -1;   //negative area - clockwise turn
    if (area2 > 0) return  1;   //positive area - counterclockwise turn
    return 0;                   //zero - collinear
}


int compare_points(const void *a, const void *b) {      //function to sort points by y-coordinate, and by x-coordinate if y's are equal
    const Point *pa = (const Point *)a;
    const Point *pb = (const Point *)b;
    if (pa->y != pb->y) {
        return pa->y - pb->y;           //sort by y-coordinate
    }
    return pa->x - pb->x;                               //if y's are equal, sort by x-coordinate
}

int compare_by_polar_angle(const void *a, const void *b) {      //compare point by angle to p0_anchor
    const Point *pa = (const Point *)a;
    const Point *pb = (const Point *)b;

    double angleA = getAngle(p0_anchor, *pa);                   //calculate angle from p0_anchor to pa
    double angleB = getAngle(p0_anchor, *pb);                   //calculate angle from p0_anchor to pb

    if (angleA < angleB) return -1;                             //if angleA is smaller, pa should come first
    if (angleA > angleB) return  1;                             //if angleB is smaller, pb should come first    


    long long dxA = pa->x - p0_anchor.x, dyA = pa->y - p0_anchor.y;     // distance x and y for A
    long long dxB = pb->x - p0_anchor.x, dyB = pb->y - p0_anchor.y;     // distance x and y for B
    long long distA = dxA * dxA + dyA * dyA;                        // compare squared distances to p0_anchor to break ties (closer point comes first)
    long long distB = dxB * dxB + dyB * dyB;                        //square distance for B

    if (distA < distB) return -1;                                   //if angles are equal, closer point should come first
    if (distA > distB) return  1;                                   //further point should come later
    return 0;                                                       //if angles and distances are equal return 0
}


static void swap_points(Point *a, Point *b) {               //point swap function
    Point tmp = *a;
    *a = *b;
    *b = tmp;
}


static void shuffle(Point arr[], int n) {               //random shuffle the array
    for (int i = n - 1; i > 0; i--) {           
        int j = rand() % (i + 1);                   
        swap_points(&arr[i], &arr[j]);
    }
}

static int median_of_3(Point arr[], int lo, int mid, int hi) {          //find median for pivot
    int ab = compare_points(&arr[lo],  &arr[mid]);      //compare low and mid
    int bc = compare_points(&arr[mid], &arr[hi]);       //compare mid and high
    int ac = compare_points(&arr[lo],  &arr[hi]);       //compare low and high


    if ((ab <= 0 && bc <= 0) || (bc >= 0 && ab >= 0)) return mid;       //mid is median if it's between lo and hi
    if ((ac <= 0 && ab >= 0) || (ab <= 0 && ac >= 0)) return lo;        //lo is median if it's between mid and hi
    return hi;                                                          //hi is median if it's between lo and mid
}               

static int partition_qs(Point arr[], int lo, int hi) {                  //partition function for quicksort
    int i = lo, j = hi + 1;                                             //i starts from left and j starts from right
    Point pivot = arr[lo];                                             //pivot is the first element

    while (1) {                                                         //infinite loop until we break
        while (compare_points(&arr[++i], &pivot) < 0)                   //move i right until we find an element greater than or equal to pivot
            if (i == hi) break;                                        //if we reach the end, break
        while (compare_points(&pivot, &arr[--j]) < 0)                   //move j left until we find an element less than or equal to pivot/
            if (j == lo) break;                                         //if we reach the beginning, break  
        if (i >= j) break;                                              //if i and j cross, break                   
        swap_points(&arr[i], &arr[j]);                                  //swap elements at i and j
    }
    swap_points(&arr[lo], &arr[j]);                             //swap pivot with element at j, so pivot is in its final position
    return j;                                                   //return index of pivot after partitioning
}

#define QS_CUTOFF 10                                                //cutoff for insertion sort in quicksort

static void insertion_sort_range(Point arr[], int lo, int hi) {     //insertion sort for small subarrays in quicksort
    for (int i = lo + 1; i <= hi; i++) {                            //start from the second element in the range
        Point key = arr[i];                                         //store the current element as key
        int j = i - 1;                                              //move j left through the sorted portion of the array
        while (j >= lo && compare_points(&arr[j], &key) > 0) {      //while previous is bigger
            arr[j + 1] = arr[j];                                    //shift element right
            j--;                                                    //move to next element to the left
        }   
        arr[j + 1] = key;                                           //insert key into its correct position in the sorted portion
    }
}

static void quicksort_impl(Point arr[], int lo, int hi) {           //recursive quicksort implementation
    if (hi <= lo + QS_CUTOFF - 1) return;                           //if the subarray is small, use insertion sort
    int m = median_of_3(arr, lo, lo + (hi - lo) / 2, hi);           //find median of first, middle, and last element to use as pivot
    swap_points(&arr[lo], &arr[m]);                                 //move pivot to the beginning of the array
    int j = partition_qs(arr, lo, hi);                              //partition the array around the pivot and get the final index of the pivot
    quicksort_impl(arr, lo, j - 1);                                 //recursively sort the left subarray
    quicksort_impl(arr, j + 1, hi);                                 //recursively sort the right subarray
}

void quicksort_points(Point arr[], int n) {                         //public function to sort points using quicksort algorithm
    if (n < 2) return;                                              //if the array is too small, no need to sort
    shuffle(arr, n);                                                //shuffle the array to avoid worst-case performance on already sorted input
    quicksort_impl(arr, 0, n - 1);                                  //call the recursive quicksort implementation
    insertion_sort_range(arr, 0, n - 1);                            //final insertion sort pass to ensure small subarrays are sorted
}



static void merge(Point arr[], Point tmp[], int lo, int mid, int hi) {      //combine two sorted halves

    memcpy(tmp + lo, arr + lo, (hi - lo + 1) * sizeof(Point));              //copy data to temporary array for merging

    int i = lo, j = mid + 1, k = lo;                                        //setup pointers for merging
    while (i <= mid && j <= hi) {                                           //while there are elements in both halves
        if (compare_by_polar_angle(&tmp[i], &tmp[j]) <= 0)                  //pick the smaller angle
            arr[k++] = tmp[i++];                                            //put the smaller element back into the original array
        else
            arr[k++] = tmp[j++];                                            //if the right element has smaller angle, put it back into the original array
    }
    while (i <= mid) arr[k++] = tmp[i++];                                   //copy remaining left and right elements if any
    while (j <= hi)  arr[k++] = tmp[j++];
}

static void mergesort_impl(Point arr[], Point tmp[], int lo, int hi) {      //mergesort implementation
    if (lo >= hi) return;                                //base case: if the subarray has one or zero elements, it's already sorted
    int mid = lo + (hi - lo) / 2;                       //split the array into two halves
    mergesort_impl(arr, tmp, lo, mid);                  //recursively sort the left half
    mergesort_impl(arr, tmp, mid + 1, hi);              //recursively sort the right half
    merge(arr, tmp, lo, mid, hi);                       //merge the two sorted halves back together
}

void mergesort_points(Point arr[], int n) {                 //public function to sort points using mergesort algorithm
    if (n < 2) return;                                      //if the array is too small, no need to sort  
    Point *tmp = (Point *)malloc(n * sizeof(Point));        //allocate temporary array for merging
    if (!tmp) return;                                       //if memory allocation fails, just return without sorting
    mergesort_impl(arr, tmp, 0, n - 1);                     //call the recursive mergesort implementation
    free(tmp);                                              //free the temporary array after sorting         
}


void convexHull(Point points[], int n, Point hull[], int *hull_size) {      //main function
    *hull_size = 0;                                                         //initialize hull size to 0
    if (n < 3) return;                                                      //if there are less than 3 points, we cannot form a convex hull, so return immediately
    quicksort_points(points, n);                                    //sort by y-coordinate, and by x-coordinate if y's are equal  
    p0_anchor = points[0];                                          //save lowest point globally
    mergesort_points(points + 1, n - 1);                            //sort other by polar angle with respect to p0_anchor   

    int top = 0;                                                    //initialize top of the hull stack
    hull[top++] = points[0];                                        //add the first point to the hull
    hull[top++] = points[1];                                        //add the second point to the hull

    for (int i = 2; i < n; i++) {                                       //loop through rest of sorted points
        while (top >= 2 && ccw(hull[top - 2], hull[top - 1], points[i]) <= 0)     
        //if the last two points in the hull and the current point do not make a left turn, pop the last point from the hull
            top--;                                                      //pop last point from the hull 
        hull[top++] = points[i];                                    //add the current point to the hull 
    }

    *hull_size = top;                                       //set the final hull size to the number of points in the hull   
}
