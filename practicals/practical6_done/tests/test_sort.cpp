#include <gtest/gtest.h>
extern "C" {
    #include "sorting.h"
}

TEST(InsertionSortTest, BasicSort) {
    Point p1 = {0,0}, p2 = {2,0}, p3 = {1,1};
    Item arr[] = {&p3, &p2, &p1};
    insertion_sort(arr, 3);
    
    EXPECT_EQ(arr[0]->x, 0);
    EXPECT_EQ(arr[1]->x, 2);
    EXPECT_EQ(arr[2]->x, 1);
}

TEST(InsertionSortTest, AlreadySorted) {
    Point p1 = {0,0}, p2 = {1,1};
    Item arr[] = {&p1, &p2};
    insertion_sort(arr, 2);
    EXPECT_EQ(arr[0], &p1);
    EXPECT_EQ(arr[1], &p2);
}

TEST(InsertionSortTest, EmptyOrSingle) {
    Item* arr = NULL;
    insertion_sort(arr, 0);
    
    Point p = {1,1};
    Item arr2[] = {&p};
    insertion_sort(arr2, 1);
    EXPECT_EQ(arr2[0], &p);
}