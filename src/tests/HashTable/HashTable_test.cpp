/**
 * @file HashTable_test.cpp
 * @brief Unit tests for Hash Table
 */

#include <gtest/gtest.h>
#include "../../HashTable/header/HashTable.h"

using namespace Coruh::DataStructures;

class HashTableTest : public ::testing::Test {
protected:
    void SetUp() override {
        hashTable = new HashTable<std::string, std::string>();
    }
    
    void TearDown() override {
        delete hashTable;
    }
    
    HashTable<std::string, std::string>* hashTable;
};

TEST_F(HashTableTest, EmptyHashTable) {
    EXPECT_TRUE(hashTable->isEmpty());
    EXPECT_EQ(hashTable->getSize(), 0);
    EXPECT_EQ(hashTable->getLoadFactor(), 0.0);
}

TEST_F(HashTableTest, InsertAndGet) {
    hashTable->insert("key1", "value1");
    EXPECT_EQ(hashTable->getSize(), 1);
    EXPECT_EQ(hashTable->get("key1"), "value1");
    EXPECT_TRUE(hashTable->contains("key1"));
}

TEST_F(HashTableTest, MultipleInsertions) {
    hashTable->insert("key1", "value1");
    hashTable->insert("key2", "value2");
    hashTable->insert("key3", "value3");
    
    EXPECT_EQ(hashTable->getSize(), 3);
    EXPECT_EQ(hashTable->get("key1"), "value1");
    EXPECT_EQ(hashTable->get("key2"), "value2");
    EXPECT_EQ(hashTable->get("key3"), "value3");
}

TEST_F(HashTableTest, UpdateValue) {
    hashTable->insert("key1", "value1");
    hashTable->insert("key1", "updated_value");
    
    EXPECT_EQ(hashTable->getSize(), 1); // Size should not change
    EXPECT_EQ(hashTable->get("key1"), "updated_value");
}

TEST_F(HashTableTest, RemoveKey) {
    hashTable->insert("key1", "value1");
    hashTable->insert("key2", "value2");
    
    EXPECT_TRUE(hashTable->remove("key1"));
    EXPECT_EQ(hashTable->getSize(), 1);
    EXPECT_FALSE(hashTable->contains("key1"));
    EXPECT_TRUE(hashTable->contains("key2"));
}

TEST_F(HashTableTest, KeyNotFound) {
    EXPECT_THROW(hashTable->get("nonexistent"), std::runtime_error);
    EXPECT_FALSE(hashTable->contains("nonexistent"));
    EXPECT_FALSE(hashTable->remove("nonexistent"));
}

TEST_F(HashTableTest, LoadFactor) {
    // Insert elements and check load factor
    for (int i = 0; i < 10; ++i) {
        hashTable->insert("key" + std::to_string(i), "value" + std::to_string(i));
    }
    
    EXPECT_GT(hashTable->getLoadFactor(), 0.0);
    EXPECT_LT(hashTable->getLoadFactor(), 1.0);
}

TEST_F(HashTableTest, CollisionHandling) {
    // Test with keys that might hash to same bucket
    hashTable->insert("key1", "value1");
    hashTable->insert("key2", "value2");
    hashTable->insert("key3", "value3");
    
    EXPECT_EQ(hashTable->getSize(), 3);
    EXPECT_TRUE(hashTable->contains("key1"));
    EXPECT_TRUE(hashTable->contains("key2"));
    EXPECT_TRUE(hashTable->contains("key3"));
}

TEST_F(HashTableTest, GetAllKeys) {
    hashTable->insert("key1", "value1");
    hashTable->insert("key2", "value2");
    hashTable->insert("key3", "value3");
    
    auto keys = hashTable->getAllKeys();
    EXPECT_EQ(keys.size(), 3);
    
    // Check if all keys are present
    EXPECT_TRUE(std::find(keys.begin(), keys.end(), "key1") != keys.end());
    EXPECT_TRUE(std::find(keys.begin(), keys.end(), "key2") != keys.end());
    EXPECT_TRUE(std::find(keys.begin(), keys.end(), "key3") != keys.end());
}

TEST_F(HashTableTest, GetAllValues) {
    hashTable->insert("key1", "value1");
    hashTable->insert("key2", "value2");
    hashTable->insert("key3", "value3");
    
    auto values = hashTable->getAllValues();
    EXPECT_EQ(values.size(), 3);
    
    // Check if all values are present
    EXPECT_TRUE(std::find(values.begin(), values.end(), "value1") != values.end());
    EXPECT_TRUE(std::find(values.begin(), values.end(), "value2") != values.end());
    EXPECT_TRUE(std::find(values.begin(), values.end(), "value3") != values.end());
}

TEST_F(HashTableTest, ClearHashTable) {
    hashTable->insert("key1", "value1");
    hashTable->insert("key2", "value2");
    hashTable->clear();
    
    EXPECT_TRUE(hashTable->isEmpty());
    EXPECT_EQ(hashTable->getSize(), 0);
    EXPECT_FALSE(hashTable->contains("key1"));
    EXPECT_FALSE(hashTable->contains("key2"));
}

TEST_F(HashTableTest, LargeHashTable) {
    // Test with many elements
    for (int i = 0; i < 1000; ++i) {
        hashTable->insert("key" + std::to_string(i), "value" + std::to_string(i));
    }
    
    EXPECT_EQ(hashTable->getSize(), 1000);
    EXPECT_TRUE(hashTable->contains("key500"));
    EXPECT_EQ(hashTable->get("key500"), "value500");
}

TEST_F(HashTableTest, HashFunction) {
    // Test that different keys can be stored
    hashTable->insert("a", "value_a");
    hashTable->insert("b", "value_b");
    hashTable->insert("c", "value_c");
    
    EXPECT_EQ(hashTable->getSize(), 3);
    EXPECT_NE(hashTable->get("a"), hashTable->get("b"));
    EXPECT_NE(hashTable->get("b"), hashTable->get("c"));
}
