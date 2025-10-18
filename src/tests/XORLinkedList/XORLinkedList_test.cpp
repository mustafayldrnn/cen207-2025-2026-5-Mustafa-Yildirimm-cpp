/**
 * @file XORLinkedList_test.cpp
 * @brief Unit tests for XOR Linked List
 */

#include <gtest/gtest.h>
#include "../../XORLinkedList/header/XORLinkedList.h"

using namespace Coruh::DataStructures;

class XORLinkedListTest : public ::testing::Test {
protected:
    void SetUp() override {
        list = new XORLinkedList<std::string>();
    }
    
    void TearDown() override {
        delete list;
    }
    
    XORLinkedList<std::string>* list;
};

TEST_F(XORLinkedListTest, EmptyList) {
    EXPECT_TRUE(list->isEmpty());
    EXPECT_EQ(list->getSize(), 0);
}

TEST_F(XORLinkedListTest, AppendElement) {
    list->append("first");
    EXPECT_FALSE(list->isEmpty());
    EXPECT_EQ(list->getSize(), 1);
    EXPECT_EQ(list->get(0), "first");
}

TEST_F(XORLinkedListTest, PrependElement) {
    list->append("second");
    list->prepend("first");
    EXPECT_EQ(list->getSize(), 2);
    EXPECT_EQ(list->get(0), "first");
    EXPECT_EQ(list->get(1), "second");
}

TEST_F(XORLinkedListTest, RemoveLast) {
    list->append("first");
    list->append("second");
    
    EXPECT_EQ(list->removeLast(), "second");
    EXPECT_EQ(list->getSize(), 1);
    EXPECT_EQ(list->get(0), "first");
}

TEST_F(XORLinkedListTest, RemoveFirst) {
    list->append("first");
    list->append("second");
    
    EXPECT_EQ(list->removeFirst(), "first");
    EXPECT_EQ(list->getSize(), 1);
    EXPECT_EQ(list->get(0), "second");
}

TEST_F(XORLinkedListTest, BidirectionalNavigation) {
    list->append("song1");
    list->append("song2");
    list->append("song3");
    
    // Test forward traversal
    EXPECT_EQ(list->get(0), "song1");
    EXPECT_EQ(list->get(1), "song2");
    EXPECT_EQ(list->get(2), "song3");
}

TEST_F(XORLinkedListTest, MemoryEfficiency) {
    // Add multiple elements
    for (int i = 0; i < 100; ++i) {
        list->append("song" + std::to_string(i));
    }
    
    EXPECT_EQ(list->getSize(), 100);
    EXPECT_EQ(list->get(0), "song0");
    EXPECT_EQ(list->get(99), "song99");
}

TEST_F(XORLinkedListTest, EdgeCases) {
    // Single element
    list->append("single");
    EXPECT_EQ(list->removeFirst(), "single");
    EXPECT_TRUE(list->isEmpty());
    
    // Remove from empty list
    EXPECT_THROW(list->removeFirst(), std::runtime_error);
    EXPECT_THROW(list->removeLast(), std::runtime_error);
}

TEST_F(XORLinkedListTest, ClearList) {
    list->append("first");
    list->append("second");
    list->clear();
    
    EXPECT_TRUE(list->isEmpty());
    EXPECT_EQ(list->getSize(), 0);
}

TEST_F(XORLinkedListTest, OutOfBounds) {
    EXPECT_THROW(list->get(0), std::out_of_range);
    
    list->append("test");
    EXPECT_THROW(list->get(1), std::out_of_range);
}
