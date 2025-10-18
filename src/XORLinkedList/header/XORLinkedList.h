/**
 * @file XORLinkedList.h
 * @brief XOR Linked List implementation for Memory-Efficient Playlist System
 */

#ifndef XOR_LINKED_LIST_H
#define XOR_LINKED_LIST_H

#include <string>
#include <cstdint>

namespace Coruh
{
    namespace DataStructures
    {
        /**
         * @class XORLinkedList
         * @brief XOR linked list for memory-efficient playlist system
         */
        template<typename T>
        class XORLinkedList
        {
        private:
            struct XORNode
            {
                T data;
                XORNode* both; // XOR of prev and next pointers
                
                XORNode(const T& value) : data(value), both(nullptr) {}
            };
            
            XORNode* head;
            XORNode* tail;
            size_t size;
            
            /**
             * XOR operation for pointers
             */
            XORNode* xorPointers(XORNode* a, XORNode* b) const;
            
        public:
            /**
             * Constructor
             */
            XORLinkedList();
            
            /**
             * Destructor
             */
            ~XORLinkedList();
            
            /**
             * Add element to the end
             * @param value Value to add
             */
            void append(const T& value);
            
            /**
             * Add element to the beginning
             * @param value Value to add
             */
            void prepend(const T& value);
            
            /**
             * Remove element from the end
             * @return Removed element
             */
            T removeLast();
            
            /**
             * Remove element from the beginning
             * @return Removed element
             */
            T removeFirst();
            
            /**
             * Get element at specific position
             * @param position Position to get
             * @return Element at position
             */
            T get(size_t position) const;
            
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
             * Display all elements (forward traversal)
             */
            void displayForward() const;
            
            /**
             * Display all elements (backward traversal)
             */
            void displayBackward() const;
            
            /**
             * Traverse forward from a given node
             * @param start Starting node
             * @param prev Previous node
             * @return Next node
             */
            XORNode* traverseForward(XORNode* start, XORNode* prev) const;
            
            /**
             * Traverse backward from a given node
             * @param start Starting node
             * @param next Next node
             * @return Previous node
             */
            XORNode* traverseBackward(XORNode* start, XORNode* next) const;
        };
    }
}

#endif // XOR_LINKED_LIST_H
