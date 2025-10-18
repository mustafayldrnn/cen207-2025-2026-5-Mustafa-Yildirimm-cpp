/**
 * @file Heap.h
 * @brief Heap implementation for Priority Task Manager
 */

#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <functional>
#include <stdexcept>

namespace Coruh
{
    namespace DataStructures
    {
        /**
         * @class Heap
         * @brief Binary heap implementation for priority management
         */
        template<typename T>
        class Heap
        {
        private:
            std::vector<T> data;
            std::function<bool(const T&, const T&)> compare;
            bool isMaxHeap;
            
            /**
             * Get parent index
             */
            size_t parent(size_t index) const;
            
            /**
             * Get left child index
             */
            size_t leftChild(size_t index) const;
            
            /**
             * Get right child index
             */
            size_t rightChild(size_t index) const;
            
            /**
             * Heapify up
             */
            void heapifyUp(size_t index);
            
            /**
             * Heapify down
             */
            void heapifyDown(size_t index);
            
        public:
            /**
             * Constructor for max heap
             */
            Heap();
            
            /**
             * Constructor for min heap
             * @param isMinHeap true for min heap, false for max heap
             */
            explicit Heap(bool isMinHeap);
            
            /**
             * Constructor with custom comparator
             * @param comp Custom comparison function
             */
            explicit Heap(std::function<bool(const T&, const T&)> comp);
            
            /**
             * Insert element
             * @param value Value to insert
             */
            void insert(const T& value);
            
            /**
             * Extract top element
             * @return Top element
             */
            T extractTop();
            
            /**
             * Get top element without removing
             * @return Top element
             */
            T peek() const;
            
            /**
             * Check if heap is empty
             * @return true if empty
             */
            bool isEmpty() const;
            
            /**
             * Get heap size
             * @return Number of elements
             */
            size_t size() const;
            
            /**
             * Clear heap
             */
            void clear();
            
            /**
             * Check heap property
             * @return true if heap property is maintained
             */
            bool isHeapPropertyMaintained() const;
            
            /**
             * Display heap
             */
            void display() const;
        };
    }
}

#endif // HEAP_H
