/**
 * @file Heap.h
 * @brief Heap implementation
 */

#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <stdexcept>
#include <functional>

namespace Coruh
{
    namespace DataStructures
    {
        template<typename T>
        class Heap
        {
        private:
            std::vector<T> data;
            std::function<bool(const T&, const T&)> compare;
            
            size_t parent(size_t index) const;
            size_t leftChild(size_t index) const;
            size_t rightChild(size_t index) const;
            void heapifyUp(size_t index);
            void heapifyDown(size_t index);

        public:
            Heap(std::function<bool(const T&, const T&)> comp = std::less<T>());
            ~Heap() = default;
            
            // Basic operations
            void insert(const T& value);
            void remove();
            T& top();
            const T& top() const;
            
            // Properties
            bool isEmpty() const;
            size_t size() const;
            
            // Utility
            void print() const;
        };
    }
}

// Template implementation is in the header file

#endif // HEAP_H