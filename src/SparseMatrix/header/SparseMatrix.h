/**
 * @file SparseMatrix.h
 * @brief Sparse Matrix implementation for Map-based Grid Application
 */

#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include <unordered_map>
#include <vector>
#include <iostream>

namespace Coruh
{
    namespace DataStructures
    {
        /**
         * @class SparseMatrix
         * @brief Sparse matrix for memory-efficient grid applications
         */
        template<typename T>
        class SparseMatrix
        {
        private:
            std::unordered_map<size_t, std::unordered_map<size_t, T>> data;
            size_t rows;
            size_t cols;
            T defaultValue;
            
            /**
             * Convert 2D coordinates to 1D key
             */
            size_t getKey(size_t row, size_t col) const;
            
        public:
            /**
             * Constructor
             * @param rows Number of rows
             * @param cols Number of columns
             * @param defaultValue Default value for empty cells
             */
            SparseMatrix(size_t rows, size_t cols, const T& defaultValue = T{});
            
            /**
             * Set value at specific position
             * @param row Row index
             * @param col Column index
             * @param value Value to set
             */
            void set(size_t row, size_t col, const T& value);
            
            /**
             * Get value at specific position
             * @param row Row index
             * @param col Column index
             * @return Value at position
             */
            T get(size_t row, size_t col) const;
            
            /**
             * Check if position has non-default value
             * @param row Row index
             * @param col Column index
             * @return true if has non-default value
             */
            bool hasValue(size_t row, size_t col) const;
            
            /**
             * Remove value at specific position
             * @param row Row index
             * @param col Column index
             */
            void remove(size_t row, size_t col);
            
            /**
             * Get number of non-zero elements
             * @return Count of non-default elements
             */
            size_t getNonZeroCount() const;
            
            /**
             * Get memory usage (approximate)
             * @return Memory usage in bytes
             */
            size_t getMemoryUsage() const;
            
            /**
             * Get all non-zero positions
             * @return Vector of (row, col, value) tuples
             */
            std::vector<std::tuple<size_t, size_t, T>> getAllNonZero() const;
            
            /**
             * Clear all values
             */
            void clear();
            
            /**
             * Display matrix (showing only non-zero values)
             */
            void display() const;
            
            /**
             * Get matrix dimensions
             * @return Pair of (rows, cols)
             */
            std::pair<size_t, size_t> getDimensions() const;
        };
    }
}

#endif // SPARSE_MATRIX_H
