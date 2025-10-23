/**
 * @file StackQueue.cpp
 * @brief Stack and Queue implementation
 */

#include "../header/StackQueue.h"
#include <iostream>

namespace Coruh
{
    namespace DataStructures
    {
        // Stack Implementation
        template<typename T>
        void Stack<T>::push(const T& value)
        {
            data.push_back(value);
        }

        template<typename T>
        void Stack<T>::pop()
        {
            if (isEmpty()) {
                throw std::runtime_error("Stack is empty");
            }
            data.pop_back();
        }

        template<typename T>
        T& Stack<T>::top()
        {
            if (isEmpty()) {
                throw std::runtime_error("Stack is empty");
            }
            return data.back();
        }

        template<typename T>
        const T& Stack<T>::top() const
        {
            if (isEmpty()) {
                throw std::runtime_error("Stack is empty");
            }
            return data.back();
        }

        template<typename T>
        bool Stack<T>::isEmpty() const
        {
            return data.empty();
        }

        template<typename T>
        size_t Stack<T>::size() const
        {
            return data.size();
        }

        template<typename T>
        void Stack<T>::print() const
        {
            for (auto it = data.rbegin(); it != data.rend(); ++it) {
                std::cout << *it << " ";
            }
            std::cout << std::endl;
        }

        // Queue Implementation
        template<typename T>
        Queue<T>::Queue() : front_(0), rear_(0) {}

        template<typename T>
        void Queue<T>::enqueue(const T& value)
        {
            data.push_back(value);
            rear_++;
        }

        template<typename T>
        void Queue<T>::dequeue()
        {
            if (isEmpty()) {
                throw std::runtime_error("Queue is empty");
            }
            front_++;
        }

        template<typename T>
        T& Queue<T>::front()
        {
            if (isEmpty()) {
                throw std::runtime_error("Queue is empty");
            }
            return data[front_];
        }

        template<typename T>
        const T& Queue<T>::front() const
        {
            if (isEmpty()) {
                throw std::runtime_error("Queue is empty");
            }
            return data[front_];
        }

        template<typename T>
        bool Queue<T>::isEmpty() const
        {
            return front_ >= rear_;
        }

        template<typename T>
        size_t Queue<T>::size() const
        {
            return rear_ - front_;
        }

        template<typename T>
        void Queue<T>::print() const
        {
            for (size_t i = front_; i < rear_; ++i) {
                std::cout << data[i] << " ";
            }
            std::cout << std::endl;
        }
    }
}