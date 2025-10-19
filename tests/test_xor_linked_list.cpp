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

