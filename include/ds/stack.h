#pragma once
#include <stdexcept>

namespace ds {

template <typename T>
class Stack {
    struct Node { T v; Node* next; explicit Node(const T& x): v(x), next(nullptr) {} };
    Node* top_ = nullptr; std::size_t sz_ = 0;
public:
    ~Stack(){ while(top_) { Node* n = top_->next; delete top_; top_ = n; } }
    void push(const T& v){ Node* n = new Node(v); n->next = top_; top_ = n; ++sz_; }
    bool empty() const { return sz_==0; }
    std::size_t size() const { return sz_; }
    T& top(){ if (!top_) throw std::runtime_error("stack empty"); return top_->v; }
    void pop(){ if (!top_) throw std::runtime_error("stack empty"); Node* n = top_->next; delete top_; top_ = n; --sz_; }
};

} // namespace ds

