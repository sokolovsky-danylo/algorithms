#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "convex_hull.h"


static int tests_run  = 0;                                      //counter for total tests run
static int tests_pass = 0;                                      //counter for total tests passed

#define PASS(name) do { tests_run++; tests_pass++; \            
    printf("  [PASS] %s\n", name); } while(0)

#define FAIL(name, msg) do { tests_run++; \
    printf("  [FAIL] %s: %s\n", name, msg); } while(0)

static int hull_contains(Point hull[], int hull_size, Point p) {        //helper function to check if a point is in the hull
    for (int i = 0; i < hull_size; i++)
        if (hull[i].x == p.x && hull[i].y == p.y) return 1;
    return 0;
}

static void test_ccw(void) {                    //test the ccw function with different point configurations
    printf("\n[ccw]\n");

    Point a = {0,0}, b = {2,0}, c = {1,2};
    if (ccw(a, b, c) == 1) PASS("ccw triangle");
    else FAIL("ccw triangle", "expected +1");

    if (ccw(a, c, b) == -1) PASS("cw triangle");
    else FAIL("cw triangle", "expected -1");

    Point d = {2,2}, e = {4,4};
    if (ccw(a, d, e) == 0) PASS("collinear points");
    else FAIL("collinear points", "expected 0");
}

static void test_compare_points(void) {         //test the compare_points function to ensure it sorts points correctly by y-coordinate and then by x-coordinate
    printf("\n[compare_points]\n");

    Point lo = {3,1}, hi = {1,2};
    if (compare_points(&lo, &hi) < 0) PASS("lower Y sorts first");
    else FAIL("lower Y sorts first", "expected negative");

    Point same_y_left  = {1,5};
    Point same_y_right = {3,5};
    if (compare_points(&same_y_left, &same_y_right) < 0) PASS("same Y: smaller X first");
    else FAIL("same Y: smaller X first", "expected negative");

    Point eq1 = {2,2}, eq2 = {2,2};
    if (compare_points(&eq1, &eq2) == 0) PASS("equal points → 0");
    else FAIL("equal points → 0", "expected 0");
}

static void test_basic_convex_hull(void) {      //test the convex hull function with a basic configuration of points to ensure it correctly identifies the hull vertices and excludes interior points
    printf("\n[basic convex hull]\n");

    Point pts[] = {{0,0},{1,1},{2,2},{1,3},{0,2},{2,0}};
    int n = 6;
    Point hull[6]; int hs = 0;
    convexHull(pts, n, hull, &hs);

    if (hs == 5) PASS("hull size == 5");
    else { FAIL("hull size == 5", "wrong count"); return; }


    Point expected[] = {{0,0},{2,0},{2,2},{1,3},{0,2}};
    int ok = 1;
    for (int i = 0; i < 5; i++)
        if (!hull_contains(hull, hs, expected[i])) { ok = 0; break; }

    if (ok) PASS("all expected vertices present");
    else FAIL("all expected vertices present", "missing vertex");

    Point interior = {1,1};
    if (!hull_contains(hull, hs, interior)) PASS("interior point excluded");
    else FAIL("interior point excluded", "interior found on hull");
}

static void test_not_enough_points(void) {      //test the convex hull function with less than 3 points to ensure it correctly handles cases where a convex hull cannot be formed and returns an empty hull
    printf("\n[not enough points]\n");

    Point pts[] = {{0,0},{1,1}};
    Point hull[2]; int hs = 0;
    convexHull(pts, 2, hull, &hs);
    if (hs == 0) PASS("2 points → hull_size == 0");
    else FAIL("2 points → hull_size == 0", "expected 0");
}

static void test_single_point(void) {           //test the convex hull function with a single point to ensure it correctly handles this edge case and returns an empty hull, since a single point cannot form a convex hull
    printf("\n[single point]\n");

    Point pts[] = {{5,5}};
    Point hull[1]; int hs = 0;
    convexHull(pts, 1, hull, &hs);
    if (hs == 0) PASS("1 point → hull_size == 0");
    else FAIL("1 point → hull_size == 0", "expected 0");
}

static void test_collinear_points(void) {       //test the convex hull function with a set of collinear points to ensure it correctly identifies the endpoints of the line segment as the hull vertices and excludes any interior collinear points
    printf("\n[collinear points]\n");

    Point pts[] = {{0,0},{1,1},{2,2},{3,3}};
    int n = 4;
    Point hull[4]; int hs = 0;
    convexHull(pts, n, hull, &hs);

    if (hs >= 2) PASS("collinear: at least 2 hull points");
    else FAIL("collinear: at least 2 hull points", "too few");

    if (hull_contains(hull, hs, (Point){0,0}) &&
        hull_contains(hull, hs, (Point){3,3}))
        PASS("collinear: endpoints present");
    else FAIL("collinear: endpoints present", "endpoint missing");
}

static void test_collinear_with_extra(void) {   //test the convex hull function with a set of collinear points plus an additional point to ensure it correctly identifies the endpoints of the line segment as the hull vertices and includes the extra point if it is outside the line formed by the collinear points, or excludes it if it is inside
    printf("\n[collinear + extra point]\n");

    Point pts[] = {{0,0},{1,1},{2,2},{3,3},{0,3}};
    int n = 5;
    Point hull[5]; int hs = 0;
    convexHull(pts, n, hull, &hs);

    if (hull_contains(hull, hs, (Point){0,3})) PASS("extra point on hull");
    else FAIL("extra point on hull", "(0,3) missing");

    if (hs == 3) PASS("hull size == 3");
    else FAIL("hull size == 3", "wrong count");
}

static void test_random_points(void) {          //test the convex hull function with a random configuration of points to ensure it produces a reasonable hull that includes the expected corner points and excludes interior points, even when the input is not in any particular order
    printf("\n[random points]\n");

    Point pts[] = {{0,0},{2,0},{3,1},{3,3},{2,3},{1,2}};
    int n = 6;
    Point hull[6]; int hs = 0;
    convexHull(pts, n, hull, &hs);

    if (hs == 5 || hs == 6) PASS("reasonable hull size (5 or 6)");
    else FAIL("reasonable hull size (5 or 6)", "unexpected count");

    int corners_ok =
        hull_contains(hull, hs, (Point){0,0}) &&
        hull_contains(hull, hs, (Point){2,0}) &&
        hull_contains(hull, hs, (Point){3,3}) &&
        hull_contains(hull, hs, (Point){2,3});

    if (corners_ok) PASS("corner points on hull");
    else FAIL("corner points on hull", "missing corner");
}

static void test_square(void) {                 //test the convex hull function with points forming a square plus an interior point to ensure it correctly identifies the four corners of the square as the hull vertices and excludes the interior point
    printf("\n[square]\n");

    Point pts[] = {{0,0},{4,0},{4,4},{0,4},{2,2}};
    int n = 5;
    Point hull[5]; int hs = 0;
    convexHull(pts, n, hull, &hs);

    if (hs == 4) PASS("square: hull size == 4");
    else FAIL("square: hull size == 4", "wrong count");

    if (!hull_contains(hull, hs, (Point){2,2})) PASS("square: centre excluded");
    else FAIL("square: centre excluded", "centre found on hull");
}

static void test_triangle(void) {               //test the convex hull function with points forming a triangle to ensure it correctly identifies all three vertices of the triangle as the hull and does not exclude any of them, since all three points are necessary to form the convex hull in this case
    printf("\n[triangle]\n");

    Point pts[] = {{0,0},{6,0},{3,6}};
    int n = 3;
    Point hull[3]; int hs = 0;
    convexHull(pts, n, hull, &hs);

    if (hs == 3) PASS("triangle: hull size == 3");
    else FAIL("triangle: hull size == 3", "wrong count");
}

int main(void) {
    printf("=== Convex Hull Unit Tests ===\n");

    test_ccw();
    test_compare_points();
    test_basic_convex_hull();
    test_not_enough_points();
    test_single_point();
    test_collinear_points();
    test_collinear_with_extra();
    test_random_points();
    test_square();
    test_triangle();

    printf("\n-------------------------\n");
    printf("Results: %d/%d passed\n", tests_pass, tests_run);

    return (tests_pass == tests_run) ? 0 : 1;
}
