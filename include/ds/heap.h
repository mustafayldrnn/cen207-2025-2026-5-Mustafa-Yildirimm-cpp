/**
 * @file heap.h
 * @brief Binary heap veri yapısı implementasyonları
 * @author Mustafa Yıldırım
 * @date 2025
 * @version 1.0
 */

#pragma once
#include <vector>
#include <functional>

namespace ds {

/**
 * @brief Manuel implementasyonlu binary heap
 * @tparam T Eleman türü
 * @tparam Compare Karşılaştırma fonksiyonu (varsayılan: std::less<T>)
 * 
 * Bu sınıf, heap özelliklerini manuel olarak implement eder.
 * Sift-up ve sift-down algoritmalarını kullanır.
 */
template <typename T, typename Compare = std::less<T>>
class BinaryHeap {
    std::vector<T> a_;  ///< Heap elemanlarını tutan vektör
    Compare cmp_{};     ///< Karşılaştırma fonksiyonu
    
    /**
     * @brief Elemanı yukarı doğru sıralar (sift-up)
     * @param i Sıralanacak elemanın indeksi
     */
    void sift_up(std::size_t i){
        while (i>0){ 
            std::size_t p=(i-1)/2; 
            if (!cmp_(a_[p], a_[i])) break; 
            std::swap(a_[p], a_[i]); 
            i=p; 
        }
    }
    
    /**
     * @brief Elemanı aşağı doğru sıralar (sift-down)
     * @param i Sıralanacak elemanın indeksi
     */
    void sift_down(std::size_t i){
        std::size_t n = a_.size();
        while(true){ 
            std::size_t l=2*i+1, r=2*i+2, m=i; 
            if (l<n && cmp_(a_[m], a_[l])) m=l; 
            if (r<n && cmp_(a_[m], a_[r])) m=r; 
            if (m==i) break; 
            std::swap(a_[i], a_[m]); 
            i=m; 
        }
    }
    
public:
    /**
     * @brief Heap'in boş olup olmadığını kontrol eder
     * @return true eğer heap boşsa
     */
    bool empty() const { return a_.empty(); }
    
    /**
     * @brief Heap'teki eleman sayısını döndürür
     * @return Eleman sayısı
     */
    std::size_t size() const { return a_.size(); }
    
    /**
     * @brief Heap'in en üstündeki elemanı döndürür
     * @return En üstteki elemanın referansı
     * @pre Heap boş olmamalıdır
     */
    const T& top() const { return a_.front(); }
    
    /**
     * @brief Heap'e yeni eleman ekler
     * @param v Eklenecek eleman
     */
    void push(const T& v){ 
        a_.push_back(v); 
        sift_up(a_.size()-1); 
    }
    
    /**
     * @brief Heap'in en üstündeki elemanı çıkarır
     * @pre Heap boş olmamalıdır
     */
    void pop(){ 
        std::swap(a_.front(), a_.back()); 
        a_.pop_back(); 
        if(!a_.empty()) sift_down(0); 
    }
    
    /**
     * @brief Heap'i sıralı dizi olarak döndürür (heap sort)
     * @return Sıralı eleman dizisi
     * 
     * Bu fonksiyon heap'i bozmadan sıralı bir kopyasını döndürür.
     * Heap sort algoritması kullanır.
     */
    std::vector<T> heap_sort_copy() const { 
        auto b=a_; 
        std::vector<T> out; 
        out.reserve(b.size()); 
        auto cmp=cmp_; 
        auto sift_down=[&](std::size_t i){ 
            std::size_t n=b.size(); 
            while(true){ 
                std::size_t l=2*i+1,r=2*i+2,m=i; 
                if(l<n&&cmp(b[m],b[l])) m=l; 
                if(r<n&&cmp(b[m],b[r])) m=r; 
                if(m==i) break; 
                std::swap(b[i],b[m]); 
                i=m; 
            }
        }; 
        for (std::size_t i=b.size()/2;i-->0;) sift_down(i); 
        while(!b.empty()){ 
            std::swap(b.front(), b.back()); 
            out.push_back(b.back()); 
            b.pop_back(); 
            if(!b.empty()) sift_down(0);
        } 
        return out; 
    }
};

} // namespace ds

