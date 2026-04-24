#include <gtest/gtest.h>

extern "C" {
    #include "../include/llrb.h"
}

class LLRBTest : public ::testing::Test {
protected:
    NodePtr tree = nullptr;

    void SetUp() override {
        const char* keys[] = {"M", "J", "R", "E", "L", "P", "X", "C", "H", "S", "A"};
        for (const char* k : keys) {
            tree = LLRBPut(tree, k, k);
        }
    }

    void TearDown() override {
        LLRBDestroy(tree);
    }
};

TEST_F(LLRBTest, StructuralIntegrity) {
    ASSERT_NE(tree, nullptr);
    EXPECT_STREQ(LLRBGetKey(tree), "M");
    EXPECT_STREQ(LLRBGetKey(LLRBGetLeft(tree)), "J");
    EXPECT_STREQ(LLRBGetKey(LLRBGetRight(tree)), "R");
    NodePtr e_node = LLRBGetLeft(LLRBGetLeft(tree));
    EXPECT_STREQ(LLRBGetKey(e_node), "E");
}

TEST_F(LLRBTest, ColorCheck) {
    EXPECT_FALSE(LLRBIsRed(tree));
    
    NodePtr e_node = LLRBGetLeft(LLRBGetLeft(tree));
    EXPECT_TRUE(LLRBIsRed(e_node));

    NodePtr r_node = LLRBGetRight(tree);
    EXPECT_FALSE(LLRBIsRed(r_node));
}

TEST_F(LLRBTest, PropertiesAndBalance) {
    EXPECT_TRUE(test_LLRBProperties(tree));
    bool is_avl_balanced = isBalanced(tree);
    EXPECT_FALSE(is_avl_balanced);
}