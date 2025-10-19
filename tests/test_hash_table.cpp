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

