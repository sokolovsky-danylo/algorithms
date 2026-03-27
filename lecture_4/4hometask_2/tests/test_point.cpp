#include <gtest/gtest.h>
#include <cmath>

extern "C" {
    #include "point.h"
}

//point tests
TEST(PointTest, CreateStoresCoordinates) {  //test that create_point correctly stores the provided coordinates in the Point structure
    PointPtr p = create_point(3, 7);
    EXPECT_EQ(p->x, 3);
    EXPECT_EQ(p->y, 7);
    destroy_point(p);      
}

TEST(PointTest, CreateNegativeCoordinates) {    //test that create_point can handle negative coordinates correctly
    PointPtr p = create_point(-5, -10);
    EXPECT_EQ(p->x, -5);
    EXPECT_EQ(p->y, -10);
    destroy_point(p);
}

//slope_to tests
TEST(SlopeTest, HorizontalLine) {       //test that slope_to correctly identifies a horizontal line and returns +0.0
    PointPtr p1 = create_point(0, 5);
    PointPtr p2 = create_point(3, 5);
    EXPECT_DOUBLE_EQ(slope_to(p1, p2), 0.0);
    destroy_point(p1);
    destroy_point(p2);
}

TEST(SlopeTest, VerticalLine) {     //test that slope_to correctly identifies a vertical line and returns +infinity
    PointPtr p1 = create_point(4, 0);
    PointPtr p2 = create_point(4, 9);
    EXPECT_TRUE(std::isinf(slope_to(p1, p2)));
    EXPECT_GT(slope_to(p1, p2), 0);
    destroy_point(p1);
    destroy_point(p2);
}

TEST(SlopeTest, SamePoint) {        //test that slope_to correctly identifies when both points are the same and returns -infinity
    PointPtr p = create_point(2, 2);
    EXPECT_TRUE(std::isinf(slope_to(p, p)));
    EXPECT_LT(slope_to(p, p), 0);
    destroy_point(p);
}

TEST(SlopeTest, DiagonalSlope) {        //test that slope_to correctly calculates the slope between two points that are not horizontal, vertical, or the same
    PointPtr p1 = create_point(0, 0);
    PointPtr p2 = create_point(2, 4);
    EXPECT_DOUBLE_EQ(slope_to(p1, p2), 2.0);
    destroy_point(p1);
    destroy_point(p2);
}

TEST(SlopeTest, NegativeSlope) {        //test that slope_to correctly calculates a negative slope between two points
    PointPtr p1 = create_point(0, 4);
    PointPtr p2 = create_point(2, 0);
    EXPECT_DOUBLE_EQ(slope_to(p1, p2), -2.0);
    destroy_point(p1);
    destroy_point(p2);
}

//compare_points tests
TEST(ComparePointsTest, SmallerYComesFirst) {       //test that compare_points correctly identifies that a point with a smaller y-coordinate should be considered "less than" a point with a larger y-coordinate
    PointPtr p1 = create_point(5, 1);
    PointPtr p2 = create_point(0, 9);
    /* p1.y < p2.y → p1 should be "less" */
    EXPECT_LT(compare_points(&p1, &p2), 0);
    EXPECT_GT(compare_points(&p2, &p1), 0);
    destroy_point(p1);
    destroy_point(p2);
}

TEST(ComparePointsTest, SameYSmallerXComesFirst) {  //test that compare_points correctly identifies that when two points have the same y-coordinate, the point with the smaller x-coordinate should be considered "less than" the other point
    PointPtr p1 = create_point(2, 5);
    PointPtr p2 = create_point(7, 5);
    EXPECT_LT(compare_points(&p1, &p2), 0);
    EXPECT_GT(compare_points(&p2, &p1), 0);
    destroy_point(p1);
    destroy_point(p2);
}

TEST(ComparePointsTest, EqualPointsReturnZero) {    //test that compare_points correctly identifies when two points are equal (same x and y coordinates) and returns 0
    PointPtr p1 = create_point(3, 3);
    PointPtr p2 = create_point(3, 3);
    EXPECT_EQ(compare_points(&p1, &p2), 0);
    destroy_point(p1);
    destroy_point(p2);
}

//compare_by_slope tests
TEST(CompareBySlopeTest, SteepSlopeIsGreater) {     //test that compare_by_slope correctly identifies that a point with a steeper slope to the reference point should be considered "greater than" a point with a less steep slope
    PointPtr ref  = create_point(0, 0);
    PointPtr p1   = create_point(2, 1);   
    PointPtr p2   = create_point(1, 3);   

    set_slope_reference(ref);   
    EXPECT_LT(compare_by_slope(&p1, &p2), 0);
    EXPECT_GT(compare_by_slope(&p2, &p1), 0);

    destroy_point(ref);
    destroy_point(p1);
    destroy_point(p2);
}

TEST(CompareBySlopeTest, EqualSlopesReturnZero) {       //test that compare_by_slope correctly identifies when two points have the same slope to the reference point and returns 0
    PointPtr ref = create_point(0, 0);
    PointPtr p1  = create_point(1, 2);   
    PointPtr p2  = create_point(2, 4);   

    set_slope_reference(ref);
    EXPECT_EQ(compare_by_slope(&p1, &p2), 0);

    destroy_point(ref);
    destroy_point(p1);
    destroy_point(p2);
}



TEST(CollinearTest, FivePointsOnHorizontalLine) {       //test that slope_to correctly calculates the slope between a reference point and multiple other points that are all collinear on a horizontal line, and that compare_by_slope correctly identifies that they all have the same slope to the reference point
    PointPtr pts[5] = {
        create_point(14000, 10000),
        create_point(18000, 10000),
        create_point(19000, 10000),
        create_point(21000, 10000),
        create_point(32000, 10000)
    };

    set_slope_reference(pts[0]);
    for (int i = 1; i < 5; i++) {
        EXPECT_DOUBLE_EQ(slope_to(pts[0], pts[i]), 0.0);
    }

    for (int i = 0; i < 5; i++) destroy_point(pts[i]);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}