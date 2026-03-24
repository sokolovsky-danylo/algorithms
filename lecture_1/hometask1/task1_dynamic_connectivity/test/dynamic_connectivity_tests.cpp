#include "dynamic_connectivity.h"

#include <gtest/gtest.h>


class DynamicConnectivityTest : public ::testing::Test {
protected:
    DynamicConnectivity dc;

    void SetUp() override {
        init_dynamic_connectivity(&dc, 10);
    }

    void TearDown() override {
        for (int i = 0; i < CAPACITY; ++i) {
            dc.id[i] = 0;
            dc.sz[i] = 0;
        }
    }
};

TEST_F(DynamicConnectivityTest, Initialization) { //1

    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(dc.id[i], i);
        EXPECT_EQ(dc.sz[i], 1);
    }
}

TEST_F(DynamicConnectivityTest, InitializationCapacity) {

    init_dynamic_connectivity(&dc, CAPACITY);
    for (int i = 0; i < CAPACITY; ++i) {
        EXPECT_EQ(dc.id[i], i);
        EXPECT_EQ(dc.sz[i], 1);
    }
}

TEST_F(DynamicConnectivityTest, RootFunction) {

    EXPECT_EQ(root(&dc, 0), 0);
    EXPECT_EQ(root(&dc, 1), 1);
    EXPECT_EQ(root(&dc, 2), 2);
}

TEST_F(DynamicConnectivityTest, ConnectedFunction) {

    EXPECT_FALSE(connected(&dc, 0, 1));
    EXPECT_TRUE(connected(&dc, 0, 0));
}

TEST_F(DynamicConnectivityTest, UnionFunction) {

    add_union(&dc, 0, 1);
    EXPECT_TRUE(connected(&dc, 0, 1));
    EXPECT_TRUE(connected(&dc, 1, 0));

    add_union(&dc, 1, 2);
    EXPECT_TRUE(connected(&dc, 0, 2));
}

TEST_F(DynamicConnectivityTest, TestTwoConnectedComponents) {

    add_union(&dc, 4, 3);
    add_union(&dc, 3, 8);
    add_union(&dc, 6, 5);
    add_union(&dc, 9, 4);
    add_union(&dc, 2, 1);
    add_union(&dc, 8, 9);
    add_union(&dc, 5, 0);
    add_union(&dc, 7, 2);
    add_union(&dc, 6, 1);

    EXPECT_TRUE(connected(&dc, 0, 7));
    EXPECT_TRUE(connected(&dc, 3, 9)); 
    EXPECT_FALSE(connected(&dc, 0, 3)); 
}

TEST_F(DynamicConnectivityTest, TestWeightedUnion) {

    add_union(&dc, 4, 3); 
    add_union(&dc, 3, 8);
    add_union(&dc, 6, 5);
    add_union(&dc, 9, 4);

    int root_4 = root(&dc, 4);
    int root_9 = root(&dc, 9);

    ASSERT_EQ(root_4, root_9); 
    ASSERT_EQ(root(&dc, 3), root_4); 
    ASSERT_EQ(root(&dc, 8), root_4); 
}

TEST_F(DynamicConnectivityTest, TestPathCompression) {

    add_union(&dc, 4, 3);
    add_union(&dc, 3, 8);
    add_union(&dc, 6, 5);
    add_union(&dc, 9, 4);
    add_union(&dc, 2, 1);

    int root_3_before = root(&dc, 3);
    int root_8_before = root(&dc, 8);

    int root_3_after = root(&dc, 3);
    int root_8_after = root(&dc, 8);

    ASSERT_EQ(root_3_before, root_3_after);
    ASSERT_EQ(root_8_before, root_8_after);

    ASSERT_EQ(dc.id[3], root_3_after);
    ASSERT_EQ(dc.id[8], root_8_after);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
