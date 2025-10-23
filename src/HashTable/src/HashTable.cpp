/**
 * @file HashTable.cpp
 * @brief Hash Table implementation
 */

#include "../header/HashTable.h"
#include <iostream>

namespace Coruh
{
    namespace DataStructures
    {
        template<typename K, typename V>
        HashTable<K, V>::HashTable(size_t initialCapacity, double loadFactor)
            : capacity(initialCapacity), loadFactor(loadFactor), size_(0)
        {
            table.resize(capacity);
        }

        template<typename K, typename V>
        size_t HashTable<K, V>::hash(const K& key) const
        {
            std::hash<K> hasher;
            return hasher(key) % capacity;
        }

        template<typename K, typename V>
        size_t HashTable<K, V>::findIndex(const K& key) const
        {
            size_t index = hash(key);
            size_t originalIndex = index;
            
            while (true) {
                if (table[index].isDeleted || table[index].key == key) {
                    return index;
                }
                index = (index + 1) % capacity;
                if (index == originalIndex) {
                    throw std::runtime_error("Hash table is full");
                }
            }
        }

        template<typename K, typename V>
        void HashTable<K, V>::resize()
        {
            std::vector<HashNode> oldTable = table;
            size_t oldCapacity = capacity;
            
            capacity *= 2;
            table.clear();
            table.resize(capacity);
            size_ = 0;
            
            for (size_t i = 0; i < oldCapacity; ++i) {
                if (!oldTable[i].isDeleted) {
                    insert(oldTable[i].key, oldTable[i].value);
                }
            }
        }

        template<typename K, typename V>
        void HashTable<K, V>::insert(const K& key, const V& value)
        {
            if (size_ >= capacity * loadFactor) {
                resize();
            }
            
            size_t index = findIndex(key);
            
            if (table[index].isDeleted || table[index].key != key) {
                size_++;
            }
            
            table[index] = HashNode(key, value);
        }

        template<typename K, typename V>
        bool HashTable<K, V>::contains(const K& key) const
        {
            size_t index = findIndex(key);
            return !table[index].isDeleted && table[index].key == key;
        }

        template<typename K, typename V>
        V& HashTable<K, V>::get(const K& key)
        {
            size_t index = findIndex(key);
            if (table[index].isDeleted || table[index].key != key) {
                throw std::runtime_error("Key not found");
            }
            return table[index].value;
        }

        template<typename K, typename V>
        const V& HashTable<K, V>::get(const K& key) const
        {
            size_t index = findIndex(key);
            if (table[index].isDeleted || table[index].key != key) {
                throw std::runtime_error("Key not found");
            }
            return table[index].value;
        }

        template<typename K, typename V>
        void HashTable<K, V>::remove(const K& key)
        {
            size_t index = findIndex(key);
            if (!table[index].isDeleted && table[index].key == key) {
                table[index].isDeleted = true;
                size_--;
            }
        }

        template<typename K, typename V>
        void HashTable<K, V>::clear()
        {
            table.clear();
            table.resize(capacity);
            size_ = 0;
        }

        template<typename K, typename V>
        size_t HashTable<K, V>::getSize() const
        {
            return size_;
        }

        template<typename K, typename V>
        bool HashTable<K, V>::isEmpty() const
        {
            return size_ == 0;
        }

        template<typename K, typename V>
        void HashTable<K, V>::print() const
        {
            for (size_t i = 0; i < capacity; ++i) {
                if (!table[i].isDeleted) {
                    std::cout << "[" << table[i].key << ": " << table[i].value << "] ";
                }
            }
            std::cout << std::endl;
        }
    }
}