#ifndef LANGUAGE_TRANSLATOR_H
#define LANGUAGE_TRANSLATOR_H

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <iostream>
// #include <curl/curl.h>  // Commented out for now - API not implemented yet

namespace Coruh
{
    namespace LanguageTranslator
    {
        class LanguageTranslatorApp
        {
        private:
            // Multi-language dictionaries
            std::unordered_map<std::string, std::unordered_map<std::string, std::string>> wordDictionaries;
            std::unordered_map<std::string, std::unordered_map<std::string, std::string>> phraseDictionaries;
            
            // Language support
            std::vector<std::string> supportedLanguages;
            std::string currentSourceLanguage;
            std::string currentTargetLanguage;
            
            // Other features
            std::vector<std::string> commonPhrases;
            std::vector<std::string> learningTips;
            std::unordered_map<std::string, std::string> pronunciationGuide;
            
            std::string currentUser;
            bool isLoggedIn;
            
            // API settings
            std::string apiKey;
            bool useAPI;
            std::string apiProvider; // "google" or "microsoft"

        public:
            LanguageTranslatorApp();
            ~LanguageTranslatorApp() = default;

            void run();
            void showMainMenu();
            void handleUserChoice(int choice);

            // Translation functions
            std::string translateText(const std::string& text);
            std::string translateWord(const std::string& word);
            std::string translatePhrase(const std::string& phrase);
            
            // Language management
            void setSourceLanguage(const std::string& language);
            void setTargetLanguage(const std::string& language);
            std::vector<std::string> getSupportedLanguages() const;
            void showLanguageSelection();
            void addLanguage(const std::string& language);

            // User management
            bool login(const std::string& username, const std::string& password);
            bool registerUser(const std::string& username, const std::string& password);
            void logout();
            bool isUserLoggedIn() const;

            // Phrase library
            void showPhraseLibrary();
            void addPhrase(const std::string& phrase, const std::string& category);

            // Learning tips
            void showLearningTips();
            void addLearningTip(const std::string& tip);

            // Pronunciation guide
            void showPronunciationGuide();
            void addPronunciation(const std::string& word, const std::string& guide);

            // Data management
            void initializeDefaultData();
            void saveData();
            void loadData();
            
            // Dictionary management
            bool loadDictionaryFromFile(const std::string& sourceLang, const std::string& targetLang, const std::string& filename);
            void loadAllDictionaries();
            
            // API Translation
            std::string translateWithGoogleAPI(const std::string& text, const std::string& sourceLang, const std::string& targetLang);
            std::string translateWithMicrosoftAPI(const std::string& text, const std::string& sourceLang, const std::string& targetLang);
            bool isAPIAvailable();
            void setAPIKey(const std::string& key);
            void setAPIMode(bool useAPI);
        };
    }
}

#endif // LANGUAGE_TRANSLATOR_H