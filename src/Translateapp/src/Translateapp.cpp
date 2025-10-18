/**
 * @file Translateapp.cpp
 * @brief Basic Language Translator Application
 *
 * This program performs multi-language word translation
 *
 */

// Standard Libraries
#include <iostream>
#include <string>
#include <stdexcept>
#include <iomanip>
#include "../header/Translateapp.h"
#include "../../Translate/header/Translate.h"

using namespace Coruh::TranslateApp;
using namespace Coruh::Translate;

// Global translator object
static Translate translator;

void TranslateApp::run() {
    std::cout << "=== Basic Language Translator ===" << std::endl;
    std::cout << "Welcome! You can translate words between multiple languages." << std::endl;
    
    int choice;
    bool running = true;
    
    while (running) {
        showMenu();
        std::cout << "Enter your choice (1-6): ";
        std::cin >> choice;
        std::cin.ignore(); // Clear buffer
        
        switch (choice) {
            case 1: {
                std::string sourceLang = selectLanguage(true);
                std::string targetLang = selectLanguage(false);
                std::string word;
                std::cout << "Enter word to translate: ";
                std::getline(std::cin, word);
                performTranslation(sourceLang, targetLang, word);
                break;
            }
            case 2: {
                std::string sourceLang = selectLanguage(true);
                std::string targetLang = selectLanguage(false);
                listTranslations(sourceLang, targetLang);
                break;
            }
            case 3:
                addNewTranslation();
                break;
            case 4:
                showSupportedLanguages();
                break;
            case 5:
                std::cout << "Exiting... Goodbye!" << std::endl;
                running = false;
                break;
            default:
                std::cout << "Invalid choice! Please enter a number between 1-5." << std::endl;
        }
        
        if (running) {
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            std::cout << "\n" << std::string(50, '=') << std::endl;
        }
    }
}

void TranslateApp::showMenu() {
    std::cout << "\n=== MENU ===" << std::endl;
    std::cout << "1. Translate word" << std::endl;
    std::cout << "2. List translations" << std::endl;
    std::cout << "3. Add new translation" << std::endl;
    std::cout << "4. Show supported languages" << std::endl;
    std::cout << "5. Exit" << std::endl;
}

void TranslateApp::performTranslation(const std::string& sourceLanguage, 
                                    const std::string& targetLanguage, 
                                    const std::string& word) {
    try {
        std::string result = translator.translate(sourceLanguage, targetLanguage, word);
        std::cout << "Translation: " << word << " -> " << result << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << std::endl;
        std::cout << "This word is not in the dictionary. Would you like to add a new translation? (y/n): ";
        char response;
        std::cin >> response;
        std::cin.ignore();
        
        if (response == 'y' || response == 'Y') {
            addNewTranslation();
        }
    }
}

void TranslateApp::listTranslations(const std::string& sourceLanguage, 
                                   const std::string& targetLanguage) {
    std::cout << "\n=== TRANSLATIONS (" << sourceLanguage << " -> " << targetLanguage << ") ===" << std::endl;
    auto translations = translator.getTranslations(sourceLanguage, targetLanguage);
    
    if (translations.empty()) {
        std::cout << "No translations found for this language pair." << std::endl;
        return;
    }
    
    std::cout << std::left << std::setw(20) << sourceLanguage << std::setw(20) << targetLanguage << std::endl;
    std::cout << std::string(40, '-') << std::endl;
    
    for (const auto& pair : translations) {
        std::cout << std::left << std::setw(20) << pair.first << std::setw(20) << pair.second << std::endl;
    }
}

void TranslateApp::addNewTranslation() {
    std::string sourceLang, targetLang, sourceWord, targetWord;
    
    std::cout << "\n=== ADD NEW TRANSLATION ===" << std::endl;
    
    sourceLang = selectLanguage(true);
    targetLang = selectLanguage(false);
    
    std::cout << "Enter word in " << sourceLang << ": ";
    std::getline(std::cin, sourceWord);
    
    std::cout << "Enter word in " << targetLang << ": ";
    std::getline(std::cin, targetWord);
    
    if (!sourceWord.empty() && !targetWord.empty()) {
        translator.addTranslation(sourceLang, targetLang, sourceWord, targetWord);
        std::cout << "Translation added successfully: " << sourceWord << " <-> " << targetWord << std::endl;
    } else {
        std::cout << "Invalid input! Both words must be non-empty." << std::endl;
    }
}

void TranslateApp::showSupportedLanguages() {
    std::cout << "\n=== SUPPORTED LANGUAGES ===" << std::endl;
    auto languages = translator.getSupportedLanguages();
    
    std::cout << "Language codes: ";
    for (size_t i = 0; i < languages.size(); ++i) {
        std::cout << languages[i];
        if (i < languages.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
    
    // Show language names
    std::cout << "\nLanguage names:" << std::endl;
    for (const auto& lang : languages) {
        std::string langName;
        if (lang == "en") langName = "English";
        else if (lang == "tr") langName = "Turkish";
        else if (lang == "es") langName = "Spanish";
        else if (lang == "fr") langName = "French";
        else if (lang == "de") langName = "German";
        else langName = "Unknown";
        
        std::cout << "  " << lang << " - " << langName << std::endl;
    }
}

std::string TranslateApp::selectLanguage(bool isSource) {
    std::string prompt = isSource ? "Select source language" : "Select target language";
    std::cout << "\n=== " << prompt << " ===" << std::endl;
    
    auto languages = translator.getSupportedLanguages();
    
    for (size_t i = 0; i < languages.size(); ++i) {
        std::string langName;
        if (languages[i] == "en") langName = "English";
        else if (languages[i] == "tr") langName = "Turkish";
        else if (languages[i] == "es") langName = "Spanish";
        else if (languages[i] == "fr") langName = "French";
        else if (languages[i] == "de") langName = "German";
        else langName = "Unknown";
        
        std::cout << (i + 1) << ". " << languages[i] << " - " << langName << std::endl;
    }
    
    int choice;
    std::cout << "Enter your choice (1-" << languages.size() << "): ";
    std::cin >> choice;
    std::cin.ignore();
    
    if (choice >= 1 && choice <= static_cast<int>(languages.size())) {
        return languages[choice - 1];
    } else {
        std::cout << "Invalid choice! Using default: en" << std::endl;
        return "en";
    }
}

int main() {
    TranslateApp::run();
    return 0;
}
