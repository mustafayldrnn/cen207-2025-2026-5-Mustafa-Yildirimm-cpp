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

TEST(SparseMatrix, Dimensions){
    ds::SparseMatrix<int> sm(50, 75);
    EXPECT_EQ(sm.rows(), 50u);
    EXPECT_EQ(sm.cols(), 75u);
    
    // Test boundary conditions
    sm.set(0, 0, 1);
    sm.set(49, 74, 2);
    EXPECT_EQ(sm.nonZeroCount(), 2u);
    
    auto v1 = sm.get(0, 0);
    ASSERT_NE(v1, nullptr);
    EXPECT_EQ(*v1, 1);
    
    auto v2 = sm.get(49, 74);
    ASSERT_NE(v2, nullptr);
    EXPECT_EQ(*v2, 2);
}

TEST(SparseMatrix, UpdateValues){
    ds::SparseMatrix<int> sm(10, 10);
    sm.set(5, 5, 100);
    EXPECT_EQ(sm.nonZeroCount(), 1u);
    
    // Update existing value
    sm.set(5, 5, 200);
    EXPECT_EQ(sm.nonZeroCount(), 1u); // Still only one non-zero element
    
    auto v = sm.get(5, 5);
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(*v, 200);
}

TEST(SparseMatrix, LargeMatrix){
    ds::SparseMatrix<int> sm(1000, 1000);
    EXPECT_EQ(sm.rows(), 1000u);
    EXPECT_EQ(sm.cols(), 1000u);
    
    // Add elements in different quadrants
    sm.set(100, 200, 1);
    sm.set(500, 500, 2);
    sm.set(800, 900, 3);
    
    EXPECT_EQ(sm.nonZeroCount(), 3u);
    
    EXPECT_EQ(*sm.get(100, 200), 1);
    EXPECT_EQ(*sm.get(500, 500), 2);
    EXPECT_EQ(*sm.get(800, 900), 3);
    
    // Verify empty positions
    EXPECT_EQ(sm.get(0, 0), nullptr);
    EXPECT_EQ(sm.get(999, 999), nullptr);
}

