#pragma once
#include <vector>
#include <optional>
#include <functional>
#include <stdexcept>

namespace ds {

enum class SlotState { Empty, Occupied, Deleted };

template <typename K, typename V>
class HashTable {
    struct Entry { K key; V value; SlotState state = SlotState::Empty; };
    std::vector<Entry> table_;
    std::size_t count_ = 0;
    float max_load_ = 0.7f;
    std::hash<K> hasher_{};

    std::size_t idx(const K& k) const { return hasher_(k) & (table_.size() - 1); }
    void rehash(std::size_t new_cap){
        std::vector<Entry> old = std::move(table_);
        table_.assign(new_cap, Entry{}); count_ = 0;
        for (auto& e : old){ if (e.state == SlotState::Occupied) insert(e.key, e.value); }
    }
    void ensure(){ if (count_ + 1 > static_cast<std::size_t>(max_load_ * table_.size())) rehash(table_.size()<<1); }

public:
    explicit HashTable(std::size_t cap = 16){ std::size_t c=1; while(c<cap) c<<=1; table_.assign(c, Entry{}); }
    std::size_t size() const { return count_; }
    bool empty() const { return count_==0; }

    bool insert(const K& k, const V& v){ ensure(); std::size_t i = idx(k); std::size_t first_del = table_.size();
        while(true){ auto& e = table_[i]; if (e.state == SlotState::Empty){ if (first_del != table_.size()) { table_[first_del] = {k,v,SlotState::Occupied}; } else { e = {k,v,SlotState::Occupied}; } ++count_; return true; }
            if (e.state == SlotState::Deleted){ if (first_del == table_.size()) first_del = i; }
            else if (e.key == k){ e.value = v; return false; }
            i = (i + 1) & (table_.size()-1);
        }
    }

    V* find(const K& k){ std::size_t i = idx(k); while(true){ auto& e = table_[i]; if (e.state == SlotState::Empty) return nullptr; if (e.state == SlotState::Occupied && e.key == k) return &e.value; i = (i + 1) & (table_.size()-1);} }
    const V* find(const K& k) const { return const_cast<HashTable*>(this)->find(k); }
    bool contains(const K& k) const { return find(k) != nullptr; }
    bool erase(const K& k){ std::size_t i = idx(k); while(true){ auto& e = table_[i]; if (e.state == SlotState::Empty) return false; if (e.state == SlotState::Occupied && e.key == k){ e.state = SlotState::Deleted; --count_; return true; } i = (i + 1) & (table_.size()-1);} }
};

} // namespace ds

