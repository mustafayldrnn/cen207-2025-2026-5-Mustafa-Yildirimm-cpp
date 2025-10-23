/**
 * @file LanguageTranslator_test.cpp
 * @brief Unit tests for Language Translator Application
 */

#include <gtest/gtest.h>
#include "../src/LanguageTranslator/header/LanguageTranslator.h"

using namespace Coruh::LanguageTranslator;

class LanguageTranslatorTest : public ::testing::Test {
protected:
    void SetUp() override {
        app = new LanguageTranslatorApp();
    }
    
    void TearDown() override {
        delete app;
    }
    
    LanguageTranslatorApp* app;
};

// Basic Translation Tests
TEST_F(LanguageTranslatorTest, BasicWordTranslation) {
    EXPECT_EQ(app->translateText("hello"), "merhaba");
    EXPECT_EQ(app->translateText("world"), "dünya");
    EXPECT_EQ(app->translateText("good"), "iyi");
    EXPECT_EQ(app->translateText("water"), "su");
    EXPECT_EQ(app->translateText("house"), "ev");
}

TEST_F(LanguageTranslatorTest, PhraseTranslation) {
    EXPECT_EQ(app->translateText("good morning"), "günaydın");
    EXPECT_EQ(app->translateText("thank you"), "teşekkür ederim");
    EXPECT_EQ(app->translateText("how are you"), "nasılsın");
    EXPECT_EQ(app->translateText("nice to meet you"), "tanıştığımıza memnun oldum");
}

TEST_F(LanguageTranslatorTest, UnknownWordHandling) {
    // Unknown words should return as-is
    EXPECT_EQ(app->translateText("unknownword"), "unknownword");
    EXPECT_EQ(app->translateText("xyz123"), "xyz123");
    EXPECT_EQ(app->translateText(""), "");
}

TEST_F(LanguageTranslatorTest, MixedKnownUnknownWords) {
    // Mixed sentence with known and unknown words
    std::string result = app->translateText("hello unknownword world");
    EXPECT_TRUE(result.find("merhaba") != std::string::npos);
    EXPECT_TRUE(result.find("unknownword") != std::string::npos);
    EXPECT_TRUE(result.find("dünya") != std::string::npos);
}

TEST_F(LanguageTranslatorTest, SameLanguageTranslation) {
    // When source and target are same, return original text
    app->setSourceLanguage("English");
    app->setTargetLanguage("English");
    EXPECT_EQ(app->translateText("hello"), "hello");
    EXPECT_EQ(app->translateText("world"), "world");
}

// Language Management Tests
TEST_F(LanguageTranslatorTest, LanguageSwitching) {
    app->setSourceLanguage("English");
    app->setTargetLanguage("Turkish");
    EXPECT_EQ(app->translateText("hello"), "merhaba");
    
    app->setSourceLanguage("English");
    app->setTargetLanguage("Spanish");
    EXPECT_EQ(app->translateText("hello"), "hola");
}

TEST_F(LanguageTranslatorTest, GetSupportedLanguages) {
    auto languages = app->getSupportedLanguages();
    EXPECT_FALSE(languages.empty());
    EXPECT_TRUE(std::find(languages.begin(), languages.end(), "English") != languages.end());
    EXPECT_TRUE(std::find(languages.begin(), languages.end(), "Turkish") != languages.end());
}

TEST_F(LanguageTranslatorTest, AddNewLanguage) {
    app->addLanguage("Japanese");
    auto languages = app->getSupportedLanguages();
    EXPECT_TRUE(std::find(languages.begin(), languages.end(), "Japanese") != languages.end());
}

// User Management Tests
TEST_F(LanguageTranslatorTest, UserLogin) {
    EXPECT_FALSE(app->isUserLoggedIn());
    
    bool loginResult = app->login("admin", "admin");
    EXPECT_TRUE(loginResult);
    EXPECT_TRUE(app->isUserLoggedIn());
}

TEST_F(LanguageTranslatorTest, UserLogout) {
    app->login("admin", "admin");
    EXPECT_TRUE(app->isUserLoggedIn());
    
    app->logout();
    EXPECT_FALSE(app->isUserLoggedIn());
}

TEST_F(LanguageTranslatorTest, InvalidLogin) {
    bool loginResult = app->login("wronguser", "wrongpass");
    EXPECT_FALSE(loginResult);
    EXPECT_FALSE(app->isUserLoggedIn());
}

TEST_F(LanguageTranslatorTest, UserRegistration) {
    bool registerResult = app->registerUser("newuser", "newpass");
    EXPECT_TRUE(registerResult);
}

// Individual Translation Function Tests
TEST_F(LanguageTranslatorTest, TranslateWordFunction) {
    EXPECT_EQ(app->translateWord("hello"), "merhaba");
    EXPECT_EQ(app->translateWord("world"), "dünya");
    EXPECT_EQ(app->translateWord("unknown"), "unknown");
}

TEST_F(LanguageTranslatorTest, TranslatePhraseFunction) {
    EXPECT_EQ(app->translatePhrase("good morning"), "günaydın");
    EXPECT_EQ(app->translatePhrase("thank you"), "teşekkür ederim");
    EXPECT_EQ(app->translatePhrase("unknown phrase"), "unknown phrase");
}

// API Tests
TEST_F(LanguageTranslatorTest, APIModeToggle) {
    EXPECT_FALSE(app->isAPIAvailable());
    
    app->setAPIMode(true);
    app->setAPIKey("test_key");
    EXPECT_TRUE(app->isAPIAvailable());
    
    app->setAPIMode(false);
    EXPECT_FALSE(app->isAPIAvailable());
}

TEST_F(LanguageTranslatorTest, APIKeyManagement) {
    app->setAPIKey("test_api_key");
    app->setAPIMode(true);
    EXPECT_TRUE(app->isAPIAvailable());
    
    app->setAPIKey("");
    EXPECT_FALSE(app->isAPIAvailable());
}

// Edge Cases and Error Handling
TEST_F(LanguageTranslatorTest, EmptyStringTranslation) {
    EXPECT_EQ(app->translateText(""), "");
    EXPECT_EQ(app->translateWord(""), "");
    EXPECT_EQ(app->translatePhrase(""), "");
}

TEST_F(LanguageTranslatorTest, WhitespaceHandling) {
    EXPECT_EQ(app->translateText("  hello  "), "merhaba");
    EXPECT_EQ(app->translateText("   "), "");
}

TEST_F(LanguageTranslatorTest, SpecialCharacters) {
    EXPECT_EQ(app->translateText("hello!"), "merhaba!");
    EXPECT_EQ(app->translateText("hello, world"), "merhaba, dünya");
    EXPECT_EQ(app->translateText("hello.world"), "merhaba.dünya");
}

TEST_F(LanguageTranslatorTest, CaseInsensitiveTranslation) {
    EXPECT_EQ(app->translateText("HELLO"), "merhaba");
    EXPECT_EQ(app->translateText("Hello"), "merhaba");
    EXPECT_EQ(app->translateText("hELLo"), "merhaba");
}

// Data Management Tests
TEST_F(LanguageTranslatorTest, DataInitialization) {
    // Test that default data is loaded
    EXPECT_EQ(app->translateText("hello"), "merhaba");
    EXPECT_EQ(app->translateText("good morning"), "günaydın");
}

TEST_F(LanguageTranslatorTest, DataSaveLoad) {
    // These functions should not crash
    app->saveData();
    app->loadData();
    
    // Data should still be available after save/load
    EXPECT_EQ(app->translateText("hello"), "merhaba");
}

// Dictionary Management Tests
TEST_F(LanguageTranslatorTest, DictionaryFileLoading) {
    // Test dictionary file loading (file may not exist, should handle gracefully)
    bool result = app->loadDictionaryFromFile("English", "Turkish", "nonexistent_file.txt");
    EXPECT_FALSE(result); // File doesn't exist
    
    // Should still work with default data
    EXPECT_EQ(app->translateText("hello"), "merhaba");
}

TEST_F(LanguageTranslatorTest, LoadAllDictionaries) {
    // This should not crash even if files don't exist
    app->loadAllDictionaries();
    
    // Default translations should still work
    EXPECT_EQ(app->translateText("hello"), "merhaba");
}

// Performance and Stress Tests
TEST_F(LanguageTranslatorTest, LongTextTranslation) {
    std::string longText = "hello world good morning thank you water food house car book computer phone friend family work";
    std::string result = app->translateText(longText);
    
    // Should contain translated words
    EXPECT_TRUE(result.find("merhaba") != std::string::npos);
    EXPECT_TRUE(result.find("dünya") != std::string::npos);
    EXPECT_TRUE(result.find("günaydın") != std::string::npos);
}

TEST_F(LanguageTranslatorTest, RepeatedTranslation) {
    // Test multiple translations of same text
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(app->translateText("hello"), "merhaba");
    }
}

// Integration Tests
TEST_F(LanguageTranslatorTest, FullTranslationWorkflow) {
    // Login
    app->login("admin", "admin");
    EXPECT_TRUE(app->isUserLoggedIn());
    
    // Set languages
    app->setSourceLanguage("English");
    app->setTargetLanguage("Turkish");
    
    // Translate
    EXPECT_EQ(app->translateText("hello world"), "merhaba dünya");
    
    // Switch to Spanish
    app->setTargetLanguage("Spanish");
    EXPECT_EQ(app->translateText("hello world"), "hola mundo");
    
    // Logout
    app->logout();
    EXPECT_FALSE(app->isUserLoggedIn());
}
