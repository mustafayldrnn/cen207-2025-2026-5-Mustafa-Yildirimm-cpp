/**
 * @file Heap.cpp
 * @brief Heap implementation
 */

#include "../header/Heap.h"
#include <iostream>

namespace Coruh
{
    namespace DataStructures
    {
        template<typename T>
        Heap<T>::Heap(std::function<bool(const T&, const T&)> comp)
            : compare(comp) {}

        template<typename T>
        size_t Heap<T>::parent(size_t index) const
        {
            return (index - 1) / 2;
        }

        template<typename T>
        size_t Heap<T>::leftChild(size_t index) const
        {
            return 2 * index + 1;
        }

        template<typename T>
        size_t Heap<T>::rightChild(size_t index) const
        {
            return 2 * index + 2;
        }

        template<typename T>
        void Heap<T>::heapifyUp(size_t index)
        {
            while (index > 0) {
                size_t parentIndex = parent(index);
                if (compare(data[parentIndex], data[index])) {
                    break;
                }
                std::swap(data[index], data[parentIndex]);
                index = parentIndex;
            }
        }

        template<typename T>
        void Heap<T>::heapifyDown(size_t index)
        {
            while (true) {
                size_t left = leftChild(index);
                size_t right = rightChild(index);
                size_t largest = index;
                
                if (left < data.size() && compare(data[left], data[largest])) {
                    largest = left;
                }
                
                if (right < data.size() && compare(data[right], data[largest])) {
                    largest = right;
                }
                
                if (largest == index) {
                    break;
                }
                
                std::swap(data[index], data[largest]);
                index = largest;
            }
        }

        template<typename T>
        void Heap<T>::insert(const T& value)
        {
            data.push_back(value);
            heapifyUp(data.size() - 1);
        }

        template<typename T>
        void Heap<T>::remove()
        {
            if (isEmpty()) {
                throw std::runtime_error("Heap is empty");
            }
            
            data[0] = data.back();
            data.pop_back();
            
            if (!isEmpty()) {
                heapifyDown(0);
            }
        }

        template<typename T>
        T& Heap<T>::top()
        {
            if (isEmpty()) {
                throw std::runtime_error("Heap is empty");
            }
            return data[0];
        }

        template<typename T>
        const T& Heap<T>::top() const
        {
            if (isEmpty()) {
                throw std::runtime_error("Heap is empty");
            }
            return data[0];
        }

        template<typename T>
        bool Heap<T>::isEmpty() const
        {
            return data.empty();
        }

        template<typename T>
        size_t Heap<T>::size() const
        {
            return data.size();
        }

        template<typename T>
        void Heap<T>::print() const
        {
            for (const auto& item : data) {
                std::cout << item << " ";
            }
            std::cout << std::endl;
        }
    }
}