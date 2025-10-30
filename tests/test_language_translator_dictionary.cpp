/**
 * @file test_language_translator_dictionary.cpp
 * @brief Comprehensive dictionary management tests for LanguageTranslator
 * @details Tests dictionary loading, word/phrase translation, and file-based dictionaries
 */

#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>
#include "../src/LanguageTranslator/header/LanguageTranslator.h"

using namespace Coruh::LanguageTranslator;

class LanguageTranslatorDictionaryTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create dictionaries directory
        std::filesystem::create_directory("dictionaries");
        app = std::make_unique<LanguageTranslatorApp>();
    }
    
    void TearDown() override {
        // Clean up test files
        if (std::filesystem::exists("dictionaries/test_en_de.txt")) {
            std::filesystem::remove("dictionaries/test_en_de.txt");
        }
        if (std::filesystem::exists("dictionaries/test_empty.txt")) {
            std::filesystem::remove("dictionaries/test_empty.txt");
        }
        if (std::filesystem::exists("dictionaries/test_comments.txt")) {
            std::filesystem::remove("dictionaries/test_comments.txt");
        }
        app.reset();
    }
    
    std::unique_ptr<LanguageTranslatorApp> app;
};

// Test dictionary file loading with valid format
TEST_F(LanguageTranslatorDictionaryTest, TestLoadValidDictionaryFile) {
    // Create a test dictionary file
    std::ofstream file("dictionaries/test_en_de.txt");
    file << "hello=halo\n";
    file << "world=welt\n";
    file << "good=gut\n";
    file << "morning=morgen\n";
    file.close();
    
    EXPECT_TRUE(app->loadDictionaryFromFile("English", "German", "dictionaries/test_en_de.txt"));
    
    app->setSourceLanguage("English");
    app->setTargetLanguage("German");
    EXPECT_EQ(app->translateWord("hello"), "halo");
    EXPECT_EQ(app->translateWord("world"), "welt");
}

// Test dictionary file loading with comments
TEST_F(LanguageTranslatorDictionaryTest, TestLoadDictionaryWithComments) {
    std::ofstream file("dictionaries/test_comments.txt");
    file << "# This is a comment\n";
    file << "hello=halo\n";
    file << "# Another comment\n";
    file << "world=welt\n";
    file.close();
    
    EXPECT_TRUE(app->loadDictionaryFromFile("English", "German", "dictionaries/test_comments.txt"));
    app->setSourceLanguage("English");
    app->setTargetLanguage("German");
    EXPECT_EQ(app->translateWord("hello"), "halo");
}

// Test empty dictionary file
TEST_F(LanguageTranslatorDictionaryTest, TestLoadEmptyDictionaryFile) {
    std::ofstream file("dictionaries/test_empty.txt");
    file.close();
    
    // Should not crash, might return false or true
    app->loadDictionaryFromFile("English", "German", "dictionaries/test_empty.txt");
}

// Test loading non-existent file
TEST_F(LanguageTranslatorDictionaryTest, TestLoadNonExistentFile) {
    EXPECT_FALSE(app->loadDictionaryFromFile("English", "German", "dictionaries/nonexistent.txt"));
}

// Test dictionary loading with whitespace trimming
TEST_F(LanguageTranslatorDictionaryTest, TestDictionaryWhitespaceTrimming) {
    std::ofstream file("dictionaries/test_en_de.txt");
    file << "  hello  :  halo  \n";
    file << "world:welt\n";
    file.close();
    
    app->loadDictionaryFromFile("English", "German", "dictionaries/test_en_de.txt");
    app->setSourceLanguage("English");
    app->setTargetLanguage("German");
    EXPECT_EQ(app->translateWord("hello"), "halo");
    EXPECT_EQ(app->translateWord("world"), "welt");
}

// Test multiple dictionary loading
TEST_F(LanguageTranslatorDictionaryTest, TestLoadMultipleDictionaries) {
    // Load English to Turkish
    app->setSourceLanguage("English");
    app->setTargetLanguage("Turkish");
    EXPECT_EQ(app->translateWord("hello"), "merhaba");
    
    // Load English to Spanish
    app->setSourceLanguage("English");
    app->setTargetLanguage("Spanish");
    EXPECT_EQ(app->translateWord("hello"), "hola");
    
    // Load English to French
    app->setSourceLanguage("English");
    app->setTargetLanguage("French");
    EXPECT_EQ(app->translateWord("hello"), "bonjour");
}

// Test all dictionaries loading
TEST_F(LanguageTranslatorDictionaryTest, TestLoadAllDictionaries) {
    EXPECT_NO_THROW(app->loadAllDictionaries());
    
    // Should have loaded multiple language pairs
    app->setSourceLanguage("English");
    app->setTargetLanguage("Turkish");
    EXPECT_EQ(app->translateWord("hello"), "merhaba");
}

// Test word translation with existing dictionary
TEST_F(LanguageTranslatorDictionaryTest, TestWordTranslation) {
    app->setSourceLanguage("English");
    app->setTargetLanguage("Turkish");
    
    EXPECT_EQ(app->translateWord("hello"), "merhaba");
    EXPECT_EQ(app->translateWord("world"), "dünya");
    EXPECT_EQ(app->translateWord("good"), "iyi");
    EXPECT_EQ(app->translateWord("water"), "su");
}

// Test phrase translation
TEST_F(LanguageTranslatorDictionaryTest, TestPhraseTranslation) {
    app->setSourceLanguage("English");
    app->setTargetLanguage("Turkish");
    
    EXPECT_EQ(app->translatePhrase("good morning"), "günaydın");
    EXPECT_EQ(app->translatePhrase("thank you"), "teşekkür ederim");
    EXPECT_EQ(app->translatePhrase("how are you"), "nasılsın");
}

// Test unknown word handling
TEST_F(LanguageTranslatorDictionaryTest, TestUnknownWordHandling) {
    app->setSourceLanguage("English");
    app->setTargetLanguage("Turkish");
    
    EXPECT_EQ(app->translateWord("unknownword"), "unknownword");
    EXPECT_EQ(app->translateWord("xyz123"), "xyz123");
}

// Test translation with different language pairs
TEST_F(LanguageTranslatorDictionaryTest, TestTranslationLanguagePairs) {
    // English to Spanish
    app->setSourceLanguage("English");
    app->setTargetLanguage("Spanish");
    EXPECT_EQ(app->translateWord("hello"), "hola");
    EXPECT_EQ(app->translateWord("world"), "mundo");
    
    // English to French
    app->setSourceLanguage("English");
    app->setTargetLanguage("French");
    EXPECT_EQ(app->translateWord("hello"), "bonjour");
    EXPECT_EQ(app->translateWord("world"), "monde");
}

// Test same language translation
TEST_F(LanguageTranslatorDictionaryTest, TestSameLanguageTranslation) {
    app->setSourceLanguage("English");
    app->setTargetLanguage("English");
    EXPECT_EQ(app->translateWord("hello"), "hello");
    EXPECT_EQ(app->translateText("hello world"), "hello world");
}

// Test dictionary with malformed entries
TEST_F(LanguageTranslatorDictionaryTest, TestMalformedDictionaryEntries) {
    std::ofstream file("dictionaries/test_en_de.txt");
    file << "nocolon\n";
    file << "only=word=\n";
    file << "valid:entry\n";
    file.close();
    
    app->loadDictionaryFromFile("English", "German", "dictionaries/test_en_de.txt");
    app->setSourceLanguage("English");
    app->setTargetLanguage("German");
    // Should handle malformed entries gracefully
}

// Test translation with mixed case
TEST_F(LanguageTranslatorDictionaryTest, TestMixedCaseTranslation) {
    app->setSourceLanguage("English");
    app->setTargetLanguage("Turkish");
    
    // Dictionary is case-sensitive
    EXPECT_EQ(app->translateWord("HELLO"), "HELLO");
    EXPECT_EQ(app->translateWord("Hello"), "Hello");
}

// Test large dictionary loading
TEST_F(LanguageTranslatorDictionaryTest, TestLargeDictionaryLoading) {
    std::ofstream file("dictionaries/test_en_de.txt");
    for (int i = 0; i < 100; ++i) {
        file << "word" << i << "=wort" << i << "\n";
    }
    file.close();
    
    app->loadDictionaryFromFile("English", "German", "dictionaries/test_en_de.txt");
    app->setSourceLanguage("English");
    app->setTargetLanguage("German");
    EXPECT_EQ(app->translateWord("word50"), "wort50");
}

