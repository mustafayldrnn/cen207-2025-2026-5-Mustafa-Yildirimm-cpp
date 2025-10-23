/**
 * @file StackQueue.h
 * @brief Stack and Queue implementation
 */

#ifndef STACK_QUEUE_H
#define STACK_QUEUE_H

#include <vector>
#include <stdexcept>

namespace Coruh
{
    namespace DataStructures
    {
        template<typename T>
        class Stack
        {
        private:
            std::vector<T> data;

        public:
            Stack() = default;
            ~Stack() = default;
            
            // Stack operations
            void push(const T& value);
            void pop();
            T& top();
            const T& top() const;
            
            // Properties
            bool isEmpty() const;
            size_t size() const;
            
            // Utility
            void print() const;
        };

        template<typename T>
        class Queue
        {
        private:
            std::vector<T> data;
            size_t front_;
            size_t rear_;

        public:
            Queue();
            ~Queue() = default;
            
            // Queue operations
            void enqueue(const T& value);
            void dequeue();
            T& front();
            const T& front() const;
            
            // Properties
            bool isEmpty() const;
            size_t size() const;
            
            // Utility
            void print() const;
        };
    }
}

// Template implementation
// Stack Implementation
template<typename T>
void Coruh::DataStructures::Stack<T>::push(const T& value)
{
    data.push_back(value);
}

template<typename T>
void Coruh::DataStructures::Stack<T>::pop()
{
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty");
    }
    data.pop_back();
}

template<typename T>
T& Coruh::DataStructures::Stack<T>::top()
{
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty");
    }
    return data.back();
}

template<typename T>
const T& Coruh::DataStructures::Stack<T>::top() const
{
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty");
    }
    return data.back();
}

template<typename T>
bool Coruh::DataStructures::Stack<T>::isEmpty() const
{
    return data.empty();
}

template<typename T>
size_t Coruh::DataStructures::Stack<T>::size() const
{
    return data.size();
}

template<typename T>
void Coruh::DataStructures::Stack<T>::print() const
{
    for (auto it = data.rbegin(); it != data.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

// Queue Implementation
template<typename T>
Coruh::DataStructures::Queue<T>::Queue() : front_(0), rear_(0) {}

template<typename T>
void Coruh::DataStructures::Queue<T>::enqueue(const T& value)
{
    data.push_back(value);
    rear_++;
}

template<typename T>
void Coruh::DataStructures::Queue<T>::dequeue()
{
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    front_++;
}

template<typename T>
T& Coruh::DataStructures::Queue<T>::front()
{
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    return data[front_];
}

template<typename T>
const T& Coruh::DataStructures::Queue<T>::front() const
{
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    return data[front_];
}

template<typename T>
bool Coruh::DataStructures::Queue<T>::isEmpty() const
{
    return front_ >= rear_;
}

template<typename T>
size_t Coruh::DataStructures::Queue<T>::size() const
{
    return rear_ - front_;
}

template<typename T>
void Coruh::DataStructures::Queue<T>::print() const
{
    for (size_t i = front_; i < rear_; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

#endif // STACK_QUEUE_H