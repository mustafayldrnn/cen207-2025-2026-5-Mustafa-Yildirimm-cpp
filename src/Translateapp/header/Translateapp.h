/**
 * @file Translateapp.h
 * @brief Basic Language Translator Application header file
 *
 */

#ifndef TRANSLATE_APP_H
#define TRANSLATE_APP_H

#include <string>

namespace Coruh
{
    namespace TranslateApp
    {
        /**
            @class TranslateApp
            @brief Basic Language Translator application main class
        */
        class TranslateApp
        {
        public:
            /**
             * Runs the application
             */
            static void run();
            
            /**
             * Shows the user menu
             */
            static void showMenu();
            
            /**
             * Performs translation operation
             * @param sourceLanguage Source language code
             * @param targetLanguage Target language code
             * @param word Word to translate
             */
            static void performTranslation(const std::string& sourceLanguage, 
                                        const std::string& targetLanguage, 
                                        const std::string& word);
            
            /**
             * Lists all translations for a language pair
             * @param sourceLanguage Source language code
             * @param targetLanguage Target language code
             */
            static void listTranslations(const std::string& sourceLanguage, 
                                       const std::string& targetLanguage);
            
            /**
             * Adds a new translation
             */
            static void addNewTranslation();
            
            /**
             * Shows supported languages
             */
            static void showSupportedLanguages();
            
            /**
             * Shows language selection menu
             * @param isSource true for source language, false for target
             * @return Selected language code
             */
            static std::string selectLanguage(bool isSource);
        };
    }
}

#endif // TRANSLATE_APP_H
