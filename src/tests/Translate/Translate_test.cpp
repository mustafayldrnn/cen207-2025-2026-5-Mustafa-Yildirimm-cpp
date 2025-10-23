/**
 * @file Translate_test.cpp
 * @brief Basic Language Translator test file
 */

#include <gtest/gtest.h>
#include "../../Translate/header/Translate.h"

using namespace Coruh::Translate;

class TranslateTest : public ::testing::Test {
protected:
    void SetUp() override {
        translator = new Translate();
    }
    
    void TearDown() override {
        delete translator;
    }
    
    Translate* translator;
};

TEST_F(TranslateTest, EnglishToTurkishTranslation) {
    EXPECT_EQ(translator->translate("en", "tr", "hello"), "merhaba");
    EXPECT_EQ(translator->translate("en", "tr", "world"), "dünya");
    EXPECT_EQ(translator->translate("en", "tr", "house"), "ev");
}

TEST_F(TranslateTest, EnglishToSpanishTranslation) {
    EXPECT_EQ(translator->translate("en", "es", "hello"), "hola");
    EXPECT_EQ(translator->translate("en", "es", "world"), "mundo");
    EXPECT_EQ(translator->translate("en", "es", "house"), "casa");
}

TEST_F(TranslateTest, CaseInsensitiveTranslation) {
    EXPECT_EQ(translator->translate("en", "tr", "HELLO"), "merhaba");
    EXPECT_EQ(translator->translate("en", "tr", "Hello"), "merhaba");
    EXPECT_EQ(translator->translate("en", "es", "WORLD"), "mundo");
    EXPECT_EQ(translator->translate("en", "es", "World"), "mundo");
}

TEST_F(TranslateTest, AddNewTranslation) {
    translator->addTranslation("en", "tr", "test", "deneme");
    EXPECT_EQ(translator->translate("en", "tr", "test"), "deneme");
}

TEST_F(TranslateTest, TranslationNotFound) {
    EXPECT_THROW(translator->translate("en", "tr", "nonexistent"), std::invalid_argument);
    EXPECT_THROW(translator->translate("en", "es", "bulunmayan"), std::invalid_argument);
}

TEST_F(TranslateTest, UnsupportedLanguage) {
    EXPECT_THROW(translator->translate("xx", "tr", "hello"), std::invalid_argument);
    EXPECT_THROW(translator->translate("en", "xx", "hello"), std::invalid_argument);
}

TEST_F(TranslateTest, GetTranslations) {
    auto translations = translator->getTranslations("en", "tr");
    EXPECT_GT(translations.size(), 0);
    
    // Check if hello-merhaba translation exists
    bool found = false;
    for (const auto& pair : translations) {
        if (pair.first == "hello" && pair.second == "merhaba") {
            found = true;
            break;
        }
    }
    EXPECT_TRUE(found);
}

TEST_F(TranslateTest, GetSupportedLanguages) {
    auto languages = translator->getSupportedLanguages();
    EXPECT_GT(languages.size(), 0);
    
    // Check if English and Turkish are supported
    bool foundEnglish = false;
    bool foundTurkish = false;
    for (const auto& lang : languages) {
        if (lang == "en") foundEnglish = true;
        if (lang == "tr") foundTurkish = true;
    }
    EXPECT_TRUE(foundEnglish);
    EXPECT_TRUE(foundTurkish);
}

TEST_F(TranslateTest, IsLanguageSupported) {
    EXPECT_TRUE(translator->isLanguageSupported("en"));
    EXPECT_TRUE(translator->isLanguageSupported("tr"));
    EXPECT_TRUE(translator->isLanguageSupported("es"));
    EXPECT_FALSE(translator->isLanguageSupported("xx"));
}

TEST_F(TranslateTest, AddSupportedLanguage) {
    translator->addSupportedLanguage("it");
    EXPECT_TRUE(translator->isLanguageSupported("it"));
}

TEST_F(TranslateTest, GetWordsByLanguage) {
    auto englishWords = translator->getWordsByLanguage("en");
    EXPECT_GT(englishWords.size(), 0);
    
    // Check if "hello" is in English words
    bool foundHello = false;
    for (const auto& word : englishWords) {
        if (word == "hello") {
            foundHello = true;
            break;
        }
    }
    EXPECT_TRUE(foundHello);
}

// Additional Edge Case Tests
TEST_F(TranslateTest, EmptyStringTranslation) {
    EXPECT_THROW(translator->translate("en", "tr", ""), std::invalid_argument);
}

TEST_F(TranslateTest, WhitespaceHandling) {
    EXPECT_THROW(translator->translate("en", "tr", "   "), std::invalid_argument);
    EXPECT_THROW(translator->translate("en", "tr", "\t\n"), std::invalid_argument);
}

TEST_F(TranslateTest, SpecialCharacters) {
    EXPECT_THROW(translator->translate("en", "tr", "hello!"), std::invalid_argument);
    EXPECT_THROW(translator->translate("en", "tr", "hello, world"), std::invalid_argument);
}

TEST_F(TranslateTest, NumbersInTranslation) {
    EXPECT_THROW(translator->translate("en", "tr", "hello123"), std::invalid_argument);
    EXPECT_THROW(translator->translate("en", "tr", "123hello"), std::invalid_argument);
}

TEST_F(TranslateTest, MultipleTranslationsSameWord) {
    // Add multiple translations for same word
    translator->addTranslation("en", "tr", "test", "deneme1");
    translator->addTranslation("en", "tr", "test", "deneme2");
    
    // Should get the last added translation
    EXPECT_EQ(translator->translate("en", "tr", "test"), "deneme2");
}

TEST_F(TranslateTest, TranslationOverwrite) {
    // Add translation
    translator->addTranslation("en", "tr", "new", "yeni");
    EXPECT_EQ(translator->translate("en", "tr", "new"), "yeni");
    
    // Overwrite translation
    translator->addTranslation("en", "tr", "new", "yeniden");
    EXPECT_EQ(translator->translate("en", "tr", "new"), "yeniden");
}

TEST_F(TranslateTest, GetTranslationsEmptyLanguage) {
    auto translations = translator->getTranslations("xx", "yy");
    EXPECT_EQ(translations.size(), 0);
}

TEST_F(TranslateTest, GetWordsByLanguageEmpty) {
    auto words = translator->getWordsByLanguage("xx");
    EXPECT_EQ(words.size(), 0);
}

TEST_F(TranslateTest, AddTranslationInvalidLanguage) {
    EXPECT_THROW(translator->addTranslation("xx", "tr", "test", "deneme"), std::invalid_argument);
    EXPECT_THROW(translator->addTranslation("en", "xx", "test", "deneme"), std::invalid_argument);
}

TEST_F(TranslateTest, AddTranslationEmptyWord) {
    EXPECT_THROW(translator->addTranslation("en", "tr", "", "deneme"), std::invalid_argument);
    EXPECT_THROW(translator->addTranslation("en", "tr", "test", ""), std::invalid_argument);
}

TEST_F(TranslateTest, AddSupportedLanguageDuplicate) {
    // Add language
    translator->addSupportedLanguage("it");
    EXPECT_TRUE(translator->isLanguageSupported("it"));
    
    // Add same language again (should not crash)
    translator->addSupportedLanguage("it");
    EXPECT_TRUE(translator->isLanguageSupported("it"));
}

TEST_F(TranslateTest, GetSupportedLanguagesAfterAdding) {
    size_t initialSize = translator->getSupportedLanguages().size();
    
    translator->addSupportedLanguage("it");
    
    auto languages = translator->getSupportedLanguages();
    EXPECT_EQ(languages.size(), initialSize + 1);
    EXPECT_TRUE(translator->isLanguageSupported("it"));
}

// Performance Tests
TEST_F(TranslateTest, MultipleTranslationsPerformance) {
    // Test multiple translations in sequence
    for (int i = 0; i < 1000; ++i) {
        EXPECT_EQ(translator->translate("en", "tr", "hello"), "merhaba");
    }
}

TEST_F(TranslateTest, LargeTranslationSet) {
    // Add many translations
    for (int i = 0; i < 100; ++i) {
        std::string word = "word" + std::to_string(i);
        std::string translation = "kelime" + std::to_string(i);
        translator->addTranslation("en", "tr", word, translation);
    }
    
    // Test some of them
    EXPECT_EQ(translator->translate("en", "tr", "word0"), "kelime0");
    EXPECT_EQ(translator->translate("en", "tr", "word50"), "kelime50");
    EXPECT_EQ(translator->translate("en", "tr", "word99"), "kelime99");
}

// Integration Tests
TEST_F(TranslateTest, FullTranslationWorkflow) {
    // Add new language
    translator->addSupportedLanguage("fr");
    
    // Add translations
    translator->addTranslation("en", "fr", "hello", "bonjour");
    translator->addTranslation("en", "fr", "world", "monde");
    
    // Test translations
    EXPECT_EQ(translator->translate("en", "fr", "hello"), "bonjour");
    EXPECT_EQ(translator->translate("en", "fr", "world"), "monde");
    
    // Verify language is supported
    EXPECT_TRUE(translator->isLanguageSupported("fr"));
    
    // Get all translations
    auto translations = translator->getTranslations("en", "fr");
    EXPECT_EQ(translations.size(), 2);
}