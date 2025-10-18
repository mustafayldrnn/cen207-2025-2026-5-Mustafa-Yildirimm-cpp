#include "../header/Translate.h"
#include <algorithm>
#include <iostream>

using namespace Coruh::Translate;

Translate::Translate() {
    // Initialize supported languages
    supportedLanguages = {"en", "tr", "es", "fr", "de"};
    
    // Add basic English-Turkish translations
    addTranslation("en", "tr", "hello", "merhaba");
    addTranslation("en", "tr", "world", "dünya");
    addTranslation("en", "tr", "house", "ev");
    addTranslation("en", "tr", "car", "araba");
    addTranslation("en", "tr", "book", "kitap");
    addTranslation("en", "tr", "water", "su");
    addTranslation("en", "tr", "food", "yemek");
    addTranslation("en", "tr", "school", "okul");
    addTranslation("en", "tr", "mother", "anne");
    addTranslation("en", "tr", "father", "baba");
    addTranslation("en", "tr", "friend", "arkadaş");
    addTranslation("en", "tr", "beautiful", "güzel");
    addTranslation("en", "tr", "big", "büyük");
    addTranslation("en", "tr", "small", "küçük");
    addTranslation("en", "tr", "good", "iyi");
    addTranslation("en", "tr", "bad", "kötü");
    addTranslation("en", "tr", "new", "yeni");
    addTranslation("en", "tr", "old", "eski");
    addTranslation("en", "tr", "fast", "hızlı");
    addTranslation("en", "tr", "slow", "yavaş");
    
    // Add basic English-Spanish translations
    addTranslation("en", "es", "hello", "hola");
    addTranslation("en", "es", "world", "mundo");
    addTranslation("en", "es", "house", "casa");
    addTranslation("en", "es", "car", "coche");
    addTranslation("en", "es", "book", "libro");
    addTranslation("en", "es", "water", "agua");
    addTranslation("en", "es", "food", "comida");
    addTranslation("en", "es", "school", "escuela");
    addTranslation("en", "es", "mother", "madre");
    addTranslation("en", "es", "father", "padre");
    addTranslation("en", "es", "friend", "amigo");
    addTranslation("en", "es", "beautiful", "hermoso");
    addTranslation("en", "es", "big", "grande");
    addTranslation("en", "es", "small", "pequeño");
    addTranslation("en", "es", "good", "bueno");
    addTranslation("en", "es", "bad", "malo");
    addTranslation("en", "es", "new", "nuevo");
    addTranslation("en", "es", "old", "viejo");
    addTranslation("en", "es", "fast", "rápido");
    addTranslation("en", "es", "slow", "lento");
}

std::string Translate::translate(const std::string& sourceLanguage, 
                                const std::string& targetLanguage, 
                                const std::string& word) {
    // Convert to lowercase
    std::string lowerWord = word;
    std::transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(), ::tolower);
    
    // Check if languages are supported
    if (!isLanguageSupported(sourceLanguage)) {
        throw std::invalid_argument("Source language not supported: " + sourceLanguage);
    }
    if (!isLanguageSupported(targetLanguage)) {
        throw std::invalid_argument("Target language not supported: " + targetLanguage);
    }
    
    // Create language pair key
    std::string languagePair = sourceLanguage + "_" + targetLanguage;
    
    // Check if translation exists
    auto it = translations.find(languagePair);
    if (it != translations.end()) {
        auto wordIt = it->second.find(lowerWord);
        if (wordIt != it->second.end()) {
            return wordIt->second;
        }
    }
    
    throw std::invalid_argument("Translation not found for: " + word);
}

void Translate::addTranslation(const std::string& sourceLanguage,
                              const std::string& targetLanguage,
                              const std::string& sourceWord,
                              const std::string& targetWord) {
    // Convert to lowercase
    std::string lowerSourceWord = sourceWord;
    std::string lowerTargetWord = targetWord;
    
    std::transform(lowerSourceWord.begin(), lowerSourceWord.end(), lowerSourceWord.begin(), ::tolower);
    std::transform(lowerTargetWord.begin(), lowerTargetWord.end(), lowerTargetWord.begin(), ::tolower);
    
    // Create language pair key
    std::string languagePair = sourceLanguage + "_" + targetLanguage;
    
    // Add translation
    translations[languagePair][lowerSourceWord] = lowerTargetWord;
}

std::vector<std::pair<std::string, std::string>> Translate::getTranslations(
    const std::string& sourceLanguage, 
    const std::string& targetLanguage) {
    std::vector<std::pair<std::string, std::string>> result;
    
    std::string languagePair = sourceLanguage + "_" + targetLanguage;
    auto it = translations.find(languagePair);
    
    if (it != translations.end()) {
        for (const auto& pair : it->second) {
            result.push_back({pair.first, pair.second});
        }
    }
    
    return result;
}

std::vector<std::string> Translate::getSupportedLanguages() {
    return supportedLanguages;
}

void Translate::addSupportedLanguage(const std::string& languageCode) {
    // Check if language already exists
    auto it = std::find(supportedLanguages.begin(), supportedLanguages.end(), languageCode);
    if (it == supportedLanguages.end()) {
        supportedLanguages.push_back(languageCode);
    }
}

bool Translate::isLanguageSupported(const std::string& languageCode) {
    return std::find(supportedLanguages.begin(), supportedLanguages.end(), languageCode) != supportedLanguages.end();
}

std::vector<std::string> Translate::getWordsByLanguage(const std::string& languageCode) {
    std::vector<std::string> words;
    
    // Find all language pairs where this language is the source
    for (const auto& pair : translations) {
        std::string languagePair = pair.first;
        size_t underscorePos = languagePair.find('_');
        if (underscorePos != std::string::npos) {
            std::string sourceLang = languagePair.substr(0, underscorePos);
            if (sourceLang == languageCode) {
                for (const auto& wordPair : pair.second) {
                    words.push_back(wordPair.first);
                }
            }
        }
    }
    
    return words;
}