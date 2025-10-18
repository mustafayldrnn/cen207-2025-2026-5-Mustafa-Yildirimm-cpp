/**
 * @file StackQueue_test.cpp
 * @brief Unit tests for Stack and Queue
 */

#include <gtest/gtest.h>
#include "../../StackQueue/header/StackQueue.h"

using namespace Coruh::DataStructures;

class StackTest : public ::testing::Test {
protected:
    void SetUp() override {
        stack = new Stack<std::string>();
    }
    
    void TearDown() override {
        delete stack;
    }
    
    Stack<std::string>* stack;
};

class QueueTest : public ::testing::Test {
protected:
    void SetUp() override {
        queue = new Queue<std::string>();
    }
    
    void TearDown() override {
        delete queue;
    }
    
    Queue<std::string>* queue;
};

// Stack Tests
TEST_F(StackTest, EmptyStack) {
    EXPECT_TRUE(stack->isEmpty());
    EXPECT_EQ(stack->size(), 0);
}

TEST_F(StackTest, PushAndPop) {
    stack->push("first");
    EXPECT_FALSE(stack->isEmpty());
    EXPECT_EQ(stack->size(), 1);
    EXPECT_EQ(stack->top(), "first");
    
    EXPECT_EQ(stack->pop(), "first");
    EXPECT_TRUE(stack->isEmpty());
}

TEST_F(StackTest, LIFOOrder) {
    stack->push("first");
    stack->push("second");
    stack->push("third");
    
    EXPECT_EQ(stack->size(), 3);
    EXPECT_EQ(stack->pop(), "third");
    EXPECT_EQ(stack->pop(), "second");
    EXPECT_EQ(stack->pop(), "first");
    EXPECT_TRUE(stack->isEmpty());
}

TEST_F(StackTest, TopWithoutPop) {
    stack->push("test");
    EXPECT_EQ(stack->top(), "test");
    EXPECT_EQ(stack->size(), 1); // Size should not change
}

TEST_F(StackTest, PopFromEmpty) {
    EXPECT_THROW(stack->pop(), std::runtime_error);
    EXPECT_THROW(stack->top(), std::runtime_error);
}

TEST_F(StackTest, ClearStack) {
    stack->push("first");
    stack->push("second");
    stack->clear();
    
    EXPECT_TRUE(stack->isEmpty());
    EXPECT_EQ(stack->size(), 0);
}

// Queue Tests
TEST_F(QueueTest, EmptyQueue) {
    EXPECT_TRUE(queue->isEmpty());
    EXPECT_EQ(queue->size(), 0);
}

TEST_F(QueueTest, EnqueueAndDequeue) {
    queue->enqueue("first");
    EXPECT_FALSE(queue->isEmpty());
    EXPECT_EQ(queue->size(), 1);
    EXPECT_EQ(queue->front(), "first");
    
    EXPECT_EQ(queue->dequeue(), "first");
    EXPECT_TRUE(queue->isEmpty());
}

TEST_F(QueueTest, FIFOOrder) {
    queue->enqueue("first");
    queue->enqueue("second");
    queue->enqueue("third");
    
    EXPECT_EQ(queue->size(), 3);
    EXPECT_EQ(queue->dequeue(), "first");
    EXPECT_EQ(queue->dequeue(), "second");
    EXPECT_EQ(queue->dequeue(), "third");
    EXPECT_TRUE(queue->isEmpty());
}

TEST_F(QueueTest, FrontWithoutDequeue) {
    queue->enqueue("test");
    EXPECT_EQ(queue->front(), "test");
    EXPECT_EQ(queue->size(), 1); // Size should not change
}

TEST_F(QueueTest, DequeueFromEmpty) {
    EXPECT_THROW(queue->dequeue(), std::runtime_error);
    EXPECT_THROW(queue->front(), std::runtime_error);
}

TEST_F(QueueTest, ClearQueue) {
    queue->enqueue("first");
    queue->enqueue("second");
    queue->clear();
    
    EXPECT_TRUE(queue->isEmpty());
    EXPECT_EQ(queue->size(), 0);
}
