#include <gtest/gtest.h>
#include "ds/heap.h"

TEST(BinaryHeap, PushPopOrder){
    ds::BinaryHeap<int> h; h.push(3); h.push(1); h.push(5); h.push(2);
    EXPECT_EQ(h.top(), 5); h.pop(); EXPECT_EQ(h.top(), 3); h.pop(); EXPECT_EQ(h.top(), 2);
}

TEST(BinaryHeap, HeapSort){
    ds::BinaryHeap<int> h; for (int v: {5,1,4,2,3}) h.push(v);
    auto sorted = h.heap_sort_copy();
    // For max-heap, heap_sort_copy returns descending
    ASSERT_EQ(sorted.size(), 5u);
    EXPECT_EQ(sorted[0], 5); EXPECT_EQ(sorted[1], 4); EXPECT_EQ(sorted[2], 3); EXPECT_EQ(sorted[3], 2); EXPECT_EQ(sorted[4], 1);
}

TEST(BinaryHeap, SizeAndEmpty){
    ds::BinaryHeap<int> h;
    EXPECT_TRUE(h.empty());
    EXPECT_EQ(h.size(), 0u);
    
    h.push(10);
    EXPECT_FALSE(h.empty());
    EXPECT_EQ(h.size(), 1u);
    
    h.push(20);
    EXPECT_EQ(h.size(), 2u);
    
    h.pop();
    EXPECT_EQ(h.size(), 1u);
    
    h.pop();
    EXPECT_TRUE(h.empty());
    EXPECT_EQ(h.size(), 0u);
}

TEST(BinaryHeap, MinHeap){
    ds::BinaryHeap<int, std::greater<int>> minHeap;
    minHeap.push(5); minHeap.push(1); minHeap.push(3); minHeap.push(2);
    EXPECT_EQ(minHeap.top(), 1);
    minHeap.pop();
    EXPECT_EQ(minHeap.top(), 2);
    minHeap.pop();
    EXPECT_EQ(minHeap.top(), 3);
}

TEST(BinaryHeap, LargeDataset){
    ds::BinaryHeap<int> h;
    // Add 100 elements
    for(int i = 0; i < 100; ++i) {
        h.push(i);
    }
    EXPECT_EQ(h.size(), 100u);
    EXPECT_EQ(h.top(), 99); // Max element
    
    // Test heap sort
    auto sorted = h.heap_sort_copy();
    EXPECT_EQ(sorted.size(), 100u);
    for(int i = 0; i < 100; ++i) {
        EXPECT_EQ(sorted[i], 99 - i);
    }
}

