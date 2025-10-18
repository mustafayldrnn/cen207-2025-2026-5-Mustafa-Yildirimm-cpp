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