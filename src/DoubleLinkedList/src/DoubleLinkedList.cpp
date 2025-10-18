#include "../header/DoubleLinkedList.h"
#include <iostream>
#include <stdexcept>

using namespace Coruh::DataStructures;

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList() : head(nullptr), tail(nullptr), current(nullptr), size(0) {}

template<typename T>
DoubleLinkedList<T>::~DoubleLinkedList() {
    clear();
}

template<typename T>
void DoubleLinkedList<T>::append(const T& value) {
    auto newNode = std::make_shared<Node>(value);
    
    if (isEmpty()) {
        head = tail = current = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
}

template<typename T>
void DoubleLinkedList<T>::prepend(const T& value) {
    auto newNode = std::make_shared<Node>(value);
    
    if (isEmpty()) {
        head = tail = current = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    size++;
}

template<typename T>
bool DoubleLinkedList<T>::insert(size_t position, const T& value) {
    if (position > size) {
        return false;
    }
    
    if (position == 0) {
        prepend(value);
        return true;
    }
    
    if (position == size) {
        append(value);
        return true;
    }
    
    auto newNode = std::make_shared<Node>(value);
    auto current = head;
    
    for (size_t i = 0; i < position - 1; ++i) {
        current = current->next;
    }
    
    newNode->next = current->next;
    newNode->prev = current;
    current->next->prev = newNode;
    current->next = newNode;
    
    size++;
    return true;
}

template<typename T>
bool DoubleLinkedList<T>::remove(size_t position) {
    if (position >= size || isEmpty()) {
        return false;
    }
    
    if (size == 1) {
        head = tail = current = nullptr;
    } else if (position == 0) {
        head = head->next;
        head->prev = nullptr;
        if (current == head->prev) {
            current = head;
        }
    } else if (position == size - 1) {
        tail = tail->prev;
        tail->next = nullptr;
        if (current == tail->next) {
            current = tail;
        }
    } else {
        auto nodeToRemove = head;
        for (size_t i = 0; i < position; ++i) {
            nodeToRemove = nodeToRemove->next;
        }
        
        nodeToRemove->prev->next = nodeToRemove->next;
        nodeToRemove->next->prev = nodeToRemove->prev;
        
        if (current == nodeToRemove) {
            current = nodeToRemove->next;
        }
    }
    
    size--;
    return true;
}

template<typename T>
T DoubleLinkedList<T>::get(size_t position) const {
    if (position >= size) {
        throw std::out_of_range("Position out of range");
    }
    
    auto current = head;
    for (size_t i = 0; i < position; ++i) {
        current = current->next;
    }
    
    return current->data;
}

template<typename T>
T DoubleLinkedList<T>::getCurrent() const {
    if (!current) {
        throw std::runtime_error("No current element");
    }
    return current->data;
}

template<typename T>
bool DoubleLinkedList<T>::moveForward() {
    if (!current || !current->next) {
        return false;
    }
    current = current->next;
    return true;
}

template<typename T>
bool DoubleLinkedList<T>::moveBackward() {
    if (!current || !current->prev) {
        return false;
    }
    current = current->prev;
    return true;
}

template<typename T>
bool DoubleLinkedList<T>::canMoveForward() const {
    return current && current->next;
}

template<typename T>
bool DoubleLinkedList<T>::canMoveBackward() const {
    return current && current->prev;
}

template<typename T>
size_t DoubleLinkedList<T>::getSize() const {
    return size;
}

template<typename T>
bool DoubleLinkedList<T>::isEmpty() const {
    return size == 0;
}

template<typename T>
void DoubleLinkedList<T>::clear() {
    while (head) {
        head = head->next;
    }
    tail = current = nullptr;
    size = 0;
}

template<typename T>
void DoubleLinkedList<T>::display() const {
    auto current = head;
    std::cout << "List: ";
    while (current) {
        std::cout << current->data;
        if (current->next) {
            std::cout << " <-> ";
        }
        current = current->next;
    }
    std::cout << std::endl;
}

// Explicit template instantiation for common types
template class DoubleLinkedList<std::string>;
template class DoubleLinkedList<int>;
