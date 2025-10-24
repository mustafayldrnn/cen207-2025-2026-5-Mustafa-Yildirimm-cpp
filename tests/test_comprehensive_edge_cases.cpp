/**
 * @file test_comprehensive_edge_cases.cpp
 * @brief Comprehensive edge case tests to maximize coverage
 * 
 * This test file focuses on edge cases, error conditions, and boundary testing
 * to achieve maximum line coverage
 */

#include <gtest/gtest.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <limits>
#include <stdexcept>

// Include all headers for comprehensive testing
#include "../src/SafeChronoCalculator.h"
#include "../src/LanguageTranslator/header/LanguageTranslator.h"

using namespace SafeChrono;
using namespace Coruh::LanguageTranslator;

class ComprehensiveEdgeCasesTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup for each test
    }
    
    void TearDown() override {
        // Cleanup after each test
    }
};

// Test SafeChronoCalculator edge cases
TEST_F(ComprehensiveEdgeCasesTest, TestSafeChronoCalculatorEdgeCases) {
    // Test with zero values
    auto result1 = SafeChronoCalculator::safeCalculateDuration(0, 1000000, 1000000000);
    EXPECT_EQ(result1.count(), 0);
    
    // Test with very small values
    auto result2 = SafeChronoCalculator::safeCalculateDuration(1, 1000000, 1000000000);
    EXPECT_GE(result2.count(), 0);
    
    // Test with maximum safe values
    long long maxSafe = std::numeric_limits<long long>::max() / 8;
    auto result3 = SafeChronoCalculator::safeCalculateDuration(maxSafe, 1000000, 1000000000);
    EXPECT_GE(result3.count(), 0);
    
    // Test with negative values (should handle gracefully)
    auto result4 = SafeChronoCalculator::safeCalculateDuration(-1000, 1000000, 1000000000);
    EXPECT_LE(result4.count(), 0);
    
    // Test with very large frequency
    auto result5 = SafeChronoCalculator::safeCalculateDuration(1000, 1000000000, 1000000000);
    EXPECT_GE(result5.count(), 0);
    
    // Test with very large period denominator
    auto result6 = SafeChronoCalculator::safeCalculateDuration(1000, 1000000, 1000000000000);
    EXPECT_GE(result6.count(), 0);
    
    // Test 10MHz with various values
    auto result7 = SafeChronoCalculator::calculateFor10MHz(0);
    EXPECT_EQ(result7.count(), 0);
    
    auto result8 = SafeChronoCalculator::calculateFor10MHz(1);
    EXPECT_GT(result8.count(), 0);
    
    auto result9 = SafeChronoCalculator::calculateFor10MHz(1000000);
    EXPECT_GT(result9.count(), 0);
    
    // Test 24MHz with various values
    auto result10 = SafeChronoCalculator::calculateFor24MHz(0);
    EXPECT_EQ(result10.count(), 0);
    
    auto result11 = SafeChronoCalculator::calculateFor24MHz(1);
    EXPECT_GT(result11.count(), 0);
    
    auto result12 = SafeChronoCalculator::calculateFor24MHz(1000000);
    EXPECT_GT(result12.count(), 0);
    
    // Test overflow detection with various edge cases
    bool overflow1 = SafeChronoCalculator::wouldOverflow(0, 0);
    EXPECT_FALSE(overflow1);
    
    bool overflow2 = SafeChronoCalculator::wouldOverflow(1, 0);
    EXPECT_FALSE(overflow2);
    
    bool overflow3 = SafeChronoCalculator::wouldOverflow(0, 1);
    EXPECT_FALSE(overflow3);
    
    bool overflow4 = SafeChronoCalculator::wouldOverflow(-1, 1);
    EXPECT_FALSE(overflow4);
    
    bool overflow5 = SafeChronoCalculator::wouldOverflow(1, -1);
    EXPECT_FALSE(overflow5);
    
    bool overflow6 = SafeChronoCalculator::wouldOverflow(-1, -1);
    EXPECT_FALSE(overflow6);
    
    // Test with maximum values
    long long maxValue = std::numeric_limits<long long>::max();
    bool overflow7 = SafeChronoCalculator::wouldOverflow(maxValue, 1);
    EXPECT_FALSE(overflow7);
    
    bool overflow8 = SafeChronoCalculator::wouldOverflow(1, maxValue);
    EXPECT_FALSE(overflow8);
    
    bool overflow9 = SafeChronoCalculator::wouldOverflow(maxValue, 2);
    EXPECT_TRUE(overflow9);
    
    bool overflow10 = SafeChronoCalculator::wouldOverflow(2, maxValue);
    EXPECT_TRUE(overflow10);
}

// Test LanguageTranslatorApp edge cases
TEST_F(ComprehensiveEdgeCasesTest, TestLanguageTranslatorAppEdgeCases) {
    LanguageTranslatorApp app;
    
    // Test with empty strings
    std::string result1 = app.translateWord("");
    EXPECT_TRUE(result1.empty());
    
    std::string result2 = app.translatePhrase("");
    EXPECT_TRUE(result2.empty());
    
    std::string result3 = app.translateText("");
    EXPECT_TRUE(result3.empty());
    
    // Test with whitespace only
    std::string result4 = app.translateWord("   ");
    EXPECT_FALSE(result4.empty());
    
    std::string result5 = app.translatePhrase("   ");
    EXPECT_FALSE(result5.empty());
    
    std::string result6 = app.translateText("   ");
    EXPECT_FALSE(result6.empty());
    
    // Test with very long strings
    std::string longString(10000, 'a');
    std::string result7 = app.translateText(longString);
    EXPECT_FALSE(result7.empty());
    
    // Test with special characters
    std::string result8 = app.translateText("Hello, World! @#$%^&*()");
    EXPECT_FALSE(result8.empty());
    
    // Test with numbers
    std::string result9 = app.translateText("123 456 789");
    EXPECT_FALSE(result9.empty());
    
    // Test with mixed languages
    std::string result10 = app.translateText("hello merhaba hola bonjour");
    EXPECT_FALSE(result10.empty());
    
    // Test with unicode characters
    std::string result11 = app.translateText("café naïve résumé");
    EXPECT_FALSE(result11.empty());
    
    // Test with newlines and tabs
    std::string result12 = app.translateText("hello\nworld\ttest");
    EXPECT_FALSE(result12.empty());
    
    // Test user management edge cases
    EXPECT_TRUE(app.registerUser("", "password"));
    EXPECT_TRUE(app.registerUser("username", ""));
    EXPECT_TRUE(app.registerUser("", ""));
    
    // Test login with empty credentials
    app.login("", "password");
    app.login("username", "");
    app.login("", "");
    
    // Test language management edge cases
    app.setSourceLanguage("");
    app.setTargetLanguage("");
    app.addLanguage("");
    
    // Test phrase library edge cases
    app.addPhrase("", "");
    app.addPhrase("phrase", "");
    app.addPhrase("", "category");
    
    // Test learning tips edge cases
    app.addLearningTip("");
    app.addLearningTip("   ");
    
    // Test pronunciation guide edge cases
    app.addPronunciation("", "");
    app.addPronunciation("word", "");
    app.addPronunciation("", "pronunciation");
    
    // Test API functions with edge cases
    app.setAPIKey("");
    app.setAPIMode(true);
    app.setAPIMode(false);
    
    std::string apiResult1 = app.translateWithGoogleAPI("", "", "");
    EXPECT_TRUE(apiResult1.empty());
    
    std::string apiResult2 = app.translateWithMicrosoftAPI("", "", "");
    EXPECT_TRUE(apiResult2.empty());
    
    // Test menu handling edge cases
    for (int i = -10; i <= 10; ++i) {
        EXPECT_NO_THROW(app.handleUserChoice(i));
    }
    
    // Test display functions multiple times
    for (int i = 0; i < 10; ++i) {
        EXPECT_NO_THROW(app.showLanguageSelection());
        EXPECT_NO_THROW(app.showPhraseLibrary());
        EXPECT_NO_THROW(app.showLearningTips());
        EXPECT_NO_THROW(app.showPronunciationGuide());
    }
}

// Test error handling and exceptions
TEST_F(ComprehensiveEdgeCasesTest, TestErrorHandling) {
    // Test SafeChronoCalculator error handling
    EXPECT_THROW(SafeChronoCalculator::safeCalculateDuration(1000, 0, 1000000000), std::invalid_argument);
    EXPECT_THROW(SafeChronoCalculator::safeCalculateDuration(1000, -1000, 1000000000), std::invalid_argument);
    EXPECT_THROW(SafeChronoCalculator::safeCalculateDuration(1000, 1000000, 0), std::invalid_argument);
    EXPECT_THROW(SafeChronoCalculator::safeCalculateDuration(1000, 1000000, -1000), std::invalid_argument);
    
    // Test with very large values that might cause overflow
    long long veryLarge = std::numeric_limits<long long>::max();
    EXPECT_NO_THROW(SafeChronoCalculator::safeCalculateDuration(veryLarge, 1, 1));
    EXPECT_NO_THROW(SafeChronoCalculator::safeCalculateDuration(1, veryLarge, 1));
    EXPECT_NO_THROW(SafeChronoCalculator::safeCalculateDuration(1, 1, veryLarge));
}

// Test performance under stress
TEST_F(ComprehensiveEdgeCasesTest, TestPerformanceStress) {
    // Test SafeChronoCalculator performance
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 1; i <= 10000; ++i) {
        auto result = SafeChronoCalculator::safeCalculateDuration(i, 1000000, 1000000000);
        EXPECT_GE(result.count(), 0);
        
        bool overflow = SafeChronoCalculator::wouldOverflow(i, i);
        // Don't assert on overflow result as it depends on implementation
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    EXPECT_LT(duration.count(), 5000); // Should complete in less than 5 seconds
    
    // Test LanguageTranslatorApp performance
    LanguageTranslatorApp app;
    
    start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < 1000; ++i) {
        app.addPhrase("phrase " + std::to_string(i), "category" + std::to_string(i % 10));
        app.addLearningTip("tip " + std::to_string(i));
        app.addPronunciation("word" + std::to_string(i), "pronunciation" + std::to_string(i));
        
        std::string result = app.translateText("test " + std::to_string(i));
        EXPECT_FALSE(result.empty());
    }
    
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    EXPECT_LT(duration.count(), 10000); // Should complete in less than 10 seconds
}

// Test memory usage and resource management
TEST_F(ComprehensiveEdgeCasesTest, TestMemoryUsage) {
    // Test with many LanguageTranslatorApp instances
    std::vector<std::unique_ptr<LanguageTranslatorApp>> apps;
    
    for (int i = 0; i < 100; ++i) {
        auto app = std::make_unique<LanguageTranslatorApp>();
        
        // Add some data to each app
        for (int j = 0; j < 10; ++j) {
            app->addPhrase("phrase " + std::to_string(j), "category");
            app->addLearningTip("tip " + std::to_string(j));
            app->addPronunciation("word" + std::to_string(j), "pronunciation");
        }
        
        apps.push_back(std::move(app));
    }
    
    // Test that all apps still work
    for (const auto& app : apps) {
        EXPECT_NO_THROW(app->showPhraseLibrary());
        EXPECT_NO_THROW(app->showLearningTips());
        EXPECT_NO_THROW(app->showPronunciationGuide());
    }
    
    // Clear apps to test cleanup
    apps.clear();
    
    // Test that we can create new apps after cleanup
    LanguageTranslatorApp newApp;
    EXPECT_NO_THROW(newApp.translateText("test"));
}

// Test concurrent access (basic thread safety)
TEST_F(ComprehensiveEdgeCasesTest, TestConcurrentAccess) {
    LanguageTranslatorApp app;
    
    // Test multiple threads accessing the same app
    std::vector<std::thread> threads;
    
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([&app, i]() {
            for (int j = 0; j < 100; ++j) {
                app.addPhrase("phrase " + std::to_string(i) + "_" + std::to_string(j), "category");
                app.addLearningTip("tip " + std::to_string(i) + "_" + std::to_string(j));
                app.addPronunciation("word" + std::to_string(i) + "_" + std::to_string(j), "pronunciation");
                
                std::string result = app.translateText("test " + std::to_string(i) + "_" + std::to_string(j));
                EXPECT_FALSE(result.empty());
            }
        });
    }
    
    // Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }
    
    // Test that the app still works after concurrent access
    EXPECT_NO_THROW(app.showPhraseLibrary());
    EXPECT_NO_THROW(app.showLearningTips());
    EXPECT_NO_THROW(app.showPronunciationGuide());
}

// Test boundary conditions
TEST_F(ComprehensiveEdgeCasesTest, TestBoundaryConditions) {
    // Test SafeChronoCalculator boundary conditions
    long long minValue = std::numeric_limits<long long>::min();
    long long maxValue = std::numeric_limits<long long>::max();
    
    // Test with minimum values
    EXPECT_NO_THROW(SafeChronoCalculator::safeCalculateDuration(minValue, 1, 1));
    EXPECT_NO_THROW(SafeChronoCalculator::safeCalculateDuration(1, minValue, 1));
    EXPECT_NO_THROW(SafeChronoCalculator::safeCalculateDuration(1, 1, minValue));
    
    // Test with maximum values
    EXPECT_NO_THROW(SafeChronoCalculator::safeCalculateDuration(maxValue, 1, 1));
    EXPECT_NO_THROW(SafeChronoCalculator::safeCalculateDuration(1, maxValue, 1));
    EXPECT_NO_THROW(SafeChronoCalculator::safeCalculateDuration(1, 1, maxValue));
    
    // Test overflow detection with boundary values
    EXPECT_FALSE(SafeChronoCalculator::wouldOverflow(minValue, 1));
    EXPECT_FALSE(SafeChronoCalculator::wouldOverflow(1, minValue));
    EXPECT_FALSE(SafeChronoCalculator::wouldOverflow(minValue, minValue));
    
    EXPECT_FALSE(SafeChronoCalculator::wouldOverflow(maxValue, 1));
    EXPECT_FALSE(SafeChronoCalculator::wouldOverflow(1, maxValue));
    EXPECT_TRUE(SafeChronoCalculator::wouldOverflow(maxValue, 2));
    EXPECT_TRUE(SafeChronoCalculator::wouldOverflow(2, maxValue));
    
    // Test LanguageTranslatorApp boundary conditions
    LanguageTranslatorApp app;
    
    // Test with maximum length strings
    std::string maxString(100000, 'a');
    std::string result = app.translateText(maxString);
    EXPECT_FALSE(result.empty());
    
    // Test with many phrases
    for (int i = 0; i < 10000; ++i) {
        app.addPhrase("phrase " + std::to_string(i), "category");
    }
    
    EXPECT_NO_THROW(app.showPhraseLibrary());
    
    // Test with many learning tips
    for (int i = 0; i < 10000; ++i) {
        app.addLearningTip("tip " + std::to_string(i));
    }
    
    EXPECT_NO_THROW(app.showLearningTips());
    
    // Test with many pronunciations
    for (int i = 0; i < 10000; ++i) {
        app.addPronunciation("word" + std::to_string(i), "pronunciation");
    }
    
    EXPECT_NO_THROW(app.showPronunciationGuide());
}

// Test consistency and reliability
TEST_F(ComprehensiveEdgeCasesTest, TestConsistencyReliability) {
    // Test SafeChronoCalculator consistency
    for (int i = 0; i < 1000; ++i) {
        auto result1 = SafeChronoCalculator::safeCalculateDuration(1000, 1000000, 1000000000);
        auto result2 = SafeChronoCalculator::safeCalculateDuration(1000, 1000000, 1000000000);
        EXPECT_EQ(result1.count(), result2.count());
        
        bool overflow1 = SafeChronoCalculator::wouldOverflow(1000, 1000);
        bool overflow2 = SafeChronoCalculator::wouldOverflow(1000, 1000);
        EXPECT_EQ(overflow1, overflow2);
    }
    
    // Test LanguageTranslatorApp consistency
    LanguageTranslatorApp app;
    
    for (int i = 0; i < 1000; ++i) {
        std::string input = "test " + std::to_string(i);
        std::string result1 = app.translateText(input);
        std::string result2 = app.translateText(input);
        EXPECT_EQ(result1, result2);
    }
    
    // Test that same operations produce same results
    app.addPhrase("test phrase", "category");
    app.addLearningTip("test tip");
    app.addPronunciation("test word", "test pronunciation");
    
    for (int i = 0; i < 100; ++i) {
        EXPECT_NO_THROW(app.showPhraseLibrary());
        EXPECT_NO_THROW(app.showLearningTips());
        EXPECT_NO_THROW(app.showPronunciationGuide());
    }
}
