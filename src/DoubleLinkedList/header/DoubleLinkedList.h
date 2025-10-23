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

// Template implementation
template<typename T>
Coruh::DataStructures::DoubleLinkedList<T>::DoubleLinkedList() : head(nullptr), tail(nullptr), size_(0) {}

template<typename T>
Coruh::DataStructures::DoubleLinkedList<T>::~DoubleLinkedList()
{
    clear();
}

template<typename T>
void Coruh::DataStructures::DoubleLinkedList<T>::append(const T& value)
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
void Coruh::DataStructures::DoubleLinkedList<T>::prepend(const T& value)
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
void Coruh::DataStructures::DoubleLinkedList<T>::insert(size_t index, const T& value)
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
void Coruh::DataStructures::DoubleLinkedList<T>::remove(size_t index)
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
void Coruh::DataStructures::DoubleLinkedList<T>::clear()
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
T& Coruh::DataStructures::DoubleLinkedList<T>::get(size_t index)
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
const T& Coruh::DataStructures::DoubleLinkedList<T>::get(size_t index) const
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
T& Coruh::DataStructures::DoubleLinkedList<T>::operator[](size_t index)
{
    return get(index);
}

template<typename T>
const T& Coruh::DataStructures::DoubleLinkedList<T>::operator[](size_t index) const
{
    return get(index);
}

template<typename T>
size_t Coruh::DataStructures::DoubleLinkedList<T>::getSize() const
{
    return size_;
}

template<typename T>
bool Coruh::DataStructures::DoubleLinkedList<T>::isEmpty() const
{
    return size_ == 0;
}

template<typename T>
void Coruh::DataStructures::DoubleLinkedList<T>::print() const
{
    Node* current = head;
    while (current) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

#endif // DOUBLE_LINKED_LIST_H