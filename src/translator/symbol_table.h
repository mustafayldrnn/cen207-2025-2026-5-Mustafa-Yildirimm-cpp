/**
 * @file symbol_table.h
 * @brief Basit sembol tablosu arabirimi
 * @author Mustafa Yıldırım
 * @date 2025
 * @version 1.0
 */
#pragma once
#include <string>
#include "ds/hash_table.h"

namespace translator {

/**
 * @brief İsim→değer eşlemesi yapan tablo
 * 
 * Bu sınıf, BASIC benzeri dildeki değişkenleri saklamak için
 * hash tablosu kullanır. Değişken tanımlama ve atama işlemlerini destekler.
 */
class SymbolTable {
    ds::HashTable<std::string, double> table_;  ///< Değişken isimlerini ve değerlerini tutan hash tablosu
    
public:
    /**
     * @brief Yeni değişken tanımı ekler veya üzerine yazar
     * @param name Değişken adı
     * @param value Değişken değeri
     * @return true eğer yeni tanım eklendiyse, false eğer güncellendiyse
     */
    bool define(const std::string& name, double value){ return table_.insert(name, value); }
    
    /**
     * @brief Var olan değişkene değer atar
     * @param name Değişken adı
     * @param value Atanacak değer
     * @return true eğer atama başarılıysa
     */
    bool assign(const std::string& name, double value){ return table_.insert(name, value); }
    
    /**
     * @brief Değişken adını arar ve değerinin adresini döndürür
     * @param name Aranacak değişken adı
     * @return Değerin const pointer'ı, bulunamazsa nullptr
     */
    const double* lookup(const std::string& name) const { return table_.find(name); }
};

} // namespace translator

