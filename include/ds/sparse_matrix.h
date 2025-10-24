/**
 * @file sparse_matrix.h
 * @brief Seyrek matris veri yapısı implementasyonları
 * @author Mustafa Yıldırım
 * @date 2025
 * @version 1.0
 */

#pragma once
#include <cstddef>
#include "ds/hash_table.h"

namespace ds {

/**
 * @brief Hash tablosu tabanlı seyrek matris
 * @tparam T Eleman türü
 * 
 * Bu sınıf, hash tablosu kullanarak seyrek matris implementasyonu sağlar.
 * Koordinatları 64-bit composite key olarak saklar (r<<32 | c).
 */
template <typename T>
class SparseMatrix {
    /**
     * @brief Satır ve sütun indekslerini 64-bit key'e dönüştürür
     * @param r Satır indeksi
     * @param c Sütun indeksi
     * @return 64-bit composite key
     */
    static inline long long key(std::size_t r, std::size_t c){ 
        return (static_cast<long long>(r) << 32) | static_cast<long long>(c); 
    }
    
    HashTable<long long, T> data_;  ///< Koordinat-eleman çiftlerini tutan hash tablosu
    std::size_t rows_;              ///< Matris satır sayısı
    std::size_t cols_;              ///< Matris sütun sayısı
    
public:
    /**
     * @brief Seyrek matris oluşturur
     * @param rows Satır sayısı
     * @param cols Sütun sayısı
     */
    SparseMatrix(std::size_t rows, std::size_t cols): data_(64), rows_(rows), cols_(cols) {}
    
    /**
     * @brief Belirtilen koordinata eleman atar
     * @param r Satır indeksi
     * @param c Sütun indeksi
     * @param v Atanacak değer
     */
    void set(std::size_t r, std::size_t c, const T& v){ 
        data_.insert(key(r,c), v); 
    }
    
    /**
     * @brief Belirtilen koordinattaki elemanı okur
     * @param r Satır indeksi
     * @param c Sütun indeksi
     * @return Elemanın pointer'ı, yoksa nullptr
     */
    const T* get(std::size_t r, std::size_t c) const { 
        return data_.find(key(r,c)); 
    }
    
    /**
     * @brief Sıfır olmayan eleman sayısını döndürür
     * @return Sıfır olmayan eleman sayısı
     */
    std::size_t nonZeroCount() const { 
        return data_.size(); 
    }
    
    /**
     * @brief Matris satır sayısını döndürür
     * @return Satır sayısı
     */
    std::size_t rows() const { 
        return rows_; 
    }
    
    /**
     * @brief Matris sütun sayısını döndürür
     * @return Sütun sayısı
     */
    std::size_t cols() const { 
        return cols_; 
    }
};

} // namespace ds

