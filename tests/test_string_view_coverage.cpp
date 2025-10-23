/**
 * @file test_string_view_coverage.cpp
 * @brief Test file to increase coverage for _msvc_string_view.hpp
 * 
 * This test file specifically targets uncovered lines in _msvc_string_view.hpp
 * to increase the line coverage from 41.9% to 100%
 */

#include <gtest/gtest.h>
#include <string_view>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <limits>

namespace {

/**
 * @class StringViewCoverageTest
 * @brief Test class for string_view functionality coverage
 */
class StringViewCoverageTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup for each test
    }
    
    void TearDown() override {
        // Cleanup after each test
    }
};

/**
 * @test TestStringViewConstruction
 * @brief Test string_view construction from various sources
 */
TEST_F(StringViewCoverageTest, TestStringViewConstruction) {
    // Test construction from C-string
    const char* cstr = "Hello, World!";
    std::string_view sv1(cstr);
    EXPECT_EQ(sv1.size(), 13);
    EXPECT_EQ(sv1.data(), cstr);
    
    // Test construction from std::string
    std::string str = "Test String";
    std::string_view sv2(str);
    EXPECT_EQ(sv2.size(), str.size());
    EXPECT_EQ(sv2.data(), str.data());
    
    // Test construction with length
    std::string_view sv3(cstr, 5);
    EXPECT_EQ(sv3.size(), 5);
    EXPECT_EQ(sv3, "Hello");
    
    // Test construction from char array
    char arr[] = "Array Test";
    std::string_view sv4(arr);
    EXPECT_EQ(sv4.size(), 10);
    EXPECT_EQ(sv4, "Array Test");
    
    // Test construction from string literal
    std::string_view sv5("Literal");
    EXPECT_EQ(sv5.size(), 7);
    EXPECT_EQ(sv5, "Literal");
}

/**
 * @test TestStringViewAccess
 * @brief Test string_view element access methods
 */
TEST_F(StringViewCoverageTest, TestStringViewAccess) {
    std::string_view sv("Hello, World!");
    
    // Test operator[]
    EXPECT_EQ(sv[0], 'H');
    EXPECT_EQ(sv[6], ' ');
    EXPECT_EQ(sv[12], '!');
    
    // Test at() method
    EXPECT_EQ(sv.at(0), 'H');
    EXPECT_EQ(sv.at(6), ' ');
    EXPECT_EQ(sv.at(12), '!');
    
    // Test front() and back()
    EXPECT_EQ(sv.front(), 'H');
    EXPECT_EQ(sv.back(), '!');
    
    // Test data() method
    EXPECT_NE(sv.data(), nullptr);
    EXPECT_EQ(sv.data()[0], 'H');
    
    // Test size() and length()
    EXPECT_EQ(sv.size(), 13);
    EXPECT_EQ(sv.length(), 13);
    
    // Test empty()
    EXPECT_FALSE(sv.empty());
    
    std::string_view empty_sv;
    EXPECT_TRUE(empty_sv.empty());
    EXPECT_EQ(empty_sv.size(), 0);
}

/**
 * @test TestStringViewIterators
 * @brief Test string_view iterator functionality
 */
TEST_F(StringViewCoverageTest, TestStringViewIterators) {
    std::string_view sv("Test");
    
    // Test begin() and end()
    auto it_begin = sv.begin();
    auto it_end = sv.end();
    EXPECT_NE(it_begin, it_end);
    EXPECT_EQ(*it_begin, 'T');
    EXPECT_EQ(*(it_end - 1), 't');
    
    // Test cbegin() and cend()
    auto cit_begin = sv.cbegin();
    auto cit_end = sv.cend();
    EXPECT_NE(cit_begin, cit_end);
    EXPECT_EQ(*cit_begin, 'T');
    
    // Test rbegin() and rend()
    auto rit_begin = sv.rbegin();
    auto rit_end = sv.rend();
    EXPECT_NE(rit_begin, rit_end);
    EXPECT_EQ(*rit_begin, 't');
    EXPECT_EQ(*(rit_end - 1), 'T');
    
    // Test crbegin() and crend()
    auto crit_begin = sv.crbegin();
    auto crit_end = sv.crend();
    EXPECT_NE(crit_begin, crit_end);
    EXPECT_EQ(*crit_begin, 't');
    
    // Test range-based for loop
    std::string result;
    for (char c : sv) {
        result += c;
    }
    EXPECT_EQ(result, "Test");
}

/**
 * @test TestStringViewSubstring
 * @brief Test string_view substring operations
 */
TEST_F(StringViewCoverageTest, TestStringViewSubstring) {
    std::string_view sv("Hello, World!");
    
    // Test substr() with start position
    std::string_view sub1 = sv.substr(7);
    EXPECT_EQ(sub1, "World!");
    EXPECT_EQ(sub1.size(), 6);
    
    // Test substr() with start position and length
    std::string_view sub2 = sv.substr(0, 5);
    EXPECT_EQ(sub2, "Hello");
    EXPECT_EQ(sub2.size(), 5);
    
    // Test substr() with middle range
    std::string_view sub3 = sv.substr(7, 5);
    EXPECT_EQ(sub3, "World");
    EXPECT_EQ(sub3.size(), 5);
    
    // Test substr() with single character
    std::string_view sub4 = sv.substr(6, 1);
    EXPECT_EQ(sub4, ",");
    EXPECT_EQ(sub4.size(), 1);
    
    // Test substr() with empty result
    std::string_view sub5 = sv.substr(13, 0);
    EXPECT_TRUE(sub5.empty());
}

/**
 * @test TestStringViewComparison
 * @brief Test string_view comparison operations
 */
TEST_F(StringViewCoverageTest, TestStringViewComparison) {
    std::string_view sv1("Hello");
    std::string_view sv2("Hello");
    std::string_view sv3("World");
    std::string_view sv4("Hell");
    
    // Test equality
    EXPECT_EQ(sv1, sv2);
    EXPECT_NE(sv1, sv3);
    EXPECT_NE(sv1, sv4);
    
    // Test less than
    EXPECT_LT(sv4, sv1);
    EXPECT_LT(sv1, sv3);
    
    // Test greater than
    EXPECT_GT(sv1, sv4);
    EXPECT_GT(sv3, sv1);
    
    // Test less than or equal
    EXPECT_LE(sv1, sv2);
    EXPECT_LE(sv4, sv1);
    EXPECT_LE(sv1, sv3);
    
    // Test greater than or equal
    EXPECT_GE(sv1, sv2);
    EXPECT_GE(sv1, sv4);
    EXPECT_GE(sv3, sv1);
    
    // Test with different types
    std::string str = "Hello";
    const char* cstr = "Hello";
    
    EXPECT_EQ(sv1, str);
    EXPECT_EQ(sv1, cstr);
    EXPECT_EQ(str, sv1);
    EXPECT_EQ(cstr, sv1);
}

/**
 * @test TestStringViewFind
 * @brief Test string_view find operations
 */
TEST_F(StringViewCoverageTest, TestStringViewFind) {
    std::string_view sv("Hello, World! Hello, Universe!");
    
    // Test find() with character
    EXPECT_EQ(sv.find('H'), 0);
    EXPECT_EQ(sv.find('o'), 4);
    EXPECT_EQ(sv.find('!'), 12);
    EXPECT_EQ(sv.find('z'), std::string_view::npos);
    
    // Test find() with string
    EXPECT_EQ(sv.find("Hello"), 0);
    EXPECT_EQ(sv.find("World"), 7);
    EXPECT_EQ(sv.find("Universe"), 20);
    EXPECT_EQ(sv.find("xyz"), std::string_view::npos);
    
    // Test find() with string_view
    std::string_view search("Hello");
    EXPECT_EQ(sv.find(search), 0);
    
    // Test find() with position
    EXPECT_EQ(sv.find("Hello", 1), 14);
    EXPECT_EQ(sv.find("o", 5), 8);
    
    // Test rfind()
    EXPECT_EQ(sv.rfind("Hello"), 14);
    EXPECT_EQ(sv.rfind('o'), 25);
    EXPECT_EQ(sv.rfind("xyz"), std::string_view::npos);
    
    // Test find_first_of()
    EXPECT_EQ(sv.find_first_of("aeiou"), 1); // 'e'
    EXPECT_EQ(sv.find_first_of("AEIOU"), std::string_view::npos);
    
    // Test find_last_of()
    EXPECT_EQ(sv.find_last_of("aeiou"), 25); // 'e'
    EXPECT_EQ(sv.find_last_of("AEIOU"), std::string_view::npos);
    
    // Test find_first_not_of()
    EXPECT_EQ(sv.find_first_not_of("H"), 1);
    EXPECT_EQ(sv.find_first_not_of("Hello, World! "), 14);
    
    // Test find_last_not_of()
    EXPECT_EQ(sv.find_last_not_of("!"), 30);
    EXPECT_EQ(sv.find_last_not_of("Hello, World! Universe!"), std::string_view::npos);
}

/**
 * @test TestStringViewStartsWithEndsWith
 * @brief Test string_view starts_with and ends_with operations
 */
TEST_F(StringViewCoverageTest, TestStringViewStartsWithEndsWith) {
    std::string_view sv("Hello, World!");
    
    // Test starts_with() with character
    EXPECT_TRUE(sv.starts_with('H'));
    EXPECT_FALSE(sv.starts_with('h'));
    EXPECT_FALSE(sv.starts_with('W'));
    
    // Test starts_with() with string
    EXPECT_TRUE(sv.starts_with("Hello"));
    EXPECT_TRUE(sv.starts_with("Hello, World!"));
    EXPECT_FALSE(sv.starts_with("World"));
    EXPECT_FALSE(sv.starts_with("Hello, Universe!"));
    
    // Test starts_with() with string_view
    std::string_view prefix("Hello");
    EXPECT_TRUE(sv.starts_with(prefix));
    
    // Test ends_with() with character
    EXPECT_TRUE(sv.ends_with('!'));
    EXPECT_FALSE(sv.ends_with('?'));
    EXPECT_FALSE(sv.ends_with('d'));
    
    // Test ends_with() with string
    EXPECT_TRUE(sv.ends_with("World!"));
    EXPECT_TRUE(sv.ends_with("Hello, World!"));
    EXPECT_FALSE(sv.ends_with("Hello"));
    EXPECT_FALSE(sv.ends_with("Universe!"));
    
    // Test ends_with() with string_view
    std::string_view suffix("World!");
    EXPECT_TRUE(sv.ends_with(suffix));
}

/**
 * @test TestStringViewContains
 * @brief Test string_view contains operations
 */
TEST_F(StringViewCoverageTest, TestStringViewContains) {
    std::string_view sv("Hello, World!");
    
    // Test contains() with character
    EXPECT_TRUE(sv.contains('H'));
    EXPECT_TRUE(sv.contains('o'));
    EXPECT_TRUE(sv.contains('!'));
    EXPECT_FALSE(sv.contains('z'));
    
    // Test contains() with string
    EXPECT_TRUE(sv.contains("Hello"));
    EXPECT_TRUE(sv.contains("World"));
    EXPECT_TRUE(sv.contains("lo, Wo"));
    EXPECT_FALSE(sv.contains("xyz"));
    EXPECT_FALSE(sv.contains("Universe"));
    
    // Test contains() with string_view
    std::string_view search("lo, Wo");
    EXPECT_TRUE(sv.contains(search));
    
    std::string_view not_found("xyz");
    EXPECT_FALSE(sv.contains(not_found));
}

/**
 * @test TestStringViewRemovePrefixSuffix
 * @brief Test string_view remove_prefix and remove_suffix operations
 */
TEST_F(StringViewCoverageTest, TestStringViewRemovePrefixSuffix) {
    std::string_view sv("Hello, World!");
    
    // Test remove_prefix()
    sv.remove_prefix(7);
    EXPECT_EQ(sv, "World!");
    EXPECT_EQ(sv.size(), 6);
    
    // Reset and test remove_suffix()
    sv = "Hello, World!";
    sv.remove_suffix(7);
    EXPECT_EQ(sv, "Hello,");
    EXPECT_EQ(sv.size(), 6);
    
    // Test remove_prefix() and remove_suffix() together
    sv = "Hello, World!";
    sv.remove_prefix(7);
    sv.remove_suffix(1);
    EXPECT_EQ(sv, "World");
    EXPECT_EQ(sv.size(), 5);
    
    // Test with empty string_view
    std::string_view empty_sv;
    empty_sv.remove_prefix(0);
    empty_sv.remove_suffix(0);
    EXPECT_TRUE(empty_sv.empty());
}

/**
 * @test TestStringViewCopy
 * @brief Test string_view copy operations
 */
TEST_F(StringViewCoverageTest, TestStringViewCopy) {
    std::string_view sv("Hello, World!");
    char buffer[20];
    
    // Test copy() with full length
    size_t copied = sv.copy(buffer, sv.size());
    EXPECT_EQ(copied, sv.size());
    buffer[copied] = '\0';
    EXPECT_STREQ(buffer, "Hello, World!");
    
    // Test copy() with partial length
    copied = sv.copy(buffer, 5);
    EXPECT_EQ(copied, 5);
    buffer[copied] = '\0';
    EXPECT_STREQ(buffer, "Hello");
    
    // Test copy() with offset
    copied = sv.copy(buffer, 5, 7);
    EXPECT_EQ(copied, 5);
    buffer[copied] = '\0';
    EXPECT_STREQ(buffer, "World");
    
    // Test copy() with small buffer
    char small_buffer[3];
    copied = sv.copy(small_buffer, 2);
    EXPECT_EQ(copied, 2);
    small_buffer[copied] = '\0';
    EXPECT_STREQ(small_buffer, "He");
}

/**
 * @test TestStringViewHash
 * @brief Test string_view hash operations
 */
TEST_F(StringViewCoverageTest, TestStringViewHash) {
    std::string_view sv1("Hello, World!");
    std::string_view sv2("Hello, World!");
    std::string_view sv3("Hello, Universe!");
    
    // Test hash equality for same content
    std::hash<std::string_view> hasher;
    EXPECT_EQ(hasher(sv1), hasher(sv2));
    
    // Test hash difference for different content
    EXPECT_NE(hasher(sv1), hasher(sv3));
    
    // Test hash with empty string_view
    std::string_view empty_sv;
    EXPECT_EQ(hasher(empty_sv), hasher(empty_sv));
    
    // Test hash consistency
    auto hash1 = hasher(sv1);
    auto hash2 = hasher(sv1);
    EXPECT_EQ(hash1, hash2);
}

/**
 * @test TestStringViewEdgeCases
 * @brief Test string_view edge cases and boundary conditions
 */
TEST_F(StringViewCoverageTest, TestStringViewEdgeCases) {
    // Test empty string_view
    std::string_view empty_sv;
    EXPECT_TRUE(empty_sv.empty());
    EXPECT_EQ(empty_sv.size(), 0);
    EXPECT_EQ(empty_sv.data(), nullptr);
    
    // Test string_view with null character
    std::string_view null_sv("Hello\0World", 11);
    EXPECT_EQ(null_sv.size(), 11);
    EXPECT_EQ(null_sv[5], '\0');
    
    // Test string_view with single character
    std::string_view single_sv("A");
    EXPECT_EQ(single_sv.size(), 1);
    EXPECT_EQ(single_sv[0], 'A');
    EXPECT_EQ(single_sv.front(), 'A');
    EXPECT_EQ(single_sv.back(), 'A');
    
    // Test string_view with very long string
    std::string long_str(1000, 'A');
    std::string_view long_sv(long_str);
    EXPECT_EQ(long_sv.size(), 1000);
    EXPECT_EQ(long_sv[0], 'A');
    EXPECT_EQ(long_sv[999], 'A');
    
    // Test string_view with special characters
    std::string_view special_sv("!@#$%^&*()");
    EXPECT_EQ(special_sv.size(), 10);
    EXPECT_EQ(special_sv[0], '!');
    EXPECT_EQ(special_sv[9], ')');
}

/**
 * @test TestStringViewConstexpr
 * @brief Test string_view constexpr operations
 */
TEST_F(StringViewCoverageTest, TestStringViewConstexpr) {
    // Test constexpr construction
    constexpr std::string_view sv("Constexpr Test");
    static_assert(sv.size() == 14);
    static_assert(sv[0] == 'C');
    static_assert(sv[13] == 't');
    
    // Test constexpr operations
    constexpr std::string_view prefix = sv.substr(0, 9);
    static_assert(prefix == "Constexpr");
    
    constexpr std::string_view suffix = sv.substr(10);
    static_assert(suffix == "Test");
    
    // Test constexpr find
    constexpr size_t pos = sv.find("Test");
    static_assert(pos == 10);
    
    // Test constexpr starts_with
    static_assert(sv.starts_with("Constexpr"));
    static_assert(sv.ends_with("Test"));
}

/**
 * @test TestStringViewPerformance
 * @brief Test string_view performance characteristics
 */
TEST_F(StringViewCoverageTest, TestStringViewPerformance) {
    std::string large_string(10000, 'A');
    std::string_view sv(large_string);
    
    // Test that operations are O(1) or O(n) as expected
    auto start = std::chrono::high_resolution_clock::now();
    
    // Perform many operations
    for (int i = 0; i < 1000; ++i) {
        auto sub = sv.substr(1000, 1000);
        auto pos = sv.find("AAA");
        auto contains = sv.contains("BBB");
        (void)sub; (void)pos; (void)contains; // Suppress unused warnings
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Should complete quickly (this is more of a smoke test)
    EXPECT_LT(duration.count(), 1000000); // Less than 1 second
}

} // namespace
