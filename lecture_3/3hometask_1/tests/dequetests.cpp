#include <gtest/gtest.h>
#include <cstring>

extern "C" {
#include "deque.h"
}

static int int_val(Item item)
{
    return *static_cast<int *>(item);
}

struct DequeGuard {
    DequePtr d;
    explicit DequeGuard() : d(DequeInit()) {}
    ~DequeGuard() { DequeDestroy(d); }
    operator DequePtr() const { return d; }
};

class DequeTest : public ::testing::Test {
protected:
    DequeGuard dg;          
    DequePtr   d = dg.d;
};

TEST_F(DequeTest, InitIsEmpty)
{
    EXPECT_TRUE(DequeEmpty(d));
    EXPECT_EQ(DequeSize(d), 0u);
}

TEST_F(DequeTest, RemoveFirstOnEmptyReturnsNull)
{
    EXPECT_EQ(DequeRemoveFirst(d), nullptr);
}

TEST_F(DequeTest, RemoveLastOnEmptyReturnsNull)
{
    EXPECT_EQ(DequeRemoveLast(d), nullptr);
}

TEST_F(DequeTest, SingleElementAddFirstRemoveFirst)
{
    int *v = new int(42);
    DequeAddFirst(d, v);

    EXPECT_FALSE(DequeEmpty(d));
    EXPECT_EQ(DequeSize(d), 1u);

    Item out = DequeRemoveFirst(d);
    EXPECT_EQ(int_val(out), 42);
    EXPECT_TRUE(DequeEmpty(d));

    delete v;
}

TEST_F(DequeTest, SingleElementAddFirstRemoveLast)
{
    int *v = new int(7);
    DequeAddFirst(d, v);

    Item out = DequeRemoveLast(d);
    EXPECT_EQ(int_val(out), 7);
    EXPECT_TRUE(DequeEmpty(d));

    delete v;
}

TEST_F(DequeTest, SingleElementAddLastRemoveFirst)
{
    int *v = new int(99);
    DequeAddLast(d, v);

    Item out = DequeRemoveFirst(d);
    EXPECT_EQ(int_val(out), 99);
    EXPECT_TRUE(DequeEmpty(d));

    delete v;
}

TEST_F(DequeTest, AddFirstActsAsStack)
{
    int *a = new int(1), *b = new int(2), *c = new int(3);
    DequeAddFirst(d, a);
    DequeAddFirst(d, b);
    DequeAddFirst(d, c);

    EXPECT_EQ(DequeSize(d), 3u);
    EXPECT_EQ(int_val(DequeRemoveFirst(d)), 3);
    EXPECT_EQ(int_val(DequeRemoveFirst(d)), 2);
    EXPECT_EQ(int_val(DequeRemoveFirst(d)), 1);
    EXPECT_TRUE(DequeEmpty(d));

    delete a; delete b; delete c;
}

TEST_F(DequeTest, AddLastActsAsStack)
{
    int *a = new int(10), *b = new int(20), *c = new int(30);
    DequeAddLast(d, a);
    DequeAddLast(d, b);
    DequeAddLast(d, c);

    EXPECT_EQ(int_val(DequeRemoveFirst(d)), 10);
    EXPECT_EQ(int_val(DequeRemoveFirst(d)), 20);
    EXPECT_EQ(int_val(DequeRemoveFirst(d)), 30);
    EXPECT_TRUE(DequeEmpty(d));

    delete a; delete b; delete c;
}

TEST_F(DequeTest, AddLastRemoveLastActsAsReverseStack)
{
    int *a = new int(1), *b = new int(2), *c = new int(3);
    DequeAddLast(d, a);
    DequeAddLast(d, b);
    DequeAddLast(d, c);

    EXPECT_EQ(int_val(DequeRemoveLast(d)), 3);
    EXPECT_EQ(int_val(DequeRemoveLast(d)), 2);
    EXPECT_EQ(int_val(DequeRemoveLast(d)), 1);
    EXPECT_TRUE(DequeEmpty(d));

    delete a; delete b; delete c;
}

TEST_F(DequeTest, MixedAddRemove)
{

    int *v[6];
    for (int i = 0; i < 6; i++) v[i] = new int((i + 1) * 5); 

    DequeAddFirst(d, v[0]);  
    DequeAddLast(d,  v[2]);  
    DequeAddFirst(d, v[1]);   
    DequeAddLast(d,  v[4]);  
    DequeAddFirst(d, v[3]);  
    DequeAddLast(d,  v[5]);  

    EXPECT_EQ(DequeSize(d), 6u);

    EXPECT_EQ(int_val(DequeRemoveFirst(d)), 20);
    EXPECT_EQ(int_val(DequeRemoveLast(d)),  30);
    EXPECT_EQ(int_val(DequeRemoveFirst(d)), 10);
    EXPECT_EQ(int_val(DequeRemoveLast(d)),  25);
    EXPECT_EQ(int_val(DequeRemoveFirst(d)),  5);
    EXPECT_EQ(int_val(DequeRemoveLast(d)),  15);

    EXPECT_TRUE(DequeEmpty(d));
    for (int i = 0; i < 6; i++) delete v[i];
}

TEST_F(DequeTest, SizeTracksCorrectly)
{
    int *items[5];
    for (int i = 0; i < 5; i++) {
        items[i] = new int(i);
        DequeAddLast(d, items[i]);
        EXPECT_EQ(DequeSize(d), static_cast<size_t>(i + 1));
    }
    for (int i = 4; i >= 0; i--) {
        DequeRemoveLast(d);
        EXPECT_EQ(DequeSize(d), static_cast<size_t>(i));
    }
    for (int i = 0; i < 5; i++) delete items[i];
}

TEST_F(DequeTest, StoresStringPointers)
{

    DequeAddLast(d,  const_cast<char *>("alpha"));
    DequeAddLast(d,  const_cast<char *>("beta"));
    DequeAddFirst(d, const_cast<char *>("zeta"));  // head = zeta

    EXPECT_STREQ(static_cast<char *>(DequeRemoveFirst(d)), "zeta");
    EXPECT_STREQ(static_cast<char *>(DequeRemoveLast(d)),  "beta");
    EXPECT_STREQ(static_cast<char *>(DequeRemoveFirst(d)), "alpha");
}

TEST_F(DequeTest, InterleavedAddRemove)
{
    int *a = new int(1);
    DequeAddFirst(d, a);
    EXPECT_EQ(int_val(DequeRemoveFirst(d)), 1);   

    int *b = new int(2);
    DequeAddLast(d, b);
    EXPECT_EQ(int_val(DequeRemoveLast(d)), 2);    

    int *c = new int(3);
    DequeAddFirst(d, c);
    EXPECT_EQ(DequeSize(d), 1u);
    EXPECT_EQ(int_val(DequeRemoveLast(d)), 3);

    EXPECT_TRUE(DequeEmpty(d));
    delete a; delete b; delete c;
}

TEST_F(DequeTest, LargeInsertionAndRemoval)
{
    const int N = 10000;
    int *items[N];

    for (int i = 0; i < N; i++) {
        items[i] = new int(i);
        (i % 2 == 0) ? DequeAddFirst(d, items[i])
                      : DequeAddLast(d,  items[i]);
    }

    EXPECT_EQ(DequeSize(d), static_cast<size_t>(N));

    for (int i = 0; i < N; i++)
        (i % 2 == 0) ? DequeRemoveFirst(d) : DequeRemoveLast(d);

    EXPECT_TRUE(DequeEmpty(d));
    for (int i = 0; i < N; i++) delete items[i];
}