/**
 * @file HashTable.h
 * @brief Hash Table implementation for Simple Key-Value Database
 */

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>
#include <list>
#include <functional>
#include <string>

namespace Coruh
{
    namespace DataStructures
    {
        /**
         * @class HashTable
         * @brief Hash table with chaining for collision resolution
         */
        template<typename K, typename V>
        class HashTable
        {
        private:
            struct KeyValuePair
            {
                K key;
                V value;
                
                KeyValuePair(const K& k, const V& v) : key(k), value(v) {}
            };
            
            std::vector<std::list<KeyValuePair>> buckets;
            size_t capacity;
            size_t size;
            std::hash<K> hasher;
            
            /**
             * Hash function
             */
            size_t hash(const K& key) const;
            
            /**
             * Resize table when load factor is too high
             */
            void resize();
            
        public:
            /**
             * Constructor
             * @param initialCapacity Initial capacity
             */
            explicit HashTable(size_t initialCapacity = 16);
            
            /**
             * Insert key-value pair
             * @param key Key
             * @param value Value
             */
            void insert(const K& key, const V& value);
            
            /**
             * Get value by key
             * @param key Key
             * @return Value if found
             */
            V get(const K& key) const;
            
            /**
             * Check if key exists
             * @param key Key to check
             * @return true if key exists
             */
            bool contains(const K& key) const;
            
            /**
             * Remove key-value pair
             * @param key Key to remove
             * @return true if removed
             */
            bool remove(const K& key);
            
            /**
             * Get table size
             * @return Number of elements
             */
            size_t getSize() const;
            
            /**
             * Get table capacity
             * @return Table capacity
             */
            size_t getCapacity() const;
            
            /**
             * Check if table is empty
             * @return true if empty
             */
            bool isEmpty() const;
            
            /**
             * Get load factor
             * @return Load factor
             */
            double getLoadFactor() const;
            
            /**
             * Clear all elements
             */
            void clear();
            
            /**
             * Display all key-value pairs
             */
            void display() const;
            
            /**
             * Get all keys
             * @return Vector of all keys
             */
            std::vector<K> getAllKeys() const;
            
            /**
             * Get all values
             * @return Vector of all values
             */
            std::vector<V> getAllValues() const;
        };
    }
}

#endif // HASH_TABLE_H
