/**
 * @file stack.h
 * @brief Basit bağlı liste tabanlı yığın (LIFO).
 */
#pragma once
#include <stdexcept>

namespace ds {

/** @tparam T Eleman tipi */
template <typename T>
class Stack {
    struct Node { T v; Node* next; explicit Node(const T& x): v(x), next(nullptr) {} };
    Node* top_ = nullptr; std::size_t sz_ = 0;
public:
    /** @brief Yıkıcı: tüm düğümleri serbest bırakır. */
    ~Stack(){ while(top_) { Node* n = top_->next; delete top_; top_ = n; } }
    /** @brief Sona (tepeye) bir eleman iter. */
    void push(const T& v){ Node* n = new Node(v); n->next = top_; top_ = n; ++sz_; }
    /** @brief Yığın boş mu? */
    bool empty() const { return sz_==0; }
    /** @brief Eleman sayısı. */
    std::size_t size() const { return sz_; }
    /** @brief Tepe elemanı döndürür. */
    T& top(){ if (!top_) throw std::runtime_error("stack empty"); return top_->v; }
    /** @brief Tepe elemanı çıkarır. */
    void pop(){ if (!top_) throw std::runtime_error("stack empty"); Node* n = top_->next; delete top_; top_ = n; --sz_; }
};

} // namespace ds
