/**
 * @file hash_table.h
 * @brief Kapalı adreslemeli hash tablosu implementasyonu
 * @author Mustafa Yıldırım
 * @date 2025
 * @version 1.0
 */

#pragma once
#include <vector>
#include <optional>
#include <functional>
#include <stdexcept>

namespace ds {

/**
 * @brief Hash tablosundaki slot durumlarını belirten enum
 */
enum class SlotState { 
    Empty,      ///< Slot boş
    Occupied,   ///< Slot dolu
    Deleted     ///< Slot silinmiş (lazy deletion)
};

/**
 * @brief Kapalı adreslemeli hash tablosu implementasyonu
 * @tparam K Anahtar türü
 * @tparam V Değer türü
 * 
 * Bu sınıf, kapalı adresleme (closed addressing) tekniği kullanarak
 * hash tablosu implementasyonu sağlar. Linear probing ile çakışma çözümü yapar.
 */
template <typename K, typename V>
class HashTable {
    /**
     * @brief Hash tablosundaki her bir girişi temsil eden yapı
     */
    struct Entry { 
        K key;                          ///< Anahtar
        V value;                        ///< Değer
        SlotState state = SlotState::Empty;  ///< Slot durumu
    };
    
    std::vector<Entry> table_;          ///< Hash tablosu
    std::size_t count_ = 0;             ///< Mevcut eleman sayısı
    float max_load_ = 0.7f;             ///< Maksimum yük faktörü
    std::hash<K> hasher_{};             ///< Hash fonksiyonu

    /**
     * @brief Anahtar için hash indeksini hesaplar
     * @param k Anahtar
     * @return Hash indeksi
     */
    std::size_t idx(const K& k) const { return hasher_(k) & (table_.size() - 1); }
    
    /**
     * @brief Tabloyu yeniden boyutlandırır ve elemanları yeniden yerleştirir
     * @param new_cap Yeni kapasite
     */
    void rehash(std::size_t new_cap){
        std::vector<Entry> old = std::move(table_);
        table_.assign(new_cap, Entry{}); count_ = 0;
        for (auto& e : old){ if (e.state == SlotState::Occupied) insert(e.key, e.value); }
    }
    
    /**
     * @brief Yük faktörünü kontrol eder ve gerekirse rehash yapar
     */
    void ensure(){ if (count_ + 1 > static_cast<std::size_t>(max_load_ * table_.size())) rehash(table_.size()<<1); }

public:
    /**
     * @brief Hash tablosu oluşturur
     * @param cap Başlangıç kapasitesi (varsayılan: 16)
     * 
     * Kapasite 2'nin kuvveti olacak şekilde ayarlanır.
     */
    explicit HashTable(std::size_t cap = 16){ std::size_t c=1; while(c<cap) c<<=1; table_.assign(c, Entry{}); }
    
    /**
     * @brief Tablodaki eleman sayısını döndürür
     * @return Eleman sayısı
     */
    std::size_t size() const { return count_; }
    
    /**
     * @brief Tablonun boş olup olmadığını kontrol eder
     * @return true eğer tablo boşsa
     */
    bool empty() const { return count_==0; }

    /**
     * @brief Anahtar-değer çifti ekler veya günceller
     * @param k Anahtar
     * @param v Değer
     * @return true eğer yeni eleman eklendiyse, false eğer güncellendiyse
     */
    bool insert(const K& k, const V& v){ ensure(); std::size_t i = idx(k); std::size_t first_del = table_.size();
        while(true){ auto& e = table_[i]; if (e.state == SlotState::Empty){ if (first_del != table_.size()) { table_[first_del] = {k,v,SlotState::Occupied}; } else { e = {k,v,SlotState::Occupied}; } ++count_; return true; }
            if (e.state == SlotState::Deleted){ if (first_del == table_.size()) first_del = i; }
            else if (e.key == k){ e.value = v; return false; }
            i = (i + 1) & (table_.size()-1);
        }
    }

    /**
     * @brief Anahtar ile değer arar
     * @param k Aranacak anahtar
     * @return Değerin pointer'ı, bulunamazsa nullptr
     */
    V* find(const K& k){ std::size_t i = idx(k); while(true){ auto& e = table_[i]; if (e.state == SlotState::Empty) return nullptr; if (e.state == SlotState::Occupied && e.key == k) return &e.value; i = (i + 1) & (table_.size()-1);} }
    
    /**
     * @brief Anahtar ile değer arar (const versiyonu)
     * @param k Aranacak anahtar
     * @return Değerin const pointer'ı, bulunamazsa nullptr
     */
    const V* find(const K& k) const { return const_cast<HashTable*>(this)->find(k); }
    
    /**
     * @brief Anahtarın tabloda olup olmadığını kontrol eder
     * @param k Kontrol edilecek anahtar
     * @return true eğer anahtar bulunursa
     */
    bool contains(const K& k) const { return find(k) != nullptr; }
    
    /**
     * @brief Anahtarı tablodan siler
     * @param k Silinecek anahtar
     * @return true eğer anahtar bulunup silindiyse
     */
    bool erase(const K& k){ std::size_t i = idx(k); while(true){ auto& e = table_[i]; if (e.state == SlotState::Empty) return false; if (e.state == SlotState::Occupied && e.key == k){ e.state = SlotState::Deleted; --count_; return true; } i = (i + 1) & (table_.size()-1);} }
};

} // namespace ds

