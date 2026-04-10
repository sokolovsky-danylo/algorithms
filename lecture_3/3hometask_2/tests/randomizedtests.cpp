#include <gtest/gtest.h>
#include <unordered_map>
#include <cmath>

extern "C" {
#include "randomized.h"
}

struct RQGuard {
    RandomizedQueuePtr rq;
    RQGuard()  : rq(RandomizedQueueInit()) {}
    ~RQGuard() { RandomizedQueueDestroy(rq); }
    operator RandomizedQueuePtr() const { return rq; }
};

class RQTest : public ::testing::Test {
protected:
    RQGuard guard;
    RandomizedQueuePtr rq = guard.rq;
};

TEST_F(RQTest, InitIsEmpty)
{
    EXPECT_TRUE(RandomizedQueueEmpty(rq));
    EXPECT_EQ(RandomizedQueueSize(rq), 0u);
}

TEST_F(RQTest, DequeueOnEmptyReturnsNull)
{
    EXPECT_EQ(RandomizedQueueDequeue(rq), nullptr);
}

TEST_F(RQTest, SingleEnqueueDequeue)
{
    int v = 42;
    RandomizedQueueEnqueue(rq, &v);

    EXPECT_FALSE(RandomizedQueueEmpty(rq));
    EXPECT_EQ(RandomizedQueueSize(rq), 1u);

    int *out = static_cast<int *>(RandomizedQueueDequeue(rq));
    EXPECT_EQ(*out, 42);
    EXPECT_TRUE(RandomizedQueueEmpty(rq));
}

TEST_F(RQTest, SizeTracksEnqueueAndDequeue)
{
    int vals[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        RandomizedQueueEnqueue(rq, &vals[i]);
        EXPECT_EQ(RandomizedQueueSize(rq), static_cast<size_t>(i + 1));
    }
    for (int i = 4; i >= 0; i--) {
        RandomizedQueueDequeue(rq);
        EXPECT_EQ(RandomizedQueueSize(rq), static_cast<size_t>(i));
    }
}

TEST_F(RQTest, AllItemsReturnedExactlyOnce)
{
    const int N = 100;
    int vals[N];
    std::unordered_map<int, int> seen;

    for (int i = 0; i < N; i++) {
        vals[i] = i;
        RandomizedQueueEnqueue(rq, &vals[i]);
    }

    for (int i = 0; i < N; i++) {
        int *out = static_cast<int *>(RandomizedQueueDequeue(rq));
        ASSERT_NE(out, nullptr);
        seen[*out]++;
    }

    EXPECT_TRUE(RandomizedQueueEmpty(rq));

    // Every value in [0, N) must appear exactly once
    for (int i = 0; i < N; i++)
        EXPECT_EQ(seen[i], 1) << "value " << i << " appeared " << seen[i] << " times";
}

TEST_F(RQTest, DequeueIsUniform)
{
    const int N      = 5;
    const int TRIALS = 10000;
    int vals[N];
    int counts[N] = {};

    for (int t = 0; t < TRIALS; t++) {
        RQGuard g;
        for (int i = 0; i < N; i++) {
            vals[i] = i;
            RandomizedQueueEnqueue(g.rq, &vals[i]);
        }
        int *out = static_cast<int *>(RandomizedQueueDequeue(g.rq));
        ASSERT_NE(out, nullptr);
        counts[*out]++;
    }

    double expected = static_cast<double>(TRIALS) / N;
    double chi2 = 0.0;
    for (int i = 0; i < N; i++) {
        double diff = counts[i] - expected;
        chi2 += diff * diff / expected;
    }

    EXPECT_LT(chi2, 18.47)
        << "Distribution looks non-uniform (chi2=" << chi2 << ")";
}

TEST_F(RQTest, GrowsBeyondInitialCapacity)
{
    const int N = 1000;
    int vals[N];
    for (int i = 0; i < N; i++) {
        vals[i] = i;
        RandomizedQueueEnqueue(rq, &vals[i]);
    }
    EXPECT_EQ(RandomizedQueueSize(rq), static_cast<size_t>(N));

    for (int i = 0; i < N; i++)
        ASSERT_NE(RandomizedQueueDequeue(rq), nullptr);

    EXPECT_TRUE(RandomizedQueueEmpty(rq));
}

TEST_F(RQTest, InterleavedEnqueueDequeue)
{
    int a = 1, b = 2, c = 3;
    RandomizedQueueEnqueue(rq, &a);
    RandomizedQueueEnqueue(rq, &b);
    EXPECT_EQ(RandomizedQueueSize(rq), 2u);

    RandomizedQueueDequeue(rq);
    EXPECT_EQ(RandomizedQueueSize(rq), 1u);

    RandomizedQueueEnqueue(rq, &c);
    EXPECT_EQ(RandomizedQueueSize(rq), 2u);

    RandomizedQueueDequeue(rq);
    RandomizedQueueDequeue(rq);
    EXPECT_TRUE(RandomizedQueueEmpty(rq));
}