/**
 * @file DoubleLinkedList_test.cpp
 * @brief Unit tests for Double Linked List
 */

#include <gtest/gtest.h>
#include "../../DoubleLinkedList/header/DoubleLinkedList.h"

using namespace Coruh::DataStructures;

class DoubleLinkedListTest : public ::testing::Test {
protected:
    void SetUp() override {
        list = new DoubleLinkedList<std::string>();
    }
    
    void TearDown() override {
        delete list;
    }
    
    DoubleLinkedList<std::string>* list;
};

TEST_F(DoubleLinkedListTest, EmptyList) {
    EXPECT_TRUE(list->isEmpty());
    EXPECT_EQ(list->getSize(), 0);
}

TEST_F(DoubleLinkedListTest, AppendElement) {
    list->append("first");
    EXPECT_FALSE(list->isEmpty());
    EXPECT_EQ(list->getSize(), 1);
    EXPECT_EQ(list->get(0), "first");
}

TEST_F(DoubleLinkedListTest, PrependElement) {
    list->append("second");
    list->prepend("first");
    EXPECT_EQ(list->getSize(), 2);
    EXPECT_EQ(list->get(0), "first");
    EXPECT_EQ(list->get(1), "second");
}

TEST_F(DoubleLinkedListTest, InsertAtPosition) {
    list->append("first");
    list->append("third");
    list->insert(1, "second");
    
    EXPECT_EQ(list->getSize(), 3);
    EXPECT_EQ(list->get(0), "first");
    EXPECT_EQ(list->get(1), "second");
    EXPECT_EQ(list->get(2), "third");
}

TEST_F(DoubleLinkedListTest, RemoveElement) {
    list->append("first");
    list->append("second");
    list->append("third");
    
    EXPECT_TRUE(list->remove(1));
    EXPECT_EQ(list->getSize(), 2);
    EXPECT_EQ(list->get(0), "first");
    EXPECT_EQ(list->get(1), "third");
}

TEST_F(DoubleLinkedListTest, Navigation) {
    list->append("page1");
    list->append("page2");
    list->append("page3");
    
    EXPECT_EQ(list->getCurrent(), "page3");
    EXPECT_TRUE(list->canMoveBackward());
    EXPECT_FALSE(list->canMoveForward());
    
    EXPECT_TRUE(list->moveBackward());
    EXPECT_EQ(list->getCurrent(), "page2");
    
    EXPECT_TRUE(list->moveBackward());
    EXPECT_EQ(list->getCurrent(), "page1");
    
    EXPECT_FALSE(list->canMoveBackward());
    EXPECT_TRUE(list->canMoveForward());
}

TEST_F(DoubleLinkedListTest, EdgeCases) {
    // Single element
    list->append("single");
    EXPECT_EQ(list->getCurrent(), "single");
    EXPECT_FALSE(list->canMoveBackward());
    EXPECT_FALSE(list->canMoveForward());
    
    // Remove single element
    EXPECT_TRUE(list->remove(0));
    EXPECT_TRUE(list->isEmpty());
}

TEST_F(DoubleLinkedListTest, ClearList) {
    list->append("first");
    list->append("second");
    list->clear();
    
    EXPECT_TRUE(list->isEmpty());
    EXPECT_EQ(list->getSize(), 0);
}

TEST_F(DoubleLinkedListTest, OutOfBounds) {
    EXPECT_THROW(list->get(0), std::out_of_range);
    EXPECT_THROW(list->get(5), std::out_of_range);
    
    list->append("test");
    EXPECT_THROW(list->get(1), std::out_of_range);
}
