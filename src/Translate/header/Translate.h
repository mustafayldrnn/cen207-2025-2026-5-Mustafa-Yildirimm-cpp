/**
 * @file Translate.h
 * 
 * @brief BASIC to C++ Translator - Core translation engine class
 */

#ifndef TRANSLATE_H
#define TRANSLATE_H

#include <string>
#include <map>
#include <vector>
#include <stdexcept>
#include <sstream>

namespace Coruh
{
    namespace Translate
    {
        /**
            @class Translate
            @brief BASIC to C++ translation operations class
        */
        class Translate
        {
        private:
            std::map<std::string, std::string> basicToCppKeywords;
            std::vector<std::string> variables;
            std::vector<std::string> functions;
            int lineNumber;
            
            /**
             * Parses a BASIC line and converts to C++
             * @param line BASIC line to parse
             * @return C++ equivalent
             */
            std::string parseLine(const std::string& line);
            
            /**
             * Parses PRINT statement
             * @param content Content after PRINT
             * @return C++ cout statement
             */
            std::string parsePrint(const std::string& content);
            
            /**
             * Parses LET statement (variable assignment)
             * @param content Content after LET
             * @return C++ assignment statement
             */
            std::string parseLet(const std::string& content);
            
            /**
             * Parses IF statement
             * @param content Content after IF
             * @return C++ if statement
             */
            std::string parseIf(const std::string& content);
            
            /**
             * Parses FOR loop
             * @param content Content after FOR
             * @return C++ for loop
             */
            std::string parseFor(const std::string& content);
            
            /**
             * Parses NEXT statement
             * @param content Content after NEXT
             * @return C++ closing brace
             */
            std::string parseNext(const std::string& content);
            
            /**
             * Parses INPUT statement
             * @param content Content after INPUT
             * @return C++ cin statement
             */
            std::string parseInput(const std::string& content);
            
            /**
             * Parses GOTO statement
             * @param content Content after GOTO
             * @return C++ goto statement
             */
            std::string parseGoto(const std::string& content);
            
            /**
             * Parses mathematical expression
             * @param expr BASIC expression
             * @return C++ expression
             */
            std::string parseExpression(const std::string& expr);
            
            /**
             * Checks if a string is a number
             * @param str String to check
             * @return True if number
             */
            bool isNumber(const std::string& str);
            
            /**
             * Checks if a string is a variable
             * @param str String to check
             * @return True if variable
             */
            bool isVariable(const std::string& str);
            
        public:
            /**
             * Constructor - Initializes BASIC to C++ translator
             */
            Translate();
            
            /**
             * Translates BASIC code to C++
             * @param basicCode BASIC code to translate
             * @return Translated C++ code
             */
            std::string translate(const std::string& basicCode);
            
            /**
             * Adds a custom BASIC keyword mapping
             * @param basicKeyword BASIC keyword
             * @param cppEquivalent C++ equivalent
             */
            void addKeywordMapping(const std::string& basicKeyword, 
                                 const std::string& cppEquivalent);
            
            /**
             * Gets all supported BASIC keywords
             * @return Vector of supported keywords
             */
            std::vector<std::string> getSupportedKeywords();
            
            /**
             * Validates BASIC syntax
             * @param basicCode BASIC code to validate
             * @return True if syntax is valid
             */
            bool validateSyntax(const std::string& basicCode);
            
            /**
             * Gets detected variables in the code
             * @return Vector of variable names
             */
            std::vector<std::string> getDetectedVariables();
            
            /**
             * Gets detected functions in the code
             * @return Vector of function names
             */
            std::vector<std::string> getDetectedFunctions();
        };
    }
}

#endif // TRANSLATE_H