#ifndef POINT_H
#define POINT_H


typedef struct Point {  //struct definition
    int x, y;
} Point;

typedef struct Point* PointPtr; //opaque pointer to the Point structure

/**
* Creates a new point with coordinates (x, y).
* @param x The x-coordinate of the point.
* @param y The y-coordinate of the point.
* @return A pointer to the created Point structure.
*/
PointPtr create_point(int x, int y);

/**
* Destroys a point and frees the allocated memory.
* @param p The pointer to the Point structure to be
destroyed.
*/
void destroy_point(PointPtr p);

/**
* Compares two points based on their y-coordinates.
* A point (x0, y0) is less than a point (x1, y1) if and only
if:
* - y0 < y1, or
* - y0 == y1 and x0 < x1.
* @param a A pointer to the first point.
* @param b A pointer to the second point.
* @return A negative value if a < b, 0 if a == b, and a
positive value if a > b.
*/
int compare_points(const void* a, const void* b);

/**
* Computes the slope between two points (x0, y0) and (x1,
y1).
* - The slope is calculated as (y1 - y0) / (x1 - x0).
* - If the line is horizontal, the slope is +0.
* - If the line is vertical, the slope is +infinity.
* - If both points are the same, the slope is -infinity.
* @param p1 The first point.
* @param p2 The second point.
* @return The computed slope as a double.
*/

double slope_to(PointPtr p1, PointPtr p2);
// added these so we can use them in tests and fast.c
void set_slope_reference(PointPtr ref);

int compare_by_slope(const void *a, const void *b);

#endif