/**
 * @file LanguageTranslator.h
 * @brief 37-Basic Language Translator Application
 * 
 * Features:
 * - Text Input and Translation
 * - Language Learning Tips
 * - Common Phrase Library
 * - Pronunciation Guide
 * - User Authentication
 */

#ifndef LANGUAGE_TRANSLATOR_H
#define LANGUAGE_TRANSLATOR_H

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <fstream>
#include <chrono>

// Include our data structure algorithms
#include "../../DoubleLinkedList/header/DoubleLinkedList.h"
#include "../../HashTable/header/HashTable.h"
#include "../../StackQueue/header/StackQueue.h"
#include "../../Heap/header/Heap.h"
#include "../../SparseMatrix/header/SparseMatrix.h"

namespace Coruh
{
    namespace LanguageTranslator
    {
        /**
         * @class User
         * @brief User authentication and profile management
         */
        class User
        {
        private:
            std::string username;
            std::string password;
            std::string preferredLanguage;
            std::vector<std::string> translationHistory;
            std::vector<std::string> favoritePhrases;
            std::chrono::system_clock::time_point lastLogin;

        public:
            User(const std::string& username, const std::string& password);
            ~User() = default;

            // Getters
            std::string getUsername() const;
            std::string getPreferredLanguage() const;
            std::vector<std::string> getTranslationHistory() const;
            std::vector<std::string> getFavoritePhrases() const;

            // Setters
            void setPreferredLanguage(const std::string& language);
            void addTranslationHistory(const std::string& translation);
            void addFavoritePhrase(const std::string& phrase);

            // Authentication
            bool authenticate(const std::string& password) const;
            void updateLastLogin();

            // File operations
            void saveToFile(const std::string& filename) const;
            void loadFromFile(const std::string& filename);
        };

        /**
         * @class TranslationEngine
         * @brief Core translation functionality using Hash Tables
         */
        class TranslationEngine
        {
        private:
            // Hash tables for fast translation lookup
            HashTable<std::string, std::string> wordDictionary;
            HashTable<std::string, std::string> phraseDictionary;
            HashTable<std::string, std::string> grammarRules;
            
            // Language support
            std::vector<std::string> supportedLanguages;
            std::string currentSourceLanguage;
            std::string currentTargetLanguage;

        public:
            TranslationEngine();
            ~TranslationEngine() = default;

            // Translation methods
            std::string translateText(const std::string& text);
            std::string translateWord(const std::string& word);
            std::string translatePhrase(const std::string& phrase);

            // Language management
            void setSourceLanguage(const std::string& language);
            void setTargetLanguage(const std::string& language);
            std::vector<std::string> getSupportedLanguages() const;

            // Dictionary management
            void addWord(const std::string& source, const std::string& target);
            void addPhrase(const std::string& source, const std::string& target);
            void loadDictionary(const std::string& filename);
            void saveDictionary(const std::string& filename) const;
        };

        /**
         * @class PhraseLibrary
         * @brief Common phrase library using Double Linked List
         */
        class PhraseLibrary
        {
        private:
            DoubleLinkedList<std::string> commonPhrases;
            DoubleLinkedList<std::string> categories;
            std::unordered_map<std::string, std::vector<std::string>> phrasesByCategory;

        public:
            PhraseLibrary();
            ~PhraseLibrary() = default;

            // Phrase management
            void addPhrase(const std::string& phrase, const std::string& category);
            void removePhrase(const std::string& phrase);
            std::vector<std::string> getPhrasesByCategory(const std::string& category) const;
            std::vector<std::string> getAllCategories() const;
            std::vector<std::string> searchPhrases(const std::string& keyword) const;

            // File operations
            void loadFromFile(const std::string& filename);
            void saveToFile(const std::string& filename) const;
        };

        /**
         * @class LearningTips
         * @brief Language learning tips and resources
         */
        class LearningTips
        {
        private:
            std::unordered_map<std::string, std::vector<std::string>> tipsByLanguage;
            std::unordered_map<std::string, std::vector<std::string>> grammarLessons;
            std::unordered_map<std::string, std::vector<std::string>> vocabularyExercises;

        public:
            LearningTips();
            ~LearningTips() = default;

            // Learning resources
            std::vector<std::string> getTips(const std::string& language) const;
            std::vector<std::string> getGrammarLessons(const std::string& language) const;
            std::vector<std::string> getVocabularyExercises(const std::string& language) const;
            
            // Add new content
            void addTip(const std::string& language, const std::string& tip);
            void addGrammarLesson(const std::string& language, const std::string& lesson);
            void addVocabularyExercise(const std::string& language, const std::string& exercise);

            // File operations
            void loadFromFile(const std::string& filename);
            void saveToFile(const std::string& filename) const;
        };

        /**
         * @class PronunciationGuide
         * @brief Pronunciation guide with audio samples
         */
        class PronunciationGuide
        {
        private:
            std::unordered_map<std::string, std::string> pronunciationRules;
            std::unordered_map<std::string, std::string> audioFiles;
            std::unordered_map<std::string, std::string> phoneticTranscriptions;

        public:
            PronunciationGuide();
            ~PronunciationGuide() = default;

            // Pronunciation methods
            std::string getPronunciation(const std::string& word) const;
            std::string getPhoneticTranscription(const std::string& word) const;
            std::string getAudioFile(const std::string& word) const;
            
            // Add pronunciation data
            void addPronunciation(const std::string& word, const std::string& pronunciation);
            void addPhoneticTranscription(const std::string& word, const std::string& phonetic);
            void addAudioFile(const std::string& word, const std::string& audioFile);

            // File operations
            void loadFromFile(const std::string& filename);
            void saveToFile(const std::string& filename) const;
        };

        /**
         * @class LanguageTranslatorApp
         * @brief Main application class
         */
        class LanguageTranslatorApp
        {
        private:
            // Core components
            std::unique_ptr<TranslationEngine> translationEngine;
            std::unique_ptr<PhraseLibrary> phraseLibrary;
            std::unique_ptr<LearningTips> learningTips;
            std::unique_ptr<PronunciationGuide> pronunciationGuide;
            
            // User management using Hash Table
            HashTable<std::string, User> users;
            std::string currentUser;
            
            // Session management using Stack
            Stack<std::string> sessionStack;
            
            // Language preferences using Heap
            Heap<std::string> languagePreferences;
            
            // Translation history using Double Linked List
            DoubleLinkedList<std::string> translationHistory;
            
            // Language relationships using Sparse Matrix
            SparseMatrix<double> languageSimilarityMatrix;

        public:
            LanguageTranslatorApp();
            ~LanguageTranslatorApp() = default;

            // Main application methods
            void run();
            void showMainMenu();
            void handleUserChoice(int choice);

            // User management
            bool login(const std::string& username, const std::string& password);
            bool registerUser(const std::string& username, const std::string& password);
            void logout();
            bool isLoggedIn() const;

            // Translation features
            void translateText();
            void translatePhrase();
            void showTranslationHistory();
            void clearTranslationHistory();

            // Learning features
            void showLearningTips();
            void showGrammarLessons();
            void showVocabularyExercises();

            // Phrase library features
            void browsePhraseLibrary();
            void searchPhrases();
            void addToFavorites();

            // Pronunciation features
            void showPronunciationGuide();
            void practicePronunciation();

            // File operations
            void saveAllData();
            void loadAllData();

            // Utility methods
            void initializeDefaultData();
            void showSupportedLanguages();
            void changeLanguageSettings();
        };
    }
}

#endif // LANGUAGE_TRANSLATOR_H
