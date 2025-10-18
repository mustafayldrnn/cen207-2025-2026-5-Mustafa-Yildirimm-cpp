/**
 * @file DoubleLinkedList.h
 * @brief Double Linked List implementation for Browser History System
 */

#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include <string>
#include <memory>

namespace Coruh
{
    namespace DataStructures
    {
        /**
         * @class DoubleLinkedList
         * @brief Double linked list implementation for browser history navigation
         */
        template<typename T>
        class DoubleLinkedList
        {
        private:
            struct Node
            {
                T data;
                std::shared_ptr<Node> next;
                std::shared_ptr<Node> prev;
                
                Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
            };
            
            std::shared_ptr<Node> head;
            std::shared_ptr<Node> tail;
            std::shared_ptr<Node> current; // Current position for navigation
            size_t size;
            
        public:
            /**
             * Constructor
             */
            DoubleLinkedList();
            
            /**
             * Destructor
             */
            ~DoubleLinkedList();
            
            /**
             * Add element to the end of the list
             * @param value Value to add
             */
            void append(const T& value);
            
            /**
             * Add element to the beginning of the list
             * @param value Value to add
             */
            void prepend(const T& value);
            
            /**
             * Insert element at specific position
             * @param position Position to insert
             * @param value Value to insert
             * @return true if successful
             */
            bool insert(size_t position, const T& value);
            
            /**
             * Remove element at specific position
             * @param position Position to remove
             * @return true if successful
             */
            bool remove(size_t position);
            
            /**
             * Get element at specific position
             * @param position Position to get
             * @return Element at position
             */
            T get(size_t position) const;
            
            /**
             * Get current element (for navigation)
             * @return Current element
             */
            T getCurrent() const;
            
            /**
             * Move to next element (forward navigation)
             * @return true if successful
             */
            bool moveForward();
            
            /**
             * Move to previous element (backward navigation)
             * @return true if successful
             */
            bool moveBackward();
            
            /**
             * Check if can move forward
             * @return true if can move forward
             */
            bool canMoveForward() const;
            
            /**
             * Check if can move backward
             * @return true if can move backward
             */
            bool canMoveBackward() const;
            
            /**
             * Get list size
             * @return Size of the list
             */
            size_t getSize() const;
            
            /**
             * Check if list is empty
             * @return true if empty
             */
            bool isEmpty() const;
            
            /**
             * Clear the list
             */
            void clear();
            
            /**
             * Display all elements
             */
            void display() const;
        };
    }
}

#endif // DOUBLE_LINKED_LIST_H
