#pragma once
#include <cstddef>
#include <iterator>

namespace ds {

template <typename T>
class DoublyLinkedList {
    struct Node { T value; Node* prev; Node* next; Node(const T& v): value(v), prev(nullptr), next(nullptr) {} };
    Node* head_ = nullptr;
    Node* tail_ = nullptr;
    std::size_t size_ = 0;

public:
    DoublyLinkedList() = default;
    ~DoublyLinkedList() { clear(); }
    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;

    struct iterator {
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T; using difference_type = std::ptrdiff_t; using pointer = T*; using reference = T&;
        Node* n = nullptr; iterator() = default; explicit iterator(Node* p): n(p) {}
        reference operator*() const { return n->value; }
        pointer operator->() const { return &n->value; }
        iterator& operator++(){ n = n->next; return *this; }
        iterator operator++(int){ iterator tmp(*this); ++(*this); return tmp; }
        iterator& operator--(){ n = n->prev; return *this; }
        iterator operator--(int){ iterator tmp(*this); --(*this); return tmp; }
        bool operator==(const iterator& o) const { return n == o.n; }
        bool operator!=(const iterator& o) const { return n != o.n; }
    };

    iterator begin() const { return iterator(head_); }
    iterator end() const { return iterator(nullptr); }
    iterator rbegin() const { return iterator(tail_); }

    std::size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

    void clear(){
        Node* p = head_;
        while (p) { Node* nx = p->next; delete p; p = nx; }
        head_ = tail_ = nullptr; size_ = 0;
    }

    iterator push_back(const T& v){
        Node* n = new Node(v);
        n->prev = tail_;
        if (tail_) tail_->next = n; else head_ = n;
        tail_ = n; ++size_;
        return iterator(n);
    }

    iterator push_front(const T& v){
        Node* n = new Node(v);
        n->next = head_;
        if (head_) head_->prev = n; else tail_ = n;
        head_ = n; ++size_;
        return iterator(n);
    }

    iterator insert_after(iterator it, const T& v){
        if (it.n == nullptr) return push_front(v);
        Node* cur = it.n; Node* n = new Node(v);
        n->prev = cur; n->next = cur->next;
        if (cur->next) cur->next->prev = n; else tail_ = n;
        cur->next = n; ++size_; return iterator(n);
    }

    iterator erase(iterator it){
        Node* cur = it.n; if (!cur) return it;
        Node* nx = cur->next;
        if (cur->prev) cur->prev->next = cur->next; else head_ = cur->next;
        if (cur->next) cur->next->prev = cur->prev; else tail_ = cur->prev;
        delete cur; --size_; return iterator(nx);
    }
};

} // namespace ds

