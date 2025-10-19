#pragma once
#include <vector>
#include <functional>

namespace ds {

template <typename T, typename Compare = std::less<T>>
class BinaryHeap {
    std::vector<T> a_;
    Compare cmp_{};
    void sift_up(std::size_t i){
        while (i>0){ std::size_t p=(i-1)/2; if (!cmp_(a_[p], a_[i])) break; std::swap(a_[p], a_[i]); i=p; }
    }
    void sift_down(std::size_t i){
        std::size_t n = a_.size();
        while(true){ std::size_t l=2*i+1, r=2*i+2, m=i; if (l<n && cmp_(a_[m], a_[l])) m=l; if (r<n && cmp_(a_[m], a_[r])) m=r; if (m==i) break; std::swap(a_[i], a_[m]); i=m; }
    }
public:
    bool empty() const { return a_.empty(); }
    std::size_t size() const { return a_.size(); }
    const T& top() const { return a_.front(); }
    void push(const T& v){ a_.push_back(v); sift_up(a_.size()-1); }
    void pop(){ std::swap(a_.front(), a_.back()); a_.pop_back(); if(!a_.empty()) sift_down(0); }
    std::vector<T> heap_sort_copy() const { auto b=a_; std::vector<T> out; out.reserve(b.size()); auto cmp=cmp_; auto sift_down=[&](std::size_t i){ std::size_t n=b.size(); while(true){ std::size_t l=2*i+1,r=2*i+2,m=i; if(l<n&&cmp(b[m],b[l])) m=l; if(r<n&&cmp(b[m],b[r])) m=r; if(m==i) break; std::swap(b[i],b[m]); i=m; }}; for (std::size_t i=b.size()/2;i-->0;) sift_down(i); while(!b.empty()){ std::swap(b.front(), b.back()); out.push_back(b.back()); b.pop_back(); if(!b.empty()) sift_down(0);} return out; }
};

} // namespace ds

