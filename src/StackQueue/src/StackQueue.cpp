#include "../header/StackQueue.h"

using namespace Coruh::DataStructures;

// Stack Implementation
template<typename T>
void Stack<T>::push(const T& value) {
    data.push_back(value);
}

template<typename T>
T Stack<T>::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty");
    }
    
    T value = data.back();
    data.pop_back();
    return value;
}

template<typename T>
T Stack<T>::top() const {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty");
    }
    
    return data.back();
}

template<typename T>
bool Stack<T>::isEmpty() const {
    return data.empty();
}

template<typename T>
size_t Stack<T>::size() const {
    return data.size();
}

template<typename T>
void Stack<T>::clear() {
    data.clear();
}

// Queue Implementation
template<typename T>
void Queue<T>::enqueue(const T& value) {
    data.push(value);
}

template<typename T>
T Queue<T>::dequeue() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    
    T value = data.front();
    data.pop();
    return value;
}

template<typename T>
T Queue<T>::front() const {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    
    return data.front();
}

template<typename T>
bool Queue<T>::isEmpty() const {
    return data.empty();
}

template<typename T>
size_t Queue<T>::size() const {
    return data.size();
}

template<typename T>
void Queue<T>::clear() {
    while (!data.empty()) {
        data.pop();
    }
}

// Explicit template instantiation for common types
template class Stack<std::string>;
template class Stack<int>;
template class Queue<std::string>;
template class Queue<int>;
