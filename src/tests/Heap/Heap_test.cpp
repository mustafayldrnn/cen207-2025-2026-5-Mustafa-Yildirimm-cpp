/**
 * @file Heap_test.cpp
 * @brief Unit tests for Heap
 */

#include <gtest/gtest.h>
#include "../../Heap/header/Heap.h"

using namespace Coruh::DataStructures;

class HeapTest : public ::testing::Test {
protected:
    void SetUp() override {
        maxHeap = new Heap<int>(true);  // Max heap
        minHeap = new Heap<int>(false); // Min heap
    }
    
    void TearDown() override {
        delete maxHeap;
        delete minHeap;
    }
    
    Heap<int>* maxHeap;
    Heap<int>* minHeap;
};

TEST_F(HeapTest, EmptyHeap) {
    EXPECT_TRUE(maxHeap->isEmpty());
    EXPECT_EQ(maxHeap->size(), 0);
    EXPECT_TRUE(minHeap->isEmpty());
    EXPECT_EQ(minHeap->size(), 0);
}

TEST_F(HeapTest, MaxHeapInsertAndExtract) {
    maxHeap->insert(10);
    maxHeap->insert(5);
    maxHeap->insert(15);
    
    EXPECT_EQ(maxHeap->size(), 3);
    EXPECT_EQ(maxHeap->peek(), 15); // Max element should be at top
    
    EXPECT_EQ(maxHeap->extractTop(), 15);
    EXPECT_EQ(maxHeap->extractTop(), 10);
    EXPECT_EQ(maxHeap->extractTop(), 5);
    EXPECT_TRUE(maxHeap->isEmpty());
}

TEST_F(HeapTest, MinHeapInsertAndExtract) {
    minHeap->insert(10);
    minHeap->insert(5);
    minHeap->insert(15);
    
    EXPECT_EQ(minHeap->size(), 3);
    EXPECT_EQ(minHeap->peek(), 5); // Min element should be at top
    
    EXPECT_EQ(minHeap->extractTop(), 5);
    EXPECT_EQ(minHeap->extractTop(), 10);
    EXPECT_EQ(minHeap->extractTop(), 15);
    EXPECT_TRUE(minHeap->isEmpty());
}

TEST_F(HeapTest, HeapPropertyMaintained) {
    maxHeap->insert(10);
    maxHeap->insert(5);
    maxHeap->insert(15);
    maxHeap->insert(3);
    maxHeap->insert(20);
    
    EXPECT_TRUE(maxHeap->isHeapPropertyMaintained());
}

TEST_F(HeapTest, PrioritySorting) {
    // Test max heap priority
    maxHeap->insert(5);
    maxHeap->insert(15);
    maxHeap->insert(10);
    maxHeap->insert(20);
    maxHeap->insert(1);
    
    std::vector<int> extracted;
    while (!maxHeap->isEmpty()) {
        extracted.push_back(maxHeap->extractTop());
    }
    
    // Should be in descending order
    for (size_t i = 1; i < extracted.size(); ++i) {
        EXPECT_GE(extracted[i-1], extracted[i]);
    }
}

TEST_F(HeapTest, MinHeapPrioritySorting) {
    // Test min heap priority
    minHeap->insert(15);
    minHeap->insert(5);
    minHeap->insert(20);
    minHeap->insert(10);
    minHeap->insert(1);
    
    std::vector<int> extracted;
    while (!minHeap->isEmpty()) {
        extracted.push_back(minHeap->extractTop());
    }
    
    // Should be in ascending order
    for (size_t i = 1; i < extracted.size(); ++i) {
        EXPECT_LE(extracted[i-1], extracted[i]);
    }
}

TEST_F(HeapTest, ExtractFromEmpty) {
    EXPECT_THROW(maxHeap->extractTop(), std::runtime_error);
    EXPECT_THROW(maxHeap->peek(), std::runtime_error);
}

TEST_F(HeapTest, ClearHeap) {
    maxHeap->insert(10);
    maxHeap->insert(5);
    maxHeap->clear();
    
    EXPECT_TRUE(maxHeap->isEmpty());
    EXPECT_EQ(maxHeap->size(), 0);
}

TEST_F(HeapTest, LargeHeap) {
    // Test with many elements
    for (int i = 0; i < 1000; ++i) {
        maxHeap->insert(i);
    }
    
    EXPECT_EQ(maxHeap->size(), 1000);
    EXPECT_TRUE(maxHeap->isHeapPropertyMaintained());
    
    // Extract all elements
    int lastExtracted = maxHeap->extractTop();
    while (!maxHeap->isEmpty()) {
        int current = maxHeap->extractTop();
        EXPECT_GE(lastExtracted, current);
        lastExtracted = current;
    }
}

TEST_F(HeapTest, CustomComparator) {
    // Test with custom comparator (min heap using max heap with negated values)
    auto customComp = [](const int& a, const int& b) { return a > b; };
    Heap<int> customHeap(customComp);
    
    customHeap.insert(10);
    customHeap.insert(5);
    customHeap.insert(15);
    
    EXPECT_EQ(customHeap.peek(), 15); // Should behave like max heap
}
