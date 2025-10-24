/**
 * @file LanguageTranslator.h
 * @brief Konsol tabanlı dil çevirici uygulamasının ana arabirimi.
 */
#ifndef LANGUAGE_TRANSLATOR_H
#define LANGUAGE_TRANSLATOR_H

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <iostream>
#include "Persistence.h"
// #include <curl/curl.h>  // Commented out for now - API not implemented yet

namespace Coruh
{
    namespace LanguageTranslator
    {
        /**
         * @class LanguageTranslatorApp
         * @brief Uygulama akışını yöneten ana sınıf.
         */
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
            std::vector<UserProfile> users; // persisted users
            std::vector<TranslationRecord> history; // translation history
            
            // API settings
            std::string apiKey;
            bool useAPI;
            std::string apiProvider; // "google" or "microsoft"

        public:
            /** @brief Uygulamayı varsayılan verilerle başlatır. */
            LanguageTranslatorApp();
            ~LanguageTranslatorApp() = default;

            /** @brief Uygulama döngüsünü çalıştırır. */
            void run();
            /** @brief Ana menüyü gösterir. */
            void showMainMenu();
            /** @brief Menü seçimini işler. */
            void handleUserChoice(int choice);

            // Translation functions
            /** @brief Metni aktif dil çiftine göre çevirir. */
            std::string translateText(const std::string& text);
            /** @brief Tek kelime çevirir. */
            std::string translateWord(const std::string& word);
            /** @brief Kalıp/ifade çevirir. */
            std::string translatePhrase(const std::string& phrase);
            
            // Language management
            /** @brief Kaynak dili ayarlar. */
            void setSourceLanguage(const std::string& language);
            /** @brief Hedef dili ayarlar. */
            void setTargetLanguage(const std::string& language);
            /** @brief Desteklenen dilleri döndürür. */
            std::vector<std::string> getSupportedLanguages() const;
            /** @brief Dil seçim ekranını gösterir. */
            void showLanguageSelection();
            /** @brief Yeni dil ekler. */
            void addLanguage(const std::string& language);

            // User management
            /** @brief Kullanıcı girişi. */
            bool login(const std::string& username, const std::string& password);
            /** @brief Kullanıcı kaydı. */
            bool registerUser(const std::string& username, const std::string& password);
            /** @brief Oturumu kapatır. */
            void logout();
            /** @brief Kullanıcı oturum durumunu döndürür. */
            bool isUserLoggedIn() const;
            const std::string& currentUsername() const { return currentUser; }

            // Phrase library
            /** @brief Kalıp sözlüğü ekranı. */
            void showPhraseLibrary();
            /** @brief Genel ifade ekler. */
            void addPhrase(const std::string& phrase, const std::string& category);

            // Learning tips
            /** @brief Öğrenme ipuçlarını listeler. */
            void showLearningTips();
            /** @brief Öğrenme ipucu ekler. */
            void addLearningTip(const std::string& tip);

            // Pronunciation guide
            /** @brief Telaffuz rehberini listeler. */
            void showPronunciationGuide();
            /** @brief Telaffuz girdisi ekler/günceller. */
            void addPronunciation(const std::string& word, const std::string& guide);

            // History
            /** @brief Çeviri geçmişini listeler. */
            void showHistory() const;
            /** @brief Çeviri geçmişini temizler. */
            void clearHistory();

            // Data management
            /** @brief Varsayılan verilerle başlatır. */
            void initializeDefaultData();
            /** @brief Verileri kalıcı depoya yazar. */
            void saveData();
            /** @brief Verileri kalıcı depodan okur. */
            void loadData();
            
            // Dictionary management
            /** @brief Dosyadan sözlük yükler. */
            bool loadDictionaryFromFile(const std::string& sourceLang, const std::string& targetLang, const std::string& filename);
            /** @brief Tüm sözlükleri yükler. */
            void loadAllDictionaries();
            
            // API Translation
            /** @brief Google API ile çeviri (stub). */
            std::string translateWithGoogleAPI(const std::string& text, const std::string& sourceLang, const std::string& targetLang);
            /** @brief Microsoft API ile çeviri (stub). */
            std::string translateWithMicrosoftAPI(const std::string& text, const std::string& sourceLang, const std::string& targetLang);
            /** @brief API kullanılabilirliği. */
            bool isAPIAvailable();
            /** @brief API anahtarını ayarlar. */
            void setAPIKey(const std::string& key);
            /** @brief API modunu aç/kapatır. */
            void setAPIMode(bool useAPI);
        };
    }
}

#endif // LANGUAGE_TRANSLATOR_H
