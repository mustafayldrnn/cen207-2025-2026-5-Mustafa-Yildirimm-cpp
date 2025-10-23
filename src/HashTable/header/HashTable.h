/**
 * @file HashTable.h
 * @brief Hash Table implementation
 */

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>
#include <functional>
#include <stdexcept>

namespace Coruh
{
    namespace DataStructures
    {
        template<typename K, typename V>
        class HashTable
        {
        private:
            struct HashNode
            {
                K key;
                V value;
                bool isDeleted;
                
                HashNode() : isDeleted(false) {}
                HashNode(const K& k, const V& v) : key(k), value(v), isDeleted(false) {}
            };
            
            std::vector<HashNode> table;
            size_t size_;
            size_t capacity;
            double loadFactor;
            
            size_t hash(const K& key) const;
            size_t findIndex(const K& key) const;
            void resize();

        public:
            HashTable(size_t initialCapacity = 16, double loadFactor = 0.75);
            ~HashTable() = default;
            
            // Basic operations
            void insert(const K& key, const V& value);
            bool contains(const K& key) const;
            V& get(const K& key);
            const V& get(const K& key) const;
            void remove(const K& key);
            void clear();
            
            // Properties
            size_t getSize() const;
            bool isEmpty() const;
            
            // Utility
            void print() const;
        };
    }
}

#include "HashTable.cpp"

#endif // HASH_TABLE_H