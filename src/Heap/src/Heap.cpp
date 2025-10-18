#include "../header/Heap.h"
#include <iostream>
#include <algorithm>

using namespace Coruh::DataStructures;

template<typename T>
Heap<T>::Heap() : isMaxHeap(true) {
    compare = [this](const T& a, const T& b) {
        return isMaxHeap ? (a > b) : (a < b);
    };
}

template<typename T>
Heap<T>::Heap(bool isMinHeap) : isMaxHeap(!isMinHeap) {
    compare = [this](const T& a, const T& b) {
        return isMaxHeap ? (a > b) : (a < b);
    };
}

template<typename T>
Heap<T>::Heap(std::function<bool(const T&, const T&)> comp) : compare(comp), isMaxHeap(true) {}

template<typename T>
size_t Heap<T>::parent(size_t index) const {
    return (index - 1) / 2;
}

template<typename T>
size_t Heap<T>::leftChild(size_t index) const {
    return 2 * index + 1;
}

template<typename T>
size_t Heap<T>::rightChild(size_t index) const {
    return 2 * index + 2;
}

template<typename T>
void Heap<T>::heapifyUp(size_t index) {
    if (index == 0) return;
    
    size_t parentIndex = parent(index);
    if (compare(data[index], data[parentIndex])) {
        std::swap(data[index], data[parentIndex]);
        heapifyUp(parentIndex);
    }
}

template<typename T>
void Heap<T>::heapifyDown(size_t index) {
    size_t left = leftChild(index);
    size_t right = rightChild(index);
    size_t top = index;
    
    if (left < data.size() && compare(data[left], data[top])) {
        top = left;
    }
    
    if (right < data.size() && compare(data[right], data[top])) {
        top = right;
    }
    
    if (top != index) {
        std::swap(data[index], data[top]);
        heapifyDown(top);
    }
}

template<typename T>
void Heap<T>::insert(const T& value) {
    data.push_back(value);
    heapifyUp(data.size() - 1);
}

template<typename T>
T Heap<T>::extractTop() {
    if (isEmpty()) {
        throw std::runtime_error("Heap is empty");
    }
    
    T top = data[0];
    data[0] = data.back();
    data.pop_back();
    
    if (!isEmpty()) {
        heapifyDown(0);
    }
    
    return top;
}

template<typename T>
T Heap<T>::peek() const {
    if (isEmpty()) {
        throw std::runtime_error("Heap is empty");
    }
    return data[0];
}

template<typename T>
bool Heap<T>::isEmpty() const {
    return data.empty();
}

template<typename T>
size_t Heap<T>::size() const {
    return data.size();
}

template<typename T>
void Heap<T>::clear() {
    data.clear();
}

template<typename T>
bool Heap<T>::isHeapPropertyMaintained() const {
    for (size_t i = 0; i < data.size(); ++i) {
        size_t left = leftChild(i);
        size_t right = rightChild(i);
        
        if (left < data.size() && !compare(data[i], data[left])) {
            return false;
        }
        
        if (right < data.size() && !compare(data[i], data[right])) {
            return false;
        }
    }
    return true;
}

template<typename T>
void Heap<T>::display() const {
    std::cout << "Heap: ";
    for (const auto& item : data) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

// Explicit template instantiation for common types
template class Heap<int>;
template class Heap<double>;
