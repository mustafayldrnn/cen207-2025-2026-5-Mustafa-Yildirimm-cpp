#include <gtest/gtest.h>
#include "ds/xor_linked_list.h"

TEST(XORLinkedList, InsertDeleteNavigate){
    ds::XORLinkedList<int> xl;
    xl.push_back(1); xl.push_back(2); xl.push_front(0);
    int forward[3]; int i=0; xl.for_each_forward([&](int v){ forward[i++]=v; return true; });
    EXPECT_EQ(forward[0],0); EXPECT_EQ(forward[1],1); EXPECT_EQ(forward[2],2);
    int backward[3]; i=0; xl.for_each_backward([&](int v){ backward[i++]=v; return true; });
    EXPECT_EQ(backward[0],2); EXPECT_EQ(backward[1],1); EXPECT_EQ(backward[2],0);
    EXPECT_TRUE(xl.remove_first(1));
    int after[2]; i=0; xl.for_each_forward([&](int v){ after[i++]=v; return true; });
    EXPECT_EQ(after[0],0); EXPECT_EQ(after[1],2);
}

TEST(XORLinkedList, SizeAndEmpty){
    ds::XORLinkedList<int> xl;
    EXPECT_TRUE(xl.empty());
    EXPECT_EQ(xl.size(), 0u);
    
    xl.push_back(10);
    EXPECT_FALSE(xl.empty());
    EXPECT_EQ(xl.size(), 1u);
    
    xl.push_front(20);
    EXPECT_EQ(xl.size(), 2u);
    
    xl.remove_first(10);
    EXPECT_EQ(xl.size(), 1u);
    
    xl.remove_first(20);
    EXPECT_TRUE(xl.empty());
    EXPECT_EQ(xl.size(), 0u);
}

TEST(XORLinkedList, PushFrontBack){
    ds::XORLinkedList<int> xl;
    xl.push_front(1);
    xl.push_front(2);
    xl.push_back(3);
    xl.push_back(4);
    
    EXPECT_EQ(xl.size(), 4u);
    
    // Forward traversal should be: 2, 1, 3, 4
    int forward[4]; int i = 0;
    xl.for_each_forward([&](int v){ forward[i++] = v; return true; });
    EXPECT_EQ(forward[0], 2);
    EXPECT_EQ(forward[1], 1);
    EXPECT_EQ(forward[2], 3);
    EXPECT_EQ(forward[3], 4);
    
    // Backward traversal should be: 4, 3, 1, 2
    int backward[4]; i = 0;
    xl.for_each_backward([&](int v){ backward[i++] = v; return true; });
    EXPECT_EQ(backward[0], 4);
    EXPECT_EQ(backward[1], 3);
    EXPECT_EQ(backward[2], 1);
    EXPECT_EQ(backward[3], 2);
}

TEST(XORLinkedList, RemoveFirst){
    ds::XORLinkedList<int> xl;
    xl.push_back(1);
    xl.push_back(2);
    xl.push_back(1); // Duplicate
    xl.push_back(3);
    
    EXPECT_EQ(xl.size(), 4u);
    
    // Remove first occurrence of 1
    EXPECT_TRUE(xl.remove_first(1));
    EXPECT_EQ(xl.size(), 3u);
    
    // Verify only first occurrence was removed
    int forward[3]; int i = 0;
    xl.for_each_forward([&](int v){ forward[i++] = v; return true; });
    EXPECT_EQ(forward[0], 2);
    EXPECT_EQ(forward[1], 1); // Second occurrence should still be there
    EXPECT_EQ(forward[2], 3);
}

TEST(XORLinkedList, RemoveNonExistent){
    ds::XORLinkedList<int> xl;
    xl.push_back(1);
    xl.push_back(2);
    
    EXPECT_FALSE(xl.remove_first(99)); // Non-existent element
    EXPECT_EQ(xl.size(), 2u); // Size should remain unchanged
}

TEST(XORLinkedList, LargeDataset){
    ds::XORLinkedList<int> xl;
    // Add 100 elements
    for(int i = 0; i < 100; ++i) {
        xl.push_back(i);
    }
    EXPECT_EQ(xl.size(), 100u);
    
    // Verify forward traversal
    int count = 0;
    xl.for_each_forward([&](int v){ 
        EXPECT_EQ(v, count++); 
        return true; 
    });
    EXPECT_EQ(count, 100);
    
    // Verify backward traversal
    count = 99;
    xl.for_each_backward([&](int v){ 
        EXPECT_EQ(v, count--); 
        return true; 
    });
    EXPECT_EQ(count, -1);
}

