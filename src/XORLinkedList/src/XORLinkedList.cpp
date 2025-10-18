#include "../header/XORLinkedList.h"
#include <iostream>
#include <stdexcept>

using namespace Coruh::DataStructures;

template<typename T>
XORLinkedList<T>::XORLinkedList() : head(nullptr), tail(nullptr), size(0) {}

template<typename T>
XORLinkedList<T>::~XORLinkedList() {
    clear();
}

template<typename T>
typename XORLinkedList<T>::XORNode* XORLinkedList<T>::xorPointers(XORNode* a, XORNode* b) const {
    return reinterpret_cast<XORNode*>(reinterpret_cast<uintptr_t>(a) ^ reinterpret_cast<uintptr_t>(b));
}

template<typename T>
void XORLinkedList<T>::append(const T& value) {
    XORNode* newNode = new XORNode(value);
    
    if (isEmpty()) {
        head = tail = newNode;
        newNode->both = nullptr;
    } else {
        tail->both = xorPointers(tail->both, newNode);
        newNode->both = tail;
        tail = newNode;
    }
    size++;
}

template<typename T>
void XORLinkedList<T>::prepend(const T& value) {
    XORNode* newNode = new XORNode(value);
    
    if (isEmpty()) {
        head = tail = newNode;
        newNode->both = nullptr;
    } else {
        head->both = xorPointers(newNode, head->both);
        newNode->both = head;
        head = newNode;
    }
    size++;
}

template<typename T>
T XORLinkedList<T>::removeLast() {
    if (isEmpty()) {
        throw std::runtime_error("Cannot remove from empty list");
    }
    
    T data = tail->data;
    
    if (size == 1) {
        delete tail;
        head = tail = nullptr;
    } else {
        XORNode* prev = traverseBackward(tail, nullptr);
        prev->both = xorPointers(prev->both, tail);
        delete tail;
        tail = prev;
    }
    
    size--;
    return data;
}

template<typename T>
T XORLinkedList<T>::removeFirst() {
    if (isEmpty()) {
        throw std::runtime_error("Cannot remove from empty list");
    }
    
    T data = head->data;
    
    if (size == 1) {
        delete head;
        head = tail = nullptr;
    } else {
        XORNode* next = traverseForward(head, nullptr);
        next->both = xorPointers(head, next->both);
        delete head;
        head = next;
    }
    
    size--;
    return data;
}

template<typename T>
T XORLinkedList<T>::get(size_t position) const {
    if (position >= size) {
        throw std::out_of_range("Position out of range");
    }
    
    XORNode* current = head;
    XORNode* prev = nullptr;
    
    for (size_t i = 0; i < position; ++i) {
        XORNode* next = traverseForward(current, prev);
        prev = current;
        current = next;
    }
    
    return current->data;
}

template<typename T>
size_t XORLinkedList<T>::getSize() const {
    return size;
}

template<typename T>
bool XORLinkedList<T>::isEmpty() const {
    return size == 0;
}

template<typename T>
void XORLinkedList<T>::clear() {
    while (!isEmpty()) {
        removeFirst();
    }
}

template<typename T>
void XORLinkedList<T>::displayForward() const {
    if (isEmpty()) {
        std::cout << "List is empty" << std::endl;
        return;
    }
    
    XORNode* current = head;
    XORNode* prev = nullptr;
    
    std::cout << "Forward: ";
    while (current) {
        std::cout << current->data;
        XORNode* next = traverseForward(current, prev);
        if (next) {
            std::cout << " -> ";
        }
        prev = current;
        current = next;
    }
    std::cout << std::endl;
}

template<typename T>
void XORLinkedList<T>::displayBackward() const {
    if (isEmpty()) {
        std::cout << "List is empty" << std::endl;
        return;
    }
    
    XORNode* current = tail;
    XORNode* next = nullptr;
    
    std::cout << "Backward: ";
    while (current) {
        std::cout << current->data;
        XORNode* prev = traverseBackward(current, next);
        if (prev) {
            std::cout << " -> ";
        }
        next = current;
        current = prev;
    }
    std::cout << std::endl;
}

template<typename T>
typename XORLinkedList<T>::XORNode* XORLinkedList<T>::traverseForward(XORNode* start, XORNode* prev) const {
    if (!start) return nullptr;
    return xorPointers(start->both, prev);
}

template<typename T>
typename XORLinkedList<T>::XORNode* XORLinkedList<T>::traverseBackward(XORNode* start, XORNode* next) const {
    if (!start) return nullptr;
    return xorPointers(start->both, next);
}

// Explicit template instantiation for common types
template class XORLinkedList<std::string>;
template class XORLinkedList<int>;
