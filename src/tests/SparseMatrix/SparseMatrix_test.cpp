/**
 * @file SparseMatrix_test.cpp
 * @brief Unit tests for Sparse Matrix
 */

#include <gtest/gtest.h>
#include "../../SparseMatrix/header/SparseMatrix.h"

using namespace Coruh::DataStructures;

class SparseMatrixTest : public ::testing::Test {
protected:
    void SetUp() override {
        matrix = new SparseMatrix<int>(10, 10, 0);
    }
    
    void TearDown() override {
        delete matrix;
    }
    
    SparseMatrix<int>* matrix;
};

TEST_F(SparseMatrixTest, EmptyMatrix) {
    EXPECT_EQ(matrix->getNonZeroCount(), 0);
    EXPECT_EQ(matrix->get(0, 0), 0);
    EXPECT_FALSE(matrix->hasValue(0, 0));
}

TEST_F(SparseMatrixTest, SetAndGetValue) {
    matrix->set(2, 3, 42);
    EXPECT_EQ(matrix->get(2, 3), 42);
    EXPECT_TRUE(matrix->hasValue(2, 3));
    EXPECT_EQ(matrix->getNonZeroCount(), 1);
}

TEST_F(SparseMatrixTest, MultipleValues) {
    matrix->set(1, 1, 10);
    matrix->set(2, 2, 20);
    matrix->set(3, 3, 30);
    
    EXPECT_EQ(matrix->getNonZeroCount(), 3);
    EXPECT_EQ(matrix->get(1, 1), 10);
    EXPECT_EQ(matrix->get(2, 2), 20);
    EXPECT_EQ(matrix->get(3, 3), 30);
}

TEST_F(SparseMatrixTest, RemoveValue) {
    matrix->set(2, 3, 42);
    EXPECT_TRUE(matrix->hasValue(2, 3));
    
    matrix->remove(2, 3);
    EXPECT_FALSE(matrix->hasValue(2, 3));
    EXPECT_EQ(matrix->get(2, 3), 0);
    EXPECT_EQ(matrix->getNonZeroCount(), 0);
}

TEST_F(SparseMatrixTest, MemoryUsage) {
    matrix->set(1, 1, 10);
    matrix->set(2, 2, 20);
    
    size_t memoryUsage = matrix->getMemoryUsage();
    EXPECT_GT(memoryUsage, 0);
}

TEST_F(SparseMatrixTest, GetAllNonZero) {
    matrix->set(1, 1, 10);
    matrix->set(2, 2, 20);
    matrix->set(3, 3, 30);
    
    auto nonZeroElements = matrix->getAllNonZero();
    EXPECT_EQ(nonZeroElements.size(), 3);
}

TEST_F(SparseMatrixTest, OutOfBounds) {
    EXPECT_THROW(matrix->set(10, 0, 42), std::out_of_range);
    EXPECT_THROW(matrix->set(0, 10, 42), std::out_of_range);
    EXPECT_THROW(matrix->get(10, 0), std::out_of_range);
    EXPECT_THROW(matrix->get(0, 10), std::out_of_range);
}

TEST_F(SparseMatrixTest, ClearMatrix) {
    matrix->set(1, 1, 10);
    matrix->set(2, 2, 20);
    matrix->clear();
    
    EXPECT_EQ(matrix->getNonZeroCount(), 0);
    EXPECT_FALSE(matrix->hasValue(1, 1));
    EXPECT_FALSE(matrix->hasValue(2, 2));
}

TEST_F(SparseMatrixTest, Dimensions) {
    auto dimensions = matrix->getDimensions();
    EXPECT_EQ(dimensions.first, 10);
    EXPECT_EQ(dimensions.second, 10);
}

TEST_F(SparseMatrixTest, SparseProperty) {
    // Fill only a few positions
    matrix->set(0, 0, 1);
    matrix->set(9, 9, 2);
    
    EXPECT_EQ(matrix->getNonZeroCount(), 2);
    EXPECT_LT(matrix->getNonZeroCount(), 100); // Much less than full matrix
}
