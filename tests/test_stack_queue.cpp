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

