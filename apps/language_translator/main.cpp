/**
 * @file main.cpp
 * @brief 37-Basic Language Translator Application Entry Point
 * 
 * This is the main entry point for the Language Translator application.
 * It demonstrates the use of various data structures:
 * - Hash Tables for fast translation lookup
 * - Double Linked Lists for phrase library and history
 * - Stack for session management
 * - Heap for language preferences
 * - Sparse Matrix for language relationships
 */

#include <iostream>
#include <memory>
#include "src/LanguageTranslator/header/LanguageTranslator.h"

using namespace Coruh::LanguageTranslator;

int main()
{
    try {
        // Create and run the Language Translator application
        LanguageTranslatorApp app;
        app.run();
        
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown error occurred!" << std::endl;
        return 1;
    }
}
