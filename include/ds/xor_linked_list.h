/**
 * @file xor_linked_list.h
 * @brief Bellek tasarrufu için XOR işaretçi tekniğiyle çift yönlü liste.
 */
#pragma once
#include <cstdint>
#include <cstddef>
#include <iterator>

namespace ds {

/** @tparam T Eleman tipi */
template <typename T>
class XORLinkedList {
    struct Node { T value; Node* npx; explicit Node(const T& v): value(v), npx(nullptr) {} };
    Node* head_ = nullptr;
    Node* tail_ = nullptr;
    std::size_t size_ = 0;

    /** @brief İşaretçileri XOR’layarak tek işaretçide saklar. */
    static Node* XOR(Node* a, Node* b){
        return reinterpret_cast<Node*>(reinterpret_cast<uintptr_t>(a) ^ reinterpret_cast<uintptr_t>(b));
    }

public:
    XORLinkedList() = default;
    ~XORLinkedList(){ clear(); }
    XORLinkedList(const XORLinkedList&) = delete;
    XORLinkedList& operator=(const XORLinkedList&) = delete;

    /** @brief Tüm düğümleri serbest bırakır. */
    void clear(){
        Node* prev = nullptr; Node* cur = head_;
        while (cur){ Node* next = XOR(prev, cur->npx); prev = cur; cur = next; delete prev; }
        head_ = tail_ = nullptr; size_ = 0;
    }

    /** @brief Eleman sayısı */
    std::size_t size() const { return size_; }
    /** @brief Boş mu? */
    bool empty() const { return size_ == 0; }

    /** @brief Sona ekler. */
    void push_back(const T& v){
        Node* n = new Node(v);
        if (!head_) { head_ = tail_ = n; }
        else {
            n->npx = tail_;
            tail_->npx = XOR(tail_->npx, n);
            tail_ = n;
        }
        ++size_;
    }

    /** @brief Başa ekler. */
    void push_front(const T& v){
        Node* n = new Node(v);
        if (!head_) { head_ = tail_ = n; }
        else {
            n->npx = head_;
            head_->npx = XOR(n, head_->npx);
            head_ = n;
        }
        ++size_;
    }

    /** @brief Sondan bir eleman çıkarır. */
    bool pop_back(){
        if (!tail_) return false;
        Node* prev = XOR(tail_->npx, nullptr);
        if (!prev){ delete tail_; head_ = tail_ = nullptr; }
        else { prev->npx = XOR(prev->npx, tail_); delete tail_; tail_ = prev; }
        --size_; return true;
    }

    /** @brief Baştan bir eleman çıkarır. */
    bool pop_front(){
        if (!head_) return false;
        Node* next = XOR(nullptr, head_->npx);
        if (!next){ delete head_; head_ = tail_ = nullptr; }
        else { next->npx = XOR(head_, next->npx); delete head_; head_ = next; }
        --size_; return true;
    }

    // Forward iteration: returns values via callback, stop if cb returns false
    /** @brief Baştan sona dolaşım (callback false döndürürse durur). */
    template <typename F>
    void for_each_forward(F cb) const {
        Node* prev = nullptr; Node* cur = head_;
        while (cur){ if (!cb(cur->value)) break; Node* next = XOR(prev, cur->npx); prev = cur; cur = next; }
    }

    /** @brief Sondan başa dolaşım (callback false döndürürse durur). */
    template <typename F>
    void for_each_backward(F cb) const {
        Node* next = nullptr; Node* cur = tail_;
        while (cur){ if (!cb(cur->value)) break; Node* prev = XOR(cur->npx, next); next = cur; cur = prev; }
    }

    // Remove first element equal to v; returns true if removed
    /** @brief İlk eşleşen değeri kaldırır. */
    bool remove_first(const T& v){
        Node* prev = nullptr; Node* cur = head_;
        while (cur){
            if (cur->value == v){
                Node* next = XOR(prev, cur->npx);
                if (prev) prev->npx = XOR(XOR(prev->npx, cur), next);
                else head_ = next;
                if (next) next->npx = XOR(prev, XOR(cur, next->npx));
                else tail_ = prev;
                delete cur; --size_; return true;
            }
            Node* next = XOR(prev, cur->npx); prev = cur; cur = next;
        }
        return false;
    }
};

} // namespace ds
