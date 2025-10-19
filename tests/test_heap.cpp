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

