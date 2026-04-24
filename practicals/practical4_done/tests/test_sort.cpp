#include <gtest/gtest.h>
#include <string.h>

extern "C" {
#include "sort.h"
}

typedef struct {
    char name[10];
    int val;
} Data;

int cmp_data(const void *a, const void *b) {
    return ((Data *)a)->val - ((Data *)b)->val;
}

TEST(SortTest, StructArray) { 
    Data arr[] = {{"B", 20}, {"A", 10}, {"C", 30}};
    shell_sort(arr, 3, sizeof(Data), cmp_data);
    EXPECT_EQ(arr[0].val, 10);
    EXPECT_EQ(arr[2].val, 30);
    EXPECT_STREQ(arr[0].name, "A");
}

int cmp_int(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

TEST(SortTest, IntArray) {
    int arr[] = {5, 1, 4, 2, 8};
    int expected[] = {1, 2, 4, 5, 8};
    shell_sort(arr, 5, sizeof(int), cmp_int);
    for(int i=0; i<5; i++) EXPECT_EQ(arr[i], expected[i]);
}