#pragma once
#include <cstddef>
#include "ds/hash_table.h"

namespace ds {

template <typename T>
class SparseMatrix {
    // Key as 64-bit composite r<<32 | c
    static inline long long key(std::size_t r, std::size_t c){ return (static_cast<long long>(r) << 32) | static_cast<long long>(c); }
    HashTable<long long, T> data_;
    std::size_t rows_, cols_;
public:
    SparseMatrix(std::size_t rows, std::size_t cols): data_(64), rows_(rows), cols_(cols) {}
    void set(std::size_t r, std::size_t c, const T& v){ data_.insert(key(r,c), v); }
    const T* get(std::size_t r, std::size_t c) const { return data_.find(key(r,c)); }
    std::size_t nonZeroCount() const { return data_.size(); }
    std::size_t rows() const { return rows_; }
    std::size_t cols() const { return cols_; }
};

} // namespace ds

