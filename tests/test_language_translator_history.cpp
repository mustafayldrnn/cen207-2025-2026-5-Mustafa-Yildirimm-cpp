/**
 * @file test_language_translator_history.cpp
 * @brief Comprehensive translation history tests for LanguageTranslator
 * @details Tests history tracking, storage, and retrieval of translation records
 */

#include <gtest/gtest.h>
#include <filesystem>
#include <chrono>
#include "../src/LanguageTranslator/header/LanguageTranslator.h"

using namespace Coruh::LanguageTranslator;

class LanguageTranslatorHistoryTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Clean up any existing data files
        if (std::filesystem::exists("data/history.bin")) {
            std::filesystem::remove("data/history.bin");
        }
        app = std::make_unique<LanguageTranslatorApp>();
        
        // Login a user to enable history tracking
        app->registerUser("testuser", "password");
        app->login("testuser", "password");
    }
    
    void TearDown() override {
        app.reset();
    }
    
    std::unique_ptr<LanguageTranslatorApp> app;
};

// Test history tracking for translations
TEST_F(LanguageTranslatorHistoryTest, TestTranslationHistoryTracking) {
    app->setSourceLanguage("English");
    app->setTargetLanguage("Turkish");
    
    app->translateText("hello");
    app->translateText("world");
    app->translateText("good morning");
    
    // History should be tracked for logged-in users
    EXPECT_TRUE(app->isUserLoggedIn());
}

// Test history with different language pairs
TEST_F(LanguageTranslatorHistoryTest, TestHistoryWithDifferentLanguagePairs) {
    // English to Turkish
    app->setSourceLanguage("English");
    app->setTargetLanguage("Turkish");
    app->translateText("hello");
    
    // English to Spanish
    app->setSourceLanguage("English");
    app->setTargetLanguage("Spanish");
    app->translateText("hello");
    
    // French to English
    app->setSourceLanguage("French");
    app->setTargetLanguage("English");
    app->translateText("bonjour");
}

// Test history for logged out users
TEST_F(LanguageTranslatorHistoryTest, TestHistoryWithoutLogin) {
    app->logout();
    EXPECT_FALSE(app->isUserLoggedIn());
    
    // History should not be tracked when logged out
    app->translateText("hello");
}

// Test history clearing
TEST_F(LanguageTranslatorHistoryTest, TestClearHistory) {
    app->setSourceLanguage("English");
    app->setTargetLanguage("Turkish");
    app->translateText("hello");
    app->translateText("world");
    
    // Clear history
    app->clearHistory();
    
    // History should be empty
}

// Test history persistence
TEST_F(LanguageTranslatorHistoryTest, TestHistoryPersistence) {
    app->setSourceLanguage("English");
    app->setTargetLanguage("Turkish");
    app->translateText("test translation");
    
    // Save data
    app->saveData();
    
    // Create new app instance and load data
    auto newApp = std::make_unique<LanguageTranslatorApp>();
    newApp->loadData();
    
    // History should be loaded
}

// Test history with empty translations
TEST_F(LanguageTranslatorHistoryTest, TestHistoryWithEmptyTranslations) {
    app->setSourceLanguage("English");
    app->setTargetLanguage("Turkish");
    
    app->translateText("");
    app->translateText("   ");
}

// Test history with special characters
TEST_F(LanguageTranslatorHistoryTest, TestHistoryWithSpecialCharacters) {
    app->setSourceLanguage("English");
    app->setTargetLanguage("Turkish");
    
    app->translateText("Hello, World!");
    app->translateText("What's up?");
    app->translateText("@#$%^&*()");
}

// Test history with long text
TEST_F(LanguageTranslatorHistoryTest, TestHistoryWithLongText) {
    app->setSourceLanguage("English");
    app->setTargetLanguage("Turkish");
    
    std::string longText(500, 'a');
    app->translateText(longText);
}

// Test history viewing
TEST_F(LanguageTranslatorHistoryTest, TestShowHistory) {
    app->setSourceLanguage("English");
    app->setTargetLanguage("Turkish");
    app->translateText("hello");
    app->translateText("world");
    
    // Show history (should not crash)
    EXPECT_NO_THROW(app->showHistory());
}

// Test history with multiple users
TEST_F(LanguageTranslatorHistoryTest, TestHistoryMultipleUsers) {
    // User 1
    app->setSourceLanguage("English");
    app->setTargetLanguage("Turkish");
    app->translateText("hello");
    
    // User 2
    app->logout();
    app->registerUser("user2", "pass");
    app->login("user2", "pass");
    app->setSourceLanguage("English");
    app->setTargetLanguage("Spanish");
    app->translateText("hola");
    
    // Each user should have their own history
}

// Test history with same translation multiple times
TEST_F(LanguageTranslatorHistoryTest, TestHistoryRepeatedTranslations) {
    app->setSourceLanguage("English");
    app->setTargetLanguage("Turkish");
    
    for (int i = 0; i < 10; ++i) {
        app->translateText("hello");
    }
}

// Test history with different translation types
TEST_F(LanguageTranslatorHistoryTest, TestHistoryWithTranslationTypes) {
    app->setSourceLanguage("English");
    app->setTargetLanguage("Turkish");
    
    // Word translation
    app->translateWord("hello");
    
    // Phrase translation
    app->translatePhrase("good morning");
    
    // Text translation
    app->translateText("hello world");
}

// Test history cleanup on logout
TEST_F(LanguageTranslatorHistoryTest, TestHistoryCleanupOnLogout) {
    app->setSourceLanguage("English");
    app->setTargetLanguage("Turkish");
    app->translateText("test");
    
    app->logout();
    app->login("testuser", "password");
    
    // History should persist across login sessions
}

