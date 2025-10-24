#include <gtest/gtest.h>
#include "ds/hash_table.h"
#include <string>

TEST(HashTable, InsertFindErase){
    ds::HashTable<std::string,int> ht(8);
    EXPECT_TRUE(ht.insert("a",1));
    EXPECT_TRUE(ht.insert("b",2));
    EXPECT_FALSE(ht.insert("a",3)); // update
    auto v = ht.find("a"); ASSERT_NE(v,nullptr); EXPECT_EQ(*v,3);
    EXPECT_TRUE(ht.erase("a"));
    EXPECT_EQ(ht.find("a"), nullptr);
}

TEST(HashTable, SizeAndEmpty){
    ds::HashTable<std::string,int> ht(4);
    EXPECT_TRUE(ht.empty());
    EXPECT_EQ(ht.size(), 0u);
    
    ht.insert("key1", 10);
    EXPECT_FALSE(ht.empty());
    EXPECT_EQ(ht.size(), 1u);
    
    ht.insert("key2", 20);
    EXPECT_EQ(ht.size(), 2u);
    
    ht.erase("key1");
    EXPECT_EQ(ht.size(), 1u);
    
    ht.erase("key2");
    EXPECT_TRUE(ht.empty());
    EXPECT_EQ(ht.size(), 0u);
}

TEST(HashTable, Contains){
    ds::HashTable<std::string,int> ht(8);
    EXPECT_FALSE(ht.contains("nonexistent"));
    
    ht.insert("test", 42);
    EXPECT_TRUE(ht.contains("test"));
    EXPECT_FALSE(ht.contains("other"));
}

TEST(HashTable, Rehash){
    ds::HashTable<std::string,int> ht(2);
    // Force rehash by adding many elements
    for(int i = 0; i < 10; ++i) {
        ht.insert("key" + std::to_string(i), i);
    }
    EXPECT_EQ(ht.size(), 10u);
    
    // Verify all elements are still accessible
    for(int i = 0; i < 10; ++i) {
        EXPECT_TRUE(ht.contains("key" + std::to_string(i)));
        auto v = ht.find("key" + std::to_string(i));
        ASSERT_NE(v, nullptr);
        EXPECT_EQ(*v, i);
    }
}

