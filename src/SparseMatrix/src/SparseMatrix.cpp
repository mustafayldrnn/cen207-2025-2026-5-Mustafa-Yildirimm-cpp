#include "../header/SparseMatrix.h"
#include <stdexcept>

using namespace Coruh::DataStructures;

template<typename T>
SparseMatrix<T>::SparseMatrix(size_t rows, size_t cols, const T& defaultValue) 
    : rows(rows), cols(cols), defaultValue(defaultValue) {}

template<typename T>
size_t SparseMatrix<T>::getKey(size_t row, size_t col) const {
    return row * cols + col;
}

template<typename T>
void SparseMatrix<T>::set(size_t row, size_t col, const T& value) {
    if (row >= rows || col >= cols) {
        throw std::out_of_range("Position out of bounds");
    }
    
    if (value == defaultValue) {
        // Remove the value if it's the default
        remove(row, col);
    } else {
        data[row][col] = value;
    }
}

template<typename T>
T SparseMatrix<T>::get(size_t row, size_t col) const {
    if (row >= rows || col >= cols) {
        throw std::out_of_range("Position out of bounds");
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
bool SparseMatrix<T>::hasValue(size_t row, size_t col) const {
    if (row >= rows || col >= cols) {
        return false;
    }
    
    auto rowIt = data.find(row);
    if (rowIt != data.end()) {
        return rowIt->second.find(col) != rowIt->second.end();
    }
    
    return false;
}

template<typename T>
void SparseMatrix<T>::remove(size_t row, size_t col) {
    auto rowIt = data.find(row);
    if (rowIt != data.end()) {
        rowIt->second.erase(col);
        if (rowIt->second.empty()) {
            data.erase(rowIt);
        }
    }
}

template<typename T>
size_t SparseMatrix<T>::getNonZeroCount() const {
    size_t count = 0;
    for (const auto& row : data) {
        count += row.second.size();
    }
    return count;
}

template<typename T>
size_t SparseMatrix<T>::getMemoryUsage() const {
    size_t memory = 0;
    memory += sizeof(*this); // Base object size
    memory += data.size() * sizeof(size_t); // Row keys
    for (const auto& row : data) {
        memory += row.second.size() * (sizeof(size_t) + sizeof(T)); // Column keys and values
    }
    return memory;
}

template<typename T>
std::vector<std::tuple<size_t, size_t, T>> SparseMatrix<T>::getAllNonZero() const {
    std::vector<std::tuple<size_t, size_t, T>> result;
    
    for (const auto& row : data) {
        for (const auto& col : row.second) {
            result.emplace_back(row.first, col.first, col.second);
        }
    }
    
    return result;
}

template<typename T>
void SparseMatrix<T>::clear() {
    data.clear();
}

template<typename T>
void SparseMatrix<T>::display() const {
    std::cout << "Sparse Matrix (" << rows << "x" << cols << "):" << std::endl;
    std::cout << "Non-zero elements: " << getNonZeroCount() << std::endl;
    
    for (const auto& row : data) {
        for (const auto& col : row.second) {
            std::cout << "[" << row.first << "," << col.first << "] = " 
                      << col.second << std::endl;
        }
    }
}

template<typename T>
std::pair<size_t, size_t> SparseMatrix<T>::getDimensions() const {
    return {rows, cols};
}

// Explicit template instantiation for common types
template class SparseMatrix<int>;
template class SparseMatrix<double>;
template class SparseMatrix<std::string>;
