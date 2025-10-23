/**
 * @file DoubleLinkedList.cpp
 * @brief Double Linked List implementation
 */

#include "../header/DoubleLinkedList.h"
#include <iostream>

namespace Coruh
{
    namespace DataStructures
    {
        template<typename T>
        DoubleLinkedList<T>::DoubleLinkedList() : head(nullptr), tail(nullptr), size_(0) {}

        template<typename T>
        DoubleLinkedList<T>::~DoubleLinkedList()
        {
            clear();
        }

        template<typename T>
        void DoubleLinkedList<T>::append(const T& value)
        {
            Node* newNode = new Node(value);
            
            if (isEmpty()) {
                head = tail = newNode;
            } else {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
            size_++;
        }

        template<typename T>
        void DoubleLinkedList<T>::prepend(const T& value)
        {
            Node* newNode = new Node(value);
            
            if (isEmpty()) {
                head = tail = newNode;
            } else {
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            }
            size_++;
        }

        template<typename T>
        void DoubleLinkedList<T>::insert(size_t index, const T& value)
        {
            if (index > size_) {
                throw std::out_of_range("Index out of range");
            }
            
            if (index == 0) {
                prepend(value);
            } else if (index == size_) {
                append(value);
            } else {
                Node* newNode = new Node(value);
                Node* current = head;
                
                for (size_t i = 0; i < index; ++i) {
                    current = current->next;
                }
                
                newNode->next = current;
                newNode->prev = current->prev;
                current->prev->next = newNode;
                current->prev = newNode;
                size_++;
            }
        }

        template<typename T>
        void DoubleLinkedList<T>::remove(size_t index)
        {
            if (index >= size_) {
                throw std::out_of_range("Index out of range");
            }
            
            Node* current = head;
            for (size_t i = 0; i < index; ++i) {
                current = current->next;
            }
            
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }
            
            if (current->next) {
                current->next->prev = current->prev;
            } else {
                tail = current->prev;
            }
            
            delete current;
            size_--;
        }

        template<typename T>
        void DoubleLinkedList<T>::clear()
        {
            while (head) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
            head = tail = nullptr;
            size_ = 0;
        }

        template<typename T>
        T& DoubleLinkedList<T>::get(size_t index)
        {
            if (index >= size_) {
                throw std::out_of_range("Index out of range");
            }
            
            Node* current = head;
            for (size_t i = 0; i < index; ++i) {
                current = current->next;
            }
            return current->data;
        }

        template<typename T>
        const T& DoubleLinkedList<T>::get(size_t index) const
        {
            if (index >= size_) {
                throw std::out_of_range("Index out of range");
            }
            
            Node* current = head;
            for (size_t i = 0; i < index; ++i) {
                current = current->next;
            }
            return current->data;
        }

        template<typename T>
        T& DoubleLinkedList<T>::operator[](size_t index)
        {
            return get(index);
        }

        template<typename T>
        const T& DoubleLinkedList<T>::operator[](size_t index) const
        {
            return get(index);
        }

        template<typename T>
        size_t DoubleLinkedList<T>::getSize() const
        {
            return size_;
        }

        template<typename T>
        bool DoubleLinkedList<T>::isEmpty() const
        {
            return size_ == 0;
        }

        template<typename T>
        void DoubleLinkedList<T>::print() const
        {
            Node* current = head;
            while (current) {
                std::cout << current->data << " ";
                current = current->next;
            }
            std::cout << std::endl;
        }
    }
}