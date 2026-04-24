#include <gtest/gtest.h>

#define N 10

int sz[N];

bool connected__quick_find(const int* id, int p, int q) {
    return id[p] == id[q];
}

void union__quick_find(int* id, int n, int p, int q) {
    int pid = id[p];
    int qid = id[q];
    for (int i = 0; i < n; i++) {
        if (id[i] == pid) {
            id[i] = qid;
        }
    }
}

int root__quick_union(const int* id, int i) {
    while (i != id[i]) {
        i = id[i];
    }
    return i;
}

bool connected__quick_union(const int* id, int p, int q) {
    return root__quick_union(id, p) == root__quick_union(id, q);
}

void union__quick_union(int* id, int p, int q) {
    int root_p = root__quick_union(id, p);
    int root_q = root__quick_union(id, q);
    id[root_p] = root_q;
}

void union__weighted_quick_union(int* id, int* sz, int p, int q) {
    int root_p = root__quick_union(id, p);
    int root_q = root__quick_union(id, q);
    if (root_p == root_q) return;
    
    if (sz[root_p] < sz[root_q]) {
        id[root_p] = root_q;
        sz[root_q] += sz[root_p];
    } else {
        id[root_q] = root_p;
        sz[root_p] += sz[root_q];
    }
}

int root__quick_union_path_compression(int* id, int i) {
    while (i != id[i]) {
        id[i] = id[id[i]];
        i = id[i];
    }
    return i;
}

class QuickUnionTest : public ::testing::Test {
protected:
    int id[N];

    void SetUp() override {
        for (int i = 0; i < N; ++i) {
            id[i] = i;
            sz[i] = 1;
        }
    }

    void TearDown() override {
    }
};

TEST_F(QuickUnionTest, ConnectedQuickFind) {
    id[3] = id[4] = 1;
    EXPECT_TRUE(connected__quick_find(id, 3, 4));
    EXPECT_FALSE(connected__quick_find(id, 3, 5));
}

TEST_F(QuickUnionTest, UnionQuickFind) {
    union__quick_find(id, N, 3, 4);
    EXPECT_TRUE(connected__quick_find(id, 3, 4));
    union__quick_find(id, N, 4, 8);
    EXPECT_TRUE(connected__quick_find(id, 3, 8));
}

TEST_F(QuickUnionTest, RootQuickUnion) {
    id[3] = 4;
    id[4] = 8;
    EXPECT_EQ(root__quick_union(id, 3), 8);
    EXPECT_EQ(root__quick_union(id, 4), 8);
}

TEST_F(QuickUnionTest, ConnectedQuickUnion) {
    id[3] = 4;
    id[4] = 8;
    id[5] = 8;
    EXPECT_TRUE(connected__quick_union(id, 3, 5));
    EXPECT_FALSE(connected__quick_union(id, 3, 1));
}

TEST_F(QuickUnionTest, UnionQuickUnion) {
    union__quick_union(id, 3, 4);
    EXPECT_EQ(root__quick_union(id, 3), 4);
    union__quick_union(id, 4, 8);
    EXPECT_EQ(root__quick_union(id, 3), 8);
}

TEST_F(QuickUnionTest, UnionWeightedQuickUnion) {
    union__weighted_quick_union(id, sz, 3, 4);
    EXPECT_TRUE(connected__quick_union(id, 3, 4));
    union__weighted_quick_union(id, sz, 4, 8);
    EXPECT_TRUE(connected__quick_union(id, 3, 8));
    
    int root = root__quick_union(id, 3);
    EXPECT_EQ(sz[root], 3);
}

TEST_F(QuickUnionTest, RootQuickUnionPathCompression) {
    id[3] = 4;
    id[4] = 8;
    id[8] = 9;
    EXPECT_EQ(root__quick_union_path_compression(id, 3), 9);
    EXPECT_EQ(id[3], 8);
}