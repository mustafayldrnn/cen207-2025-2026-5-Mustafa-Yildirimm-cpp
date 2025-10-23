/**
 * @file SparseMatrix.cpp
 * @brief Sparse Matrix implementation
 */

#include "../header/SparseMatrix.h"
#include <iostream>

namespace Coruh
{
    namespace DataStructures
    {
        template<typename T>
        SparseMatrix<T>::SparseMatrix(size_t rows, size_t cols, const T& defaultVal)
            : rows_(rows), cols_(cols), defaultValue(defaultVal) {}

        template<typename T>
        void SparseMatrix<T>::set(size_t row, size_t col, const T& value)
        {
            if (row >= rows_ || col >= cols_) {
                throw std::out_of_range("Index out of range");
            }
            
            if (value == defaultValue) {
                // Remove the element if it's the default value
                if (data.find(row) != data.end()) {
                    data[row].erase(col);
                    if (data[row].empty()) {
                        data.erase(row);
                    }
                }
            } else {
                data[row][col] = value;
            }
        }

        template<typename T>
        T SparseMatrix<T>::get(size_t row, size_t col) const
        {
            if (row >= rows_ || col >= cols_) {
                throw std::out_of_range("Index out of range");
            }
            
            auto rowIt = data.find(row);
            if (rowIt != data.end()) {
                auto colIt = rowIt->second.find(col);
                if (colIt != rowIt->second.end()) {
                    return colIt->second;
                }
            }
            return defaultValue;
        }

        template<typename T>
        size_t SparseMatrix<T>::getRows() const
        {
            return rows_;
        }

        template<typename T>
        size_t SparseMatrix<T>::getCols() const
        {
            return cols_;
        }

        template<typename T>
        size_t SparseMatrix<T>::getNonZeroCount() const
        {
            size_t count = 0;
            for (const auto& row : data) {
                count += row.second.size();
            }
            return count;
        }

        template<typename T>
        void SparseMatrix<T>::print() const
        {
            for (size_t i = 0; i < rows_; ++i) {
                for (size_t j = 0; j < cols_; ++j) {
                    std::cout << get(i, j) << " ";
                }
                std::cout << std::endl;
            }
        }

        template<typename T>
        void SparseMatrix<T>::clear()
        {
            data.clear();
        }
    }
}