#include <gtest/gtest.h>
#include "ds/sparse_matrix.h"

TEST(SparseMatrix, InsertAndLookup){
    ds::SparseMatrix<int> sm(100,100);
    EXPECT_EQ(sm.nonZeroCount(), 0u);
    sm.set(2,3,10); sm.set(50,50,7);
    EXPECT_EQ(sm.nonZeroCount(), 2u);
    auto v = sm.get(2,3); ASSERT_NE(v, nullptr); EXPECT_EQ(*v, 10);
    auto v2 = sm.get(1,1); EXPECT_EQ(v2, nullptr);
}

