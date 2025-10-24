#include <gtest/gtest.h>
#include "ds/stack.h"
#include "ds/queue.h"

TEST(StackQueue, StackLIFO){
    ds::Stack<int> st; st.push(1); st.push(2); st.push(3);
    EXPECT_EQ(st.top(), 3); st.pop(); EXPECT_EQ(st.top(), 2); st.pop(); EXPECT_EQ(st.top(), 1);
}

TEST(StackQueue, QueueFIFO){
    ds::Queue<int> q; q.enqueue(1); q.enqueue(2); q.enqueue(3);
    EXPECT_EQ(q.front(), 1); q.dequeue(); EXPECT_EQ(q.front(), 2); q.dequeue(); EXPECT_EQ(q.front(), 3);
}

TEST(StackQueue, StackSizeAndEmpty){
    ds::Stack<int> st;
    EXPECT_TRUE(st.empty());
    EXPECT_EQ(st.size(), 0u);
    
    st.push(10);
    EXPECT_FALSE(st.empty());
    EXPECT_EQ(st.size(), 1u);
    
    st.push(20);
    EXPECT_EQ(st.size(), 2u);
    
    st.pop();
    EXPECT_EQ(st.size(), 1u);
    
    st.pop();
    EXPECT_TRUE(st.empty());
    EXPECT_EQ(st.size(), 0u);
}

TEST(StackQueue, QueueSizeAndEmpty){
    ds::Queue<int> q;
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0u);
    
    q.enqueue(10);
    EXPECT_FALSE(q.empty());
    EXPECT_EQ(q.size(), 1u);
    
    q.enqueue(20);
    EXPECT_EQ(q.size(), 2u);
    
    q.dequeue();
    EXPECT_EQ(q.size(), 1u);
    
    q.dequeue();
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0u);
}

TEST(StackQueue, StackLargeDataset){
    ds::Stack<int> st;
    // Push 100 elements
    for(int i = 0; i < 100; ++i) {
        st.push(i);
    }
    EXPECT_EQ(st.size(), 100u);
    EXPECT_EQ(st.top(), 99);
    
    // Pop all elements
    for(int i = 99; i >= 0; --i) {
        EXPECT_EQ(st.top(), i);
        st.pop();
    }
    EXPECT_TRUE(st.empty());
}

TEST(StackQueue, QueueLargeDataset){
    ds::Queue<int> q;
    // Enqueue 100 elements
    for(int i = 0; i < 100; ++i) {
        q.enqueue(i);
    }
    EXPECT_EQ(q.size(), 100u);
    EXPECT_EQ(q.front(), 0);
    
    // Dequeue all elements
    for(int i = 0; i < 100; ++i) {
        EXPECT_EQ(q.front(), i);
        q.dequeue();
    }
    EXPECT_TRUE(q.empty());
}

