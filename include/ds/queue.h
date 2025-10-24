/**
 * @file queue.h
 * @brief Bağlı liste tabanlı kuyruk (FIFO).
 */
#pragma once
#include <stdexcept>

namespace ds {

/** @tparam T Eleman tipi */
template <typename T>
class Queue {
    struct Node { T v; Node* next; explicit Node(const T& x): v(x), next(nullptr) {} };
    Node* head_ = nullptr; Node* tail_ = nullptr; std::size_t sz_ = 0;
public:
    /** @brief Yıkıcı: tüm düğümleri serbest bırakır. */
    ~Queue(){ while(head_){ Node* n = head_->next; delete head_; head_ = n; } tail_ = nullptr; }
    /** @brief Kuyruğun sonuna ekler. */
    void enqueue(const T& v){ Node* n = new Node(v); if (!tail_) head_ = tail_ = n; else { tail_->next = n; tail_ = n; } ++sz_; }
    /** @brief Baştaki elemanı çıkarır. */
    void dequeue(){ if (!head_) throw std::runtime_error("queue empty"); Node* n = head_->next; delete head_; head_ = n; if (!head_) tail_ = nullptr; --sz_; }
    /** @brief Baştaki elemanı döndürür. */
    T& front(){ if (!head_) throw std::runtime_error("queue empty"); return head_->v; }
    /** @brief Kuyruk boş mu? */
    bool empty() const { return sz_==0; }
    /** @brief Eleman sayısı. */
    std::size_t size() const { return sz_; }
};

} // namespace ds
