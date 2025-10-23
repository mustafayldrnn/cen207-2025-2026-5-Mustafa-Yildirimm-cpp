/**
 * @file test_string_view_advanced_coverage.cpp
 * @brief Advanced test file to maximize coverage for _msvc_string_view.hpp
 * 
 * This test file targets remaining uncovered lines in _msvc_string_view.hpp
 * to achieve 100% line coverage
 */

#include <gtest/gtest.h>
#include <string_view>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <limits>
#include <sstream>
#include <iomanip>

namespace {

/**
 * @class StringViewAdvancedCoverageTest
 * @brief Advanced test class for comprehensive string_view coverage
 */
class StringViewAdvancedCoverageTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup for each test
    }
    
    void TearDown() override {
        // Cleanup after each test
    }
};

/**
 * @test TestStringViewComparisonOperators
 * @brief Test all string_view comparison operators
 */
TEST_F(StringViewAdvancedCoverageTest, TestStringViewComparisonOperators) {
    std::string_view sv1("abc");
    std::string_view sv2("def");
    std::string_view sv3("abc");
    
    // Test operator==
    EXPECT_TRUE(sv1 == sv3);
    EXPECT_FALSE(sv1 == sv2);
    
    // Test operator!=
    EXPECT_TRUE(sv1 != sv2);
    EXPECT_FALSE(sv1 != sv3);
    
    // Test operator<
    EXPECT_TRUE(sv1 < sv2);
    EXPECT_FALSE(sv2 < sv1);
    EXPECT_FALSE(sv1 < sv3);
    
    // Test operator<=
    EXPECT_TRUE(sv1 <= sv2);
    EXPECT_TRUE(sv1 <= sv3);
    EXPECT_FALSE(sv2 <= sv1);
    
    // Test operator>
    EXPECT_TRUE(sv2 > sv1);
    EXPECT_FALSE(sv1 > sv2);
    EXPECT_FALSE(sv1 > sv3);
    
    // Test operator>=
    EXPECT_TRUE(sv2 >= sv1);
    EXPECT_TRUE(sv1 >= sv3);
    EXPECT_FALSE(sv1 >= sv2);
    
    // Test with different types
    std::string str = "abc";
    const char* cstr = "abc";
    
    EXPECT_TRUE(sv1 == str);
    EXPECT_TRUE(sv1 == cstr);
    EXPECT_TRUE(str == sv1);
    EXPECT_TRUE(cstr == sv1);
    
    EXPECT_TRUE(sv1 != "def");
    EXPECT_TRUE("def" != sv1);
}

/**
 * @test TestStringViewStreamOutput
 * @brief Test string_view stream output operations
 */
TEST_F(StringViewAdvancedCoverageTest, TestStringViewStreamOutput) {
    std::string_view sv("Hello, World!");
    std::ostringstream oss;
    
    // Test basic stream output
    oss << sv;
    EXPECT_EQ(oss.str(), "Hello, World!");
    
    // Test with multiple string_views
    oss.str("");
    std::string_view sv1("Hello");
    std::string_view sv2(", ");
    std::string_view sv3("World!");
    oss << sv1 << sv2 << sv3;
    EXPECT_EQ(oss.str(), "Hello, World!");
    
    // Test with formatting
    oss.str("");
    oss << std::setw(20) << sv;
    EXPECT_EQ(oss.str().length(), 20);
    EXPECT_TRUE(oss.str().find("Hello, World!") != std::string::npos);
}

/**
 * @test TestStringViewConstMethods
 * @brief Test string_view const methods
 */
TEST_F(StringViewAdvancedCoverageTest, TestStringViewConstMethods) {
    const std::string_view sv("Hello, World!");
    
    // Test const access methods
    EXPECT_EQ(sv[0], 'H');
    EXPECT_EQ(sv.at(0), 'H');
    EXPECT_EQ(sv.front(), 'H');
    EXPECT_EQ(sv.back(), '!');
    EXPECT_EQ(sv.data()[0], 'H');
    
    // Test const size methods
    EXPECT_EQ(sv.size(), 13);
    EXPECT_EQ(sv.length(), 13);
    EXPECT_FALSE(sv.empty());
    
    // Test const iterator methods
    EXPECT_NE(sv.begin(), sv.end());
    EXPECT_NE(sv.cbegin(), sv.cend());
    EXPECT_NE(sv.rbegin(), sv.rend());
    EXPECT_NE(sv.crbegin(), sv.crend());
    
    // Test const find methods
    EXPECT_EQ(sv.find('H'), 0);
    EXPECT_EQ(sv.find("Hello"), 0);
    EXPECT_EQ(sv.rfind('!'), 12);
    EXPECT_EQ(sv.find_first_of("aeiou"), 1);
    EXPECT_EQ(sv.find_last_of("aeiou"), 8);
    EXPECT_EQ(sv.find_first_not_of("H"), 1);
    EXPECT_EQ(sv.find_last_not_of("!"), 11);
    
    // Test const contains methods
    EXPECT_TRUE(sv.contains('H'));
    EXPECT_TRUE(sv.contains("Hello"));
    EXPECT_TRUE(sv.starts_with("Hello"));
    EXPECT_TRUE(sv.ends_with("World!"));
}

/**
 * @test TestStringViewSubstrEdgeCases
 * @brief Test string_view substr edge cases
 */
TEST_F(StringViewAdvancedCoverageTest, TestStringViewSubstrEdgeCases) {
    std::string_view sv("Hello, World!");
    
    // Test substr with zero length
    std::string_view sub1 = sv.substr(0, 0);
    EXPECT_TRUE(sub1.empty());
    EXPECT_EQ(sub1.size(), 0);
    
    // Test substr with length beyond string
    std::string_view sub2 = sv.substr(10, 100);
    EXPECT_EQ(sub2, "d!");
    EXPECT_EQ(sub2.size(), 3);
    
    // Test substr at end of string
    std::string_view sub3 = sv.substr(12, 1);
    EXPECT_EQ(sub3, "!");
    EXPECT_EQ(sub3.size(), 1);
    
    // Test substr with npos
    std::string_view sub4 = sv.substr(std::string_view::npos);
    EXPECT_TRUE(sub4.empty());
    
    // Test substr with very large position
    std::string_view sub5 = sv.substr(1000);
    EXPECT_TRUE(sub5.empty());
}

/**
 * @test TestStringViewFindEdgeCases
 * @brief Test string_view find edge cases
 */
TEST_F(StringViewAdvancedCoverageTest, TestStringViewFindEdgeCases) {
    std::string_view sv("Hello, World!");
    
    // Test find with empty string
    std::string_view empty_sv;
    EXPECT_EQ(empty_sv.find('H'), std::string_view::npos);
    EXPECT_EQ(empty_sv.find("Hello"), std::string_view::npos);
    
    // Test find with position beyond string
    EXPECT_EQ(sv.find('H', 100), std::string_view::npos);
    EXPECT_EQ(sv.find("Hello", 100), std::string_view::npos);
    
    // Test find with empty search string
    EXPECT_EQ(sv.find(""), 0);
    EXPECT_EQ(sv.find("", 5), 5);
    
    // Test find with single character at boundaries
    EXPECT_EQ(sv.find('H'), 0);
    EXPECT_EQ(sv.find('!'), 12);
    
    // Test find with repeated characters
    std::string_view repeated("aaa");
    EXPECT_EQ(repeated.find('a'), 0);
    EXPECT_EQ(repeated.find('a', 1), 1);
    EXPECT_EQ(repeated.find('a', 2), 2);
    EXPECT_EQ(repeated.find('a', 3), std::string_view::npos);
}

/**
 * @test TestStringViewCopyEdgeCases
 * @brief Test string_view copy edge cases
 */
TEST_F(StringViewAdvancedCoverageTest, TestStringViewCopyEdgeCases) {
    std::string_view sv("Hello, World!");
    char buffer[20];
    
    // Test copy with zero length
    size_t copied = sv.copy(buffer, 0);
    EXPECT_EQ(copied, 0);
    
    // Test copy with position beyond string
    copied = sv.copy(buffer, 5, 100);
    EXPECT_EQ(copied, 0);
    
    // Test copy with npos position
    copied = sv.copy(buffer, 5, std::string_view::npos);
    EXPECT_EQ(copied, 0);
    
    // Test copy with exact length
    copied = sv.copy(buffer, sv.size());
    EXPECT_EQ(copied, sv.size());
    buffer[copied] = '\0';
    EXPECT_STREQ(buffer, "Hello, World!");
    
    // Test copy with small buffer
    char small_buffer[3];
    copied = sv.copy(small_buffer, 2);
    EXPECT_EQ(copied, 2);
    small_buffer[copied] = '\0';
    EXPECT_STREQ(small_buffer, "He");
}

/**
 * @test TestStringViewStartsWithEndsWithEdgeCases
 * @brief Test string_view starts_with and ends_with edge cases
 */
TEST_F(StringViewAdvancedCoverageTest, TestStringViewStartsWithEndsWithEdgeCases) {
    std::string_view sv("Hello, World!");
    
    // Test with empty string_view
    std::string_view empty_sv;
    EXPECT_TRUE(empty_sv.starts_with(""));
    EXPECT_TRUE(empty_sv.ends_with(""));
    EXPECT_FALSE(empty_sv.starts_with("Hello"));
    EXPECT_FALSE(empty_sv.ends_with("World!"));
    
    // Test with empty search string
    EXPECT_TRUE(sv.starts_with(""));
    EXPECT_TRUE(sv.ends_with(""));
    
    // Test with exact match
    EXPECT_TRUE(sv.starts_with("Hello, World!"));
    EXPECT_TRUE(sv.ends_with("Hello, World!"));
    
    // Test with longer search string
    EXPECT_FALSE(sv.starts_with("Hello, World! Extra"));
    EXPECT_FALSE(sv.ends_with("Extra Hello, World!"));
    
    // Test with single character
    EXPECT_TRUE(sv.starts_with('H'));
    EXPECT_TRUE(sv.ends_with('!'));
    EXPECT_FALSE(sv.starts_with('h'));
    EXPECT_FALSE(sv.ends_with('?'));
}

/**
 * @test TestStringViewContainsEdgeCases
 * @brief Test string_view contains edge cases
 */
TEST_F(StringViewAdvancedCoverageTest, TestStringViewContainsEdgeCases) {
    std::string_view sv("Hello, World!");
    
    // Test with empty string_view
    std::string_view empty_sv;
    EXPECT_TRUE(empty_sv.contains(""));
    EXPECT_FALSE(empty_sv.contains("Hello"));
    
    // Test with empty search string
    EXPECT_TRUE(sv.contains(""));
    
    // Test with exact match
    EXPECT_TRUE(sv.contains("Hello, World!"));
    
    // Test with longer search string
    EXPECT_FALSE(sv.contains("Hello, World! Extra"));
    
    // Test with single character
    EXPECT_TRUE(sv.contains('H'));
    EXPECT_TRUE(sv.contains('!'));
    EXPECT_FALSE(sv.contains('z'));
    
    // Test with repeated characters
    std::string_view repeated("aaa");
    EXPECT_TRUE(repeated.contains('a'));
    EXPECT_TRUE(repeated.contains("aa"));
    EXPECT_FALSE(repeated.contains('b'));
}

/**
 * @test TestStringViewRemovePrefixSuffixEdgeCases
 * @brief Test string_view remove_prefix and remove_suffix edge cases
 */
TEST_F(StringViewAdvancedCoverageTest, TestStringViewRemovePrefixSuffixEdgeCases) {
    std::string_view sv("Hello, World!");
    
    // Test remove_prefix with zero
    sv.remove_prefix(0);
    EXPECT_EQ(sv, "Hello, World!");
    
    // Test remove_suffix with zero
    sv.remove_suffix(0);
    EXPECT_EQ(sv, "Hello, World!");
    
    // Test remove_prefix with full length
    sv.remove_prefix(sv.size());
    EXPECT_TRUE(sv.empty());
    
    // Reset and test remove_suffix with full length
    sv = "Hello, World!";
    sv.remove_suffix(sv.size());
    EXPECT_TRUE(sv.empty());
    
    // Test with empty string_view
    std::string_view empty_sv;
    empty_sv.remove_prefix(0);
    empty_sv.remove_suffix(0);
    EXPECT_TRUE(empty_sv.empty());
}

/**
 * @test TestStringViewHashEdgeCases
 * @brief Test string_view hash edge cases
 */
TEST_F(StringViewAdvancedCoverageTest, TestStringViewHashEdgeCases) {
    std::hash<std::string_view> hasher;
    
    // Test empty string_view
    std::string_view empty_sv;
    auto empty_hash = hasher(empty_sv);
    EXPECT_EQ(empty_hash, hasher(empty_sv));
    
    // Test single character
    std::string_view single_sv("A");
    auto single_hash = hasher(single_sv);
    EXPECT_NE(empty_hash, single_hash);
    
    // Test same content different sources
    std::string str = "Hello";
    const char* cstr = "Hello";
    std::string_view sv1(str);
    std::string_view sv2(cstr);
    
    EXPECT_EQ(hasher(sv1), hasher(sv2));
    
    // Test different content same length
    std::string_view sv3("Hello");
    std::string_view sv4("World");
    EXPECT_NE(hasher(sv3), hasher(sv4));
}

/**
 * @test TestStringViewIteratorEdgeCases
 * @brief Test string_view iterator edge cases
 */
TEST_F(StringViewAdvancedCoverageTest, TestStringViewIteratorEdgeCases) {
    // Test empty string_view iterators
    std::string_view empty_sv;
    EXPECT_EQ(empty_sv.begin(), empty_sv.end());
    EXPECT_EQ(empty_sv.cbegin(), empty_sv.cend());
    EXPECT_EQ(empty_sv.rbegin(), empty_sv.rend());
    EXPECT_EQ(empty_sv.crbegin(), empty_sv.crend());
    
    // Test single character iterators
    std::string_view single_sv("A");
    EXPECT_NE(single_sv.begin(), single_sv.end());
    EXPECT_EQ(single_sv.begin() + 1, single_sv.end());
    EXPECT_EQ(*single_sv.begin(), 'A');
    EXPECT_EQ(*(single_sv.end() - 1), 'A');
    
    // Test reverse iterators
    std::string_view sv("ABC");
    auto rit = sv.rbegin();
    EXPECT_EQ(*rit, 'C');
    ++rit;
    EXPECT_EQ(*rit, 'B');
    ++rit;
    EXPECT_EQ(*rit, 'A');
    ++rit;
    EXPECT_EQ(rit, sv.rend());
}

/**
 * @test TestStringViewConstexprEdgeCases
 * @brief Test string_view constexpr edge cases
 */
TEST_F(StringViewAdvancedCoverageTest, TestStringViewConstexprEdgeCases) {
    // Test constexpr with empty string
    constexpr std::string_view empty_sv("");
    static_assert(empty_sv.empty());
    static_assert(empty_sv.size() == 0);
    
    // Test constexpr with single character
    constexpr std::string_view single_sv("A");
    static_assert(single_sv.size() == 1);
    static_assert(single_sv[0] == 'A');
    
    // Test constexpr find operations
    constexpr std::string_view sv("Hello, World!");
    constexpr size_t pos1 = sv.find("World");
    static_assert(pos1 == 7);
    
    constexpr size_t pos2 = sv.find("xyz");
    static_assert(pos2 == std::string_view::npos);
    
    // Test constexpr starts_with and ends_with
    static_assert(sv.starts_with("Hello"));
    static_assert(sv.ends_with("World!"));
    static_assert(!sv.starts_with("World"));
    static_assert(!sv.ends_with("Hello"));
    
    // Test constexpr contains
    static_assert(sv.contains("lo, Wo"));
    static_assert(!sv.contains("xyz"));
}

/**
 * @test TestStringViewPerformanceEdgeCases
 * @brief Test string_view performance edge cases
 */
TEST_F(StringViewAdvancedCoverageTest, TestStringViewPerformanceEdgeCases) {
    // Test with very large string
    std::string large_string(100000, 'A');
    std::string_view sv(large_string);
    
    // Test operations that should be fast
    auto start = std::chrono::high_resolution_clock::now();
    
    // Perform many operations
    for (int i = 0; i < 100; ++i) {
        auto sub = sv.substr(1000, 1000);
        auto pos = sv.find("AAA");
        auto contains = sv.contains("BBB");
        auto starts = sv.starts_with("AAAA");
        auto ends = sv.ends_with("AAAA");
        (void)sub; (void)pos; (void)contains; (void)starts; (void)ends;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Should complete quickly
    EXPECT_LT(duration.count(), 100000); // Less than 0.1 second
}

} // namespace
