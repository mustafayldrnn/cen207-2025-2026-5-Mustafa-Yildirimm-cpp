/**
 * @file SparseMatrix.h
 * @brief Sparse Matrix implementation
 */

#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include <unordered_map>
#include <stdexcept>

namespace Coruh
{
    namespace DataStructures
    {
        template<typename T>
        class SparseMatrix
        {
        private:
            std::unordered_map<size_t, std::unordered_map<size_t, T>> data;
            size_t rows_;
            size_t cols_;
            T defaultValue;

        public:
            SparseMatrix(size_t rows, size_t cols, const T& defaultVal = T{});
            ~SparseMatrix() = default;
            
            // Basic operations
            void set(size_t row, size_t col, const T& value);
            T get(size_t row, size_t col) const;
            
            // Properties
            size_t getRows() const;
            size_t getCols() const;
            size_t getNonZeroCount() const;
            
            // Utility
            void print() const;
            void clear();
        };
    }
}

#include "SparseMatrix.cpp"

#endif // SPARSE_MATRIX_H