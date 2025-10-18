/**
 * @file StackQueue.h
 * @brief Stack and Queue implementation for Task Scheduler
 */

#ifndef STACK_QUEUE_H
#define STACK_QUEUE_H

#include <vector>
#include <queue>
#include <string>
#include <stdexcept>

namespace Coruh
{
    namespace DataStructures
    {
        /**
         * @class Stack
         * @brief Stack implementation for undo operations (LIFO)
         */
        template<typename T>
        class Stack
        {
        private:
            std::vector<T> data;
            
        public:
            /**
             * Push element onto stack
             * @param value Value to push
             */
            void push(const T& value);
            
            /**
             * Pop element from stack
             * @return Top element
             */
            T pop();
            
            /**
             * Get top element without removing
             * @return Top element
             */
            T top() const;
            
            /**
             * Check if stack is empty
             * @return true if empty
             */
            bool isEmpty() const;
            
            /**
             * Get stack size
             * @return Number of elements
             */
            size_t size() const;
            
            /**
             * Clear stack
             */
            void clear();
        };
        
        /**
         * @class Queue
         * @brief Queue implementation for task queue (FIFO)
         */
        template<typename T>
        class Queue
        {
        private:
            std::queue<T> data;
            
        public:
            /**
             * Enqueue element
             * @param value Value to enqueue
             */
            void enqueue(const T& value);
            
            /**
             * Dequeue element
             * @return Front element
             */
            T dequeue();
            
            /**
             * Get front element without removing
             * @return Front element
             */
            T front() const;
            
            /**
             * Check if queue is empty
             * @return true if empty
             */
            bool isEmpty() const;
            
            /**
             * Get queue size
             * @return Number of elements
             */
            size_t size() const;
            
            /**
             * Clear queue
             */
            void clear();
        };
    }
}

#endif // STACK_QUEUE_H
