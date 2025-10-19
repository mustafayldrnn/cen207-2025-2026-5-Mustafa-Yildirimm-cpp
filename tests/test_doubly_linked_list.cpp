#include <gtest/gtest.h>
#include "ds/doubly_linked_list.h"

TEST(DoublyLinkedList, InsertAndTraverse){
    ds::DoublyLinkedList<int> dll;
    EXPECT_TRUE(dll.empty());
    dll.push_back(1); dll.push_back(2); dll.push_front(0);
    int sum = 0; for (auto it=dll.begin(); it!=dll.end(); ++it) sum += *it;
    EXPECT_EQ(sum, 3);
    auto it = dll.begin(); ++it; dll.insert_after(it, 5); // after 1
    int arr[4]; int i=0; for (auto it2=dll.begin(); it2!=dll.end(); ++it2) arr[i++]=*it2;
    EXPECT_EQ(arr[0],0); EXPECT_EQ(arr[1],1); EXPECT_EQ(arr[2],5); EXPECT_EQ(arr[3],2);
    // erase middle
    auto it3 = dll.begin(); ++it3; dll.erase(it3);
    int arr2[3]; i=0; for (auto it4=dll.begin(); it4!=dll.end(); ++it4) arr2[i++]=*it4;
    EXPECT_EQ(arr2[0],0); EXPECT_EQ(arr2[1],5); EXPECT_EQ(arr2[2],2);
}

TEST(DoublyLinkedList, EdgeCases){
    ds::DoublyLinkedList<int> dll;
    // insert into empty after end behaves like push_front
    dll.insert_after(ds::DoublyLinkedList<int>::iterator(), 42);
    EXPECT_FALSE(dll.empty());
    auto it = dll.begin(); EXPECT_EQ(*it, 42);
}

