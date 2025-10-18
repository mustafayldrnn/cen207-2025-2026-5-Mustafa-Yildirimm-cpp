#include "../header/HashTable.h"
#include <iostream>
#include <stdexcept>

using namespace Coruh::DataStructures;

template<typename K, typename V>
HashTable<K, V>::HashTable(size_t initialCapacity) 
    : capacity(initialCapacity), size(0) {
    buckets.resize(capacity);
}

template<typename K, typename V>
size_t HashTable<K, V>::hash(const K& key) const {
    return hasher(key) % capacity;
}

template<typename K, typename V>
void HashTable<K, V>::resize() {
    size_t oldCapacity = capacity;
    capacity *= 2;
    
    std::vector<std::list<KeyValuePair>> oldBuckets = std::move(buckets);
    buckets.clear();
    buckets.resize(capacity);
    
    // Rehash all elements
    for (const auto& bucket : oldBuckets) {
        for (const auto& pair : bucket) {
            size_t newIndex = hash(pair.key);
            buckets[newIndex].push_back(pair);
        }
    }
}

template<typename K, typename V>
void HashTable<K, V>::insert(const K& key, const V& value) {
    size_t index = hash(key);
    
    // Check if key already exists
    for (auto it = buckets[index].begin(); it != buckets[index].end(); ++it) {
        if (it->key == key) {
            it->value = value; // Update existing value
            return;
        }
    }
    
    // Insert new key-value pair
    buckets[index].emplace_back(key, value);
    size++;
    
    // Resize if load factor is too high
    if (getLoadFactor() > 0.75) {
        resize();
    }
}

template<typename K, typename V>
V HashTable<K, V>::get(const K& key) const {
    size_t index = hash(key);
    
    for (const auto& pair : buckets[index]) {
        if (pair.key == key) {
            return pair.value;
        }
    }
    
    throw std::runtime_error("Key not found");
}

template<typename K, typename V>
bool HashTable<K, V>::contains(const K& key) const {
    size_t index = hash(key);
    
    for (const auto& pair : buckets[index]) {
        if (pair.key == key) {
            return true;
        }
    }
    
    return false;
}

template<typename K, typename V>
bool HashTable<K, V>::remove(const K& key) {
    size_t index = hash(key);
    
    for (auto it = buckets[index].begin(); it != buckets[index].end(); ++it) {
        if (it->key == key) {
            buckets[index].erase(it);
            size--;
            return true;
        }
    }
    
    return false;
}

template<typename K, typename V>
size_t HashTable<K, V>::getSize() const {
    return size;
}

template<typename K, typename V>
size_t HashTable<K, V>::getCapacity() const {
    return capacity;
}

template<typename K, typename V>
bool HashTable<K, V>::isEmpty() const {
    return size == 0;
}

template<typename K, typename V>
double HashTable<K, V>::getLoadFactor() const {
    return static_cast<double>(size) / capacity;
}

template<typename K, typename V>
void HashTable<K, V>::clear() {
    for (auto& bucket : buckets) {
        bucket.clear();
    }
    size = 0;
}

template<typename K, typename V>
void HashTable<K, V>::display() const {
    std::cout << "HashTable (Size: " << size << ", Capacity: " << capacity 
              << ", Load Factor: " << getLoadFactor() << "):" << std::endl;
    
    for (size_t i = 0; i < capacity; ++i) {
        if (!buckets[i].empty()) {
            std::cout << "Bucket " << i << ": ";
            for (const auto& pair : buckets[i]) {
                std::cout << "[" << pair.key << "=" << pair.value << "] ";
            }
            std::cout << std::endl;
        }
    }
}

template<typename K, typename V>
std::vector<K> HashTable<K, V>::getAllKeys() const {
    std::vector<K> keys;
    for (const auto& bucket : buckets) {
        for (const auto& pair : bucket) {
            keys.push_back(pair.key);
        }
    }
    return keys;
}

template<typename K, typename V>
std::vector<V> HashTable<K, V>::getAllValues() const {
    std::vector<V> values;
    for (const auto& bucket : buckets) {
        for (const auto& pair : bucket) {
            values.push_back(pair.value);
        }
    }
    return values;
}

// Explicit template instantiation for common types
template class HashTable<std::string, std::string>;
template class HashTable<std::string, int>;
template class HashTable<int, std::string>;
template class HashTable<int, int>;
