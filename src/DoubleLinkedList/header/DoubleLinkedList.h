/**
 * @file DoubleLinkedList.h
 * @brief Double Linked List implementation
 */

#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include <stdexcept>

namespace Coruh
{
    namespace DataStructures
    {
        template<typename T>
        class DoubleLinkedList
        {
        private:
            struct Node
            {
                T data;
                Node* next;
                Node* prev;
                
                Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
            };
            
            Node* head;
            Node* tail;
            size_t size_;

        public:
            DoubleLinkedList();
            ~DoubleLinkedList();
            
            // Basic operations
            void append(const T& value);
            void prepend(const T& value);
            void insert(size_t index, const T& value);
            void remove(size_t index);
            void clear();
            
            // Access
            T& get(size_t index);
            const T& get(size_t index) const;
            T& operator[](size_t index);
            const T& operator[](size_t index) const;
            
            // Properties
            size_t getSize() const;
            bool isEmpty() const;
            
            // Utility
            void print() const;
        };
    }
}

#include "DoubleLinkedList.cpp"

#endif // DOUBLE_LINKED_LIST_H