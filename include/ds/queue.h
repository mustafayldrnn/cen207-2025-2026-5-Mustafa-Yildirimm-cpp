#pragma once
#include <stdexcept>

namespace ds {

template <typename T>
class Queue {
    struct Node { T v; Node* next; explicit Node(const T& x): v(x), next(nullptr) {} };
    Node* head_ = nullptr; Node* tail_ = nullptr; std::size_t sz_ = 0;
public:
    ~Queue(){ while(head_){ Node* n = head_->next; delete head_; head_ = n; } tail_ = nullptr; }
    void enqueue(const T& v){ Node* n = new Node(v); if (!tail_) head_ = tail_ = n; else { tail_->next = n; tail_ = n; } ++sz_; }
    void dequeue(){ if (!head_) throw std::runtime_error("queue empty"); Node* n = head_->next; delete head_; head_ = n; if (!head_) tail_ = nullptr; --sz_; }
    T& front(){ if (!head_) throw std::runtime_error("queue empty"); return head_->v; }
    bool empty() const { return sz_==0; }
    std::size_t size() const { return sz_; }
};

} // namespace ds

