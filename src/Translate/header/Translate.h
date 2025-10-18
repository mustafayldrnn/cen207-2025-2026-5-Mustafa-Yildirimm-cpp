/**
 * @file Translate.h
 * 
 * @brief Basic Language Translator - Multi-language word translation class
 */

#ifndef TRANSLATE_H
#define TRANSLATE_H

#include <string>
#include <map>
#include <vector>
#include <stdexcept>

namespace Coruh
{
    namespace Translate
    {
        /**
            @class Translate
            @brief Basic language translation operations class
        */
        class Translate
        {
        private:
            std::map<std::string, std::map<std::string, std::string>> translations;
            std::vector<std::string> supportedLanguages;
            
        public:
            /**
             * Constructor - Initializes translation dictionary
             */
            Translate();
            
            /**
             * Translates a word from source language to target language
             * @param sourceLanguage Source language code (e.g., "en", "tr", "es")
             * @param targetLanguage Target language code (e.g., "en", "tr", "es")
             * @param word Word to translate
             * @return Translated word
             * @throws std::invalid_argument If word not found
             */
            std::string translate(const std::string& sourceLanguage, 
                                const std::string& targetLanguage, 
                                const std::string& word);
            
            /**
             * Adds a new translation pair
             * @param sourceLanguage Source language code
             * @param targetLanguage Target language code
             * @param sourceWord Word in source language
             * @param targetWord Word in target language
             */
            void addTranslation(const std::string& sourceLanguage,
                              const std::string& targetLanguage,
                              const std::string& sourceWord,
                              const std::string& targetWord);
            
            /**
             * Gets all translations for a specific language pair
             * @param sourceLanguage Source language code
             * @param targetLanguage Target language code
             * @return Vector of translation pairs
             */
            std::vector<std::pair<std::string, std::string>> getTranslations(
                const std::string& sourceLanguage, 
                const std::string& targetLanguage);
            
            /**
             * Gets all supported languages
             * @return Vector of supported language codes
             */
            std::vector<std::string> getSupportedLanguages();
            
            /**
             * Adds a new supported language
             * @param languageCode Language code to add
             */
            void addSupportedLanguage(const std::string& languageCode);
            
            /**
             * Checks if a language is supported
             * @param languageCode Language code to check
             * @return True if language is supported
             */
            bool isLanguageSupported(const std::string& languageCode);
            
            /**
             * Gets all words for a specific language
             * @param languageCode Language code
             * @return Vector of words in that language
             */
            std::vector<std::string> getWordsByLanguage(const std::string& languageCode);
        };
    }
}

#endif // TRANSLATE_H