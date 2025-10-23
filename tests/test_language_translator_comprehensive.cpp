/**
 * @file test_language_translator_comprehensive.cpp
 * @brief Comprehensive test file for LanguageTranslator to increase coverage
 * 
 * This test file targets all uncovered functions in LanguageTranslator
 * to achieve maximum line coverage
 */

#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "../src/LanguageTranslator/header/LanguageTranslator.h"

using namespace Coruh::LanguageTranslator;

class LanguageTranslatorComprehensiveTest : public ::testing::Test {
protected:
    void SetUp() override {
        app = std::make_unique<LanguageTranslatorApp>();
    }
    
    void TearDown() override {
        app.reset();
    }
    
    std::unique_ptr<LanguageTranslatorApp> app;
};

// Test constructor and basic initialization
TEST_F(LanguageTranslatorComprehensiveTest, TestConstructor) {
    EXPECT_FALSE(app->isUserLoggedIn());
    EXPECT_EQ(app->getSupportedLanguages().size(), 4); // English, Turkish, Spanish, French
}

// Test language management functions
TEST_F(LanguageTranslatorComprehensiveTest, TestLanguageManagement) {
    // Test setSourceLanguage
    app->setSourceLanguage("Spanish");
    app->setTargetLanguage("French");
    
    // Test addLanguage
    app->addLanguage("German");
    auto languages = app->getSupportedLanguages();
    EXPECT_TRUE(std::find(languages.begin(), languages.end(), "German") != languages.end());
}

// Test user management functions
TEST_F(LanguageTranslatorComprehensiveTest, TestUserManagement) {
    // Test registration
    EXPECT_TRUE(app->registerUser("testuser", "password123"));
    EXPECT_TRUE(app->registerUser("testuser2", "password456"));
    
    // Test login
    EXPECT_TRUE(app->login("testuser", "password123"));
    EXPECT_TRUE(app->isUserLoggedIn());
    
    // Test logout
    app->logout();
    EXPECT_FALSE(app->isUserLoggedIn());
    
    // Test invalid login
    EXPECT_FALSE(app->login("testuser", "wrongpassword"));
    EXPECT_FALSE(app->login("nonexistent", "password"));
}

// Test phrase library functions
TEST_F(LanguageTranslatorComprehensiveTest, TestPhraseLibrary) {
    // Test adding phrases
    app->addPhrase("Hello, how are you?", "greetings");
    app->addPhrase("Thank you very much", "politeness");
    app->addPhrase("Where is the bathroom?", "travel");
    
    // Test phrase translation
    std::string result = app->translatePhrase("Hello, how are you?");
    EXPECT_FALSE(result.empty());
}

// Test learning tips functions
TEST_F(LanguageTranslatorComprehensiveTest, TestLearningTips) {
    // Test adding learning tips
    app->addLearningTip("Practice daily for better results");
    app->addLearningTip("Use flashcards for vocabulary");
    app->addLearningTip("Listen to native speakers");
    
    // Test showing learning tips (should not crash)
    EXPECT_NO_THROW(app->showLearningTips());
}

// Test pronunciation guide functions
TEST_F(LanguageTranslatorComprehensiveTest, TestPronunciationGuide) {
    // Test adding pronunciation guides
    app->addPronunciation("hello", "heh-LOH");
    app->addPronunciation("world", "wurld");
    app->addPronunciation("thank you", "thangk yoo");
    
    // Test showing pronunciation guide (should not crash)
    EXPECT_NO_THROW(app->showPronunciationGuide());
}

// Test data management functions
TEST_F(LanguageTranslatorComprehensiveTest, TestDataManagement) {
    // Test initializeDefaultData (should not crash)
    EXPECT_NO_THROW(app->initializeDefaultData());
    
    // Test saveData (should not crash)
    EXPECT_NO_THROW(app->saveData());
    
    // Test loadData (should not crash)
    EXPECT_NO_THROW(app->loadData());
}

// Test dictionary management functions
TEST_F(LanguageTranslatorComprehensiveTest, TestDictionaryManagement) {
    // Test loadAllDictionaries (should not crash)
    EXPECT_NO_THROW(app->loadAllDictionaries());
    
    // Test loadDictionaryFromFile with non-existent file
    EXPECT_FALSE(app->loadDictionaryFromFile("English", "German", "nonexistent.txt"));
    
    // Test loadDictionaryFromFile with valid file (if it exists)
    std::filesystem::create_directory("dictionaries");
    std::ofstream testFile("dictionaries/test_en_de.txt");
    testFile << "hello=halo\nworld=welt\n";
    testFile.close();
    
    EXPECT_TRUE(app->loadDictionaryFromFile("English", "German", "dictionaries/test_en_de.txt"));
    
    // Clean up
    std::filesystem::remove("dictionaries/test_en_de.txt");
}

// Test API functions
TEST_F(LanguageTranslatorComprehensiveTest, TestAPIFunctions) {
    // Test isAPIAvailable
    EXPECT_FALSE(app->isAPIAvailable());
    
    // Test setAPIKey
    app->setAPIKey("test-api-key-123");
    
    // Test setAPIMode
    app->setAPIMode(true);
    app->setAPIMode(false);
    
    // Test Google API translation (should return empty string)
    std::string result = app->translateWithGoogleAPI("hello", "en", "tr");
    EXPECT_TRUE(result.empty());
    
    // Test Microsoft API translation (should return empty string)
    result = app->translateWithMicrosoftAPI("hello", "en", "tr");
    EXPECT_TRUE(result.empty());
}

// Test translation functions with various inputs
TEST_F(LanguageTranslatorComprehensiveTest, TestTranslationFunctions) {
    // Test translateWord
    std::string result = app->translateWord("hello");
    EXPECT_FALSE(result.empty());
    
    // Test translatePhrase
    result = app->translatePhrase("good morning");
    EXPECT_FALSE(result.empty());
    
    // Test translateText
    result = app->translateText("hello world");
    EXPECT_FALSE(result.empty());
    
    // Test with empty input
    result = app->translateWord("");
    EXPECT_TRUE(result.empty());
    
    result = app->translatePhrase("");
    EXPECT_TRUE(result.empty());
    
    result = app->translateText("");
    EXPECT_TRUE(result.empty());
}

// Test edge cases and error handling
TEST_F(LanguageTranslatorComprehensiveTest, TestEdgeCases) {
    // Test with very long text
    std::string longText(1000, 'a');
    std::string result = app->translateText(longText);
    EXPECT_FALSE(result.empty());
    
    // Test with special characters
    result = app->translateText("Hello, World! @#$%^&*()");
    EXPECT_FALSE(result.empty());
    
    // Test with numbers
    result = app->translateText("123 456 789");
    EXPECT_FALSE(result.empty());
    
    // Test with mixed languages
    result = app->translateText("hello merhaba hola");
    EXPECT_FALSE(result.empty());
}

// Test menu and choice handling
TEST_F(LanguageTranslatorComprehensiveTest, TestMenuHandling) {
    // Test handleUserChoice with various inputs
    EXPECT_NO_THROW(app->handleUserChoice(0)); // Exit
    EXPECT_NO_THROW(app->handleUserChoice(1)); // Login/Translate
    EXPECT_NO_THROW(app->handleUserChoice(2)); // Register/Change Languages
    EXPECT_NO_THROW(app->handleUserChoice(3)); // Phrase Library
    EXPECT_NO_THROW(app->handleUserChoice(4)); // Learning Tips
    EXPECT_NO_THROW(app->handleUserChoice(5)); // Pronunciation Guide
    EXPECT_NO_THROW(app->handleUserChoice(6)); // Logout
    EXPECT_NO_THROW(app->handleUserChoice(99)); // Invalid choice
}

// Test language selection
TEST_F(LanguageTranslatorComprehensiveTest, TestLanguageSelection) {
    // Test showLanguageSelection (should not crash)
    EXPECT_NO_THROW(app->showLanguageSelection());
}

// Test phrase library display
TEST_F(LanguageTranslatorComprehensiveTest, TestPhraseLibraryDisplay) {
    // Test showPhraseLibrary (should not crash)
    EXPECT_NO_THROW(app->showPhraseLibrary());
}

// Test with different language combinations
TEST_F(LanguageTranslatorComprehensiveTest, TestLanguageCombinations) {
    // Test English to Turkish
    app->setSourceLanguage("English");
    app->setTargetLanguage("Turkish");
    std::string result = app->translateText("hello world");
    EXPECT_FALSE(result.empty());
    
    // Test English to Spanish
    app->setSourceLanguage("English");
    app->setTargetLanguage("Spanish");
    result = app->translateText("hello world");
    EXPECT_FALSE(result.empty());
    
    // Test English to French
    app->setSourceLanguage("English");
    app->setTargetLanguage("French");
    result = app->translateText("hello world");
    EXPECT_FALSE(result.empty());
    
    // Test Turkish to English
    app->setSourceLanguage("Turkish");
    app->setTargetLanguage("English");
    result = app->translateText("merhaba dünya");
    EXPECT_FALSE(result.empty());
}

// Test performance with large datasets
TEST_F(LanguageTranslatorComprehensiveTest, TestPerformance) {
    // Add many phrases
    for (int i = 0; i < 100; ++i) {
        app->addPhrase("phrase " + std::to_string(i), "category" + std::to_string(i % 5));
    }
    
    // Add many learning tips
    for (int i = 0; i < 50; ++i) {
        app->addLearningTip("tip " + std::to_string(i));
    }
    
    // Add many pronunciations
    for (int i = 0; i < 50; ++i) {
        app->addPronunciation("word" + std::to_string(i), "pronunciation" + std::to_string(i));
    }
    
    // Test that everything still works
    EXPECT_NO_THROW(app->showPhraseLibrary());
    EXPECT_NO_THROW(app->showLearningTips());
    EXPECT_NO_THROW(app->showPronunciationGuide());
}
