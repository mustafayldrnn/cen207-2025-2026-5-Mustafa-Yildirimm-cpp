/**
 * @file StackQueue.h
 * @brief Stack and Queue implementation
 */

#ifndef STACK_QUEUE_H
#define STACK_QUEUE_H

#include <vector>
#include <stdexcept>

namespace Coruh
{
    namespace DataStructures
    {
        template<typename T>
        class Stack
        {
        private:
            std::vector<T> data;

        public:
            Stack() = default;
            ~Stack() = default;
            
            // Stack operations
            void push(const T& value);
            void pop();
            T& top();
            const T& top() const;
            
            // Properties
            bool isEmpty() const;
            size_t size() const;
            
            // Utility
            void print() const;
        };

        template<typename T>
        class Queue
        {
        private:
            std::vector<T> data;
            size_t front_;
            size_t rear_;

        public:
            Queue();
            ~Queue() = default;
            
            // Queue operations
            void enqueue(const T& value);
            void dequeue();
            T& front();
            const T& front() const;
            
            // Properties
            bool isEmpty() const;
            size_t size() const;
            
            // Utility
            void print() const;
        };
    }
}

#include "StackQueue.cpp"

#endif // STACK_QUEUE_H