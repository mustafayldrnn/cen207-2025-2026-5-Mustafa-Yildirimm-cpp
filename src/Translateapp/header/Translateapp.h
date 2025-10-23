/**
 * @file Translateapp.h
 * @brief BASIC to C++ Translator Application header file
 *
 */

#ifndef TRANSLATE_APP_H
#define TRANSLATE_APP_H

#include <string>
#include <vector>

namespace Coruh
{
    namespace TranslateApp
    {
        /**
            @class TranslateApp
            @brief BASIC to C++ Translator application main class
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
             * Translates BASIC code to C++
             * @param basicCode BASIC code to translate
             * @return Translated C++ code
             */
            static std::string translateBasicToCpp(const std::string& basicCode);
            
            /**
             * Loads BASIC code from file
             * @param filename File path
             * @return BASIC code content
             */
            static std::string loadBasicFile(const std::string& filename);
            
            /**
             * Saves C++ code to file
             * @param filename File path
             * @param cppCode C++ code to save
             */
            static void saveCppFile(const std::string& filename, const std::string& cppCode);
            
            /**
             * Shows example BASIC programs
             */
            static void showExamples();
            
            /**
             * Interactive BASIC code editor
             */
            static void interactiveEditor();
            
            /**
             * Validates BASIC syntax
             * @param basicCode BASIC code to validate
             * @return True if syntax is valid
             */
            static bool validateBasicSyntax(const std::string& basicCode);
            
            /**
             * Shows supported BASIC commands
             */
            static void showSupportedCommands();
        };
    }
}

#endif // TRANSLATE_APP_H
