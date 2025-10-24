/**
 * @file doubly_linked_list.h
 * @brief Basit, şablonlu çift yönlü bağlı liste
 * @author Mustafa Yıldırım
 * @date 2025
 * @version 1.0
 */
#pragma once
#include <cstddef>
#include <iterator>

namespace ds {

/**
 * @brief Çift yönlü bağlı liste kapsayıcısı
 * @tparam T Eleman tipi
 * 
 * Bu sınıf, çift yönlü bağlı liste veri yapısını implement eder.
 * Her düğüm, önceki ve sonraki düğümlere referans tutar.
 * Iterator desteği ile STL uyumlu erişim sağlar.
 */
template <typename T>
class DoublyLinkedList {
    /**
     * @brief Liste düğümü
     */
    struct Node { 
        T value;        ///< Düğümdeki değer
        Node* prev;     ///< Önceki düğüm pointer'ı
        Node* next;     ///< Sonraki düğüm pointer'ı
        
        /**
         * @brief Düğüm oluşturur
         * @param v Düğümde saklanacak değer
         */
        Node(const T& v): value(v), prev(nullptr), next(nullptr) {} 
    };
    
    Node* head_ = nullptr;      ///< Liste başı pointer'ı
    Node* tail_ = nullptr;      ///< Liste sonu pointer'ı
    std::size_t size_ = 0;      ///< Liste eleman sayısı

public:
    /**
     * @brief Varsayılan constructor
     */
    DoublyLinkedList() = default;
    
    /**
     * @brief Destructor - tüm düğümleri serbest bırakır
     */
    ~DoublyLinkedList() { clear(); }
    
    /**
     * @brief Copy constructor (silinmiş)
     */
    DoublyLinkedList(const DoublyLinkedList&) = delete;
    
    /**
     * @brief Copy assignment operator (silinmiş)
     */
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;

    /**
     * @brief Çift yönlü iterator
     * 
     * Bu iterator, listeyi ileri ve geri yönde gezinmeyi sağlar.
     * STL bidirectional_iterator_tag kategorisini destekler.
     */
    struct iterator {
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T; 
        using difference_type = std::ptrdiff_t; 
        using pointer = T*; 
        using reference = T&;
        
        Node* n = nullptr;  ///< Mevcut düğüm pointer'ı
        
        /**
         * @brief Varsayılan constructor
         */
        iterator() = default; 
        
        /**
         * @brief Düğüm pointer'ı ile constructor
         * @param p Düğüm pointer'ı
         */
        explicit iterator(Node* p): n(p) {}
        
        /**
         * @brief Dereference operator
         * @return Düğümdeki değerin referansı
         */
        reference operator*() const { return n->value; }
        
        /**
         * @brief Arrow operator
         * @return Düğümdeki değerin pointer'ı
         */
        pointer operator->() const { return &n->value; }
        
        /**
         * @brief Pre-increment operator
         * @return Sonraki düğüme geçen iterator
         */
        iterator& operator++(){ n = n->next; return *this; }
        
        /**
         * @brief Post-increment operator
         * @return Eski konumdaki iterator
         */
        iterator operator++(int){ iterator tmp(*this); ++(*this); return tmp; }
        
        /**
         * @brief Pre-decrement operator
         * @return Önceki düğüme geçen iterator
         */
        iterator& operator--(){ n = n->prev; return *this; }
        
        /**
         * @brief Post-decrement operator
         * @return Eski konumdaki iterator
         */
        iterator operator--(int){ iterator tmp(*this); --(*this); return tmp; }
        
        /**
         * @brief Equality operator
         * @param o Karşılaştırılacak iterator
         * @return true eğer aynı düğümü gösteriyorlarsa
         */
        bool operator==(const iterator& o) const { return n == o.n; }
        
        /**
         * @brief Inequality operator
         * @param o Karşılaştırılacak iterator
         * @return true eğer farklı düğümleri gösteriyorlarsa
         */
        bool operator!=(const iterator& o) const { return n != o.n; }
    };

    /**
     * @brief Başlangıç iteratörü
     * @return İlk düğümü gösteren iterator
     */
    iterator begin() const { return iterator(head_); }
    
    /**
     * @brief Sondan bir sonrası iteratörü
     * @return Liste sonundaki null iterator
     */
    iterator end() const { return iterator(nullptr); }
    
    /**
     * @brief Sondan geri iterasyon için başlangıç
     * @return Son düğümü gösteren iterator
     */
    iterator rbegin() const { return iterator(tail_); }

    /**
     * @brief Liste eleman sayısını döndürür
     * @return Eleman sayısı
     */
    std::size_t size() const { return size_; }
    
    /**
     * @brief Listenin boş olup olmadığını kontrol eder
     * @return true eğer liste boşsa
     */
    bool empty() const { return size_ == 0; }

    /**
     * @brief Tüm elemanları serbest bırakır
     * 
     * Liste başından sonuna kadar tüm düğümleri siler
     * ve listeyi boş duruma getirir.
     */
    void clear(){
        Node* p = head_;
        while (p) { 
            Node* nx = p->next; 
            delete p; 
            p = nx; 
        }
        head_ = tail_ = nullptr; 
        size_ = 0;
    }

    /**
     * @brief Listeye sona eleman ekler
     * @param v Eklenecek değer
     * @return Yeni eklenen düğümü gösteren iterator
     */
    iterator push_back(const T& v){
        Node* n = new Node(v);
        n->prev = tail_;
        if (tail_) tail_->next = n; else head_ = n;
        tail_ = n; ++size_;
        return iterator(n);
    }

    /**
     * @brief Listeye başa eleman ekler
     * @param v Eklenecek değer
     * @return Yeni eklenen düğümü gösteren iterator
     */
    iterator push_front(const T& v){
        Node* n = new Node(v);
        n->next = head_;
        if (head_) head_->prev = n; else tail_ = n;
        head_ = n; ++size_;
        return iterator(n);
    }

    /**
     * @brief Verilen düğümden sonra eleman ekler
     * @param it Referans alınacak iterator
     * @param v Eklenecek değer
     * @return Yeni eklenen düğümü gösteren iterator
     */
    iterator insert_after(iterator it, const T& v){
        if (it.n == nullptr) return push_front(v);
        Node* cur = it.n; 
        Node* n = new Node(v);
        n->prev = cur; 
        n->next = cur->next;
        if (cur->next) cur->next->prev = n; else tail_ = n;
        cur->next = n; ++size_; 
        return iterator(n);
    }

    /**
     * @brief Verilen konumdaki düğümü kaldırır
     * @param it Silinecek düğümü gösteren iterator
     * @return Sonraki düğümü gösteren iterator
     */
    iterator erase(iterator it){
        Node* cur = it.n; 
        if (!cur) return it;
        Node* nx = cur->next;
        if (cur->prev) cur->prev->next = cur->next; else head_ = cur->next;
        if (cur->next) cur->next->prev = cur->prev; else tail_ = cur->prev;
        delete cur; --size_; 
        return iterator(nx);
    }
};

} // namespace ds
