/**
 * @file Translateapp.cpp
 * @brief BASIC to C++ Translator Application
 *
 * This program translates BASIC code to C++ code
 *
 */

// Standard Libraries
#include <iostream>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "../header/Translateapp.h"
#include "../../Translate/header/Translate.h"

using namespace Coruh::TranslateApp;
using namespace Coruh::Translate;

// Global translator object
static Translate translator;

void TranslateApp::run() {
    std::cout << "=== BASIC to C++ Translator ===" << std::endl;
    std::cout << "Welcome! You can translate BASIC code to C++ code." << std::endl;
    
    int choice;
    bool running = true;
    
    while (running) {
        showMenu();
        std::cout << "Enter your choice (1-7): ";
        std::cin >> choice;
        std::cin.ignore(); // Clear buffer
        
        switch (choice) {
            case 1: {
                std::string filename;
                std::cout << "Enter BASIC file path: ";
                std::getline(std::cin, filename);
                try {
                    std::string basicCode = loadBasicFile(filename);
                    std::string cppCode = translateBasicToCpp(basicCode);
                    std::cout << "\n=== TRANSLATED C++ CODE ===" << std::endl;
                    std::cout << cppCode << std::endl;
                    
                    std::cout << "\nSave to file? (y/n): ";
                    char save;
                    std::cin >> save;
                    if (save == 'y' || save == 'Y') {
                        std::string outputFile;
                        std::cout << "Enter output file path: ";
                        std::cin.ignore();
                        std::getline(std::cin, outputFile);
                        saveCppFile(outputFile, cppCode);
                    }
                } catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << std::endl;
                }
                break;
            }
            case 2:
                interactiveEditor();
                break;
            case 3:
                showExamples();
                break;
            case 4:
                showSupportedCommands();
                break;
            case 5: {
                std::string basicCode;
                std::cout << "Enter BASIC code (end with 'END' on new line):" << std::endl;
                std::string line;
                while (std::getline(std::cin, line) && line != "END") {
                    basicCode += line + "\n";
                }
                
                if (validateBasicSyntax(basicCode)) {
                    std::string cppCode = translateBasicToCpp(basicCode);
                    std::cout << "\n=== TRANSLATED C++ CODE ===" << std::endl;
                    std::cout << cppCode << std::endl;
                } else {
                    std::cout << "Invalid BASIC syntax!" << std::endl;
                }
                break;
            }
            case 6:
                std::cout << "Exiting... Goodbye!" << std::endl;
                running = false;
                break;
            default:
                std::cout << "Invalid choice! Please enter a number between 1-6." << std::endl;
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
    std::cout << "1. Translate BASIC file to C++" << std::endl;
    std::cout << "2. Interactive BASIC editor" << std::endl;
    std::cout << "3. Show example BASIC programs" << std::endl;
    std::cout << "4. Show supported BASIC commands" << std::endl;
    std::cout << "5. Translate BASIC code directly" << std::endl;
    std::cout << "6. Exit" << std::endl;
}

std::string TranslateApp::translateBasicToCpp(const std::string& basicCode) {
    return translator.translate(basicCode);
}

std::string TranslateApp::loadBasicFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    
    return buffer.str();
}

void TranslateApp::saveCppFile(const std::string& filename, const std::string& cppCode) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot create file: " + filename);
    }
    
    file << cppCode;
    file.close();
    
    std::cout << "C++ code saved to: " << filename << std::endl;
}

void TranslateApp::showExamples() {
    std::cout << "\n=== EXAMPLE BASIC PROGRAMS ===" << std::endl;
    
    std::cout << "\n1. Hello World Program:" << std::endl;
    std::cout << "10 PRINT \"Hello, World!\"" << std::endl;
    std::cout << "20 END" << std::endl;
    
    std::cout << "\n2. Simple Calculator:" << std::endl;
    std::cout << "10 INPUT \"Enter first number: \", A" << std::endl;
    std::cout << "20 INPUT \"Enter second number: \", B" << std::endl;
    std::cout << "30 LET C = A + B" << std::endl;
    std::cout << "40 PRINT \"Sum is: \", C" << std::endl;
    std::cout << "50 END" << std::endl;
    
    std::cout << "\n3. For Loop Example:" << std::endl;
    std::cout << "10 FOR I = 1 TO 5" << std::endl;
    std::cout << "20   PRINT \"Number: \", I" << std::endl;
    std::cout << "30 NEXT I" << std::endl;
    std::cout << "40 END" << std::endl;
    
    std::cout << "\n4. If-Then Example:" << std::endl;
    std::cout << "10 INPUT \"Enter your age: \", AGE" << std::endl;
    std::cout << "20 IF AGE >= 18 THEN PRINT \"You are an adult\"" << std::endl;
    std::cout << "30 IF AGE < 18 THEN PRINT \"You are a minor\"" << std::endl;
    std::cout << "40 END" << std::endl;
}

void TranslateApp::interactiveEditor() {
    std::cout << "\n=== INTERACTIVE BASIC EDITOR ===" << std::endl;
    std::cout << "Enter BASIC code line by line. Type 'TRANSLATE' to translate, 'QUIT' to exit." << std::endl;
    
    std::string basicCode;
    std::string line;
    
    while (true) {
        std::cout << "BASIC> ";
        std::getline(std::cin, line);
        
        if (line == "QUIT") {
            break;
        } else if (line == "TRANSLATE") {
            if (!basicCode.empty()) {
                std::cout << "\n=== TRANSLATED C++ CODE ===" << std::endl;
                std::string cppCode = translateBasicToCpp(basicCode);
                std::cout << cppCode << std::endl;
                
                std::cout << "\nSave to file? (y/n): ";
                char save;
                std::cin >> save;
                if (save == 'y' || save == 'Y') {
                    std::string outputFile;
                    std::cout << "Enter output file path: ";
                    std::cin.ignore();
                    std::getline(std::cin, outputFile);
                    saveCppFile(outputFile, cppCode);
                }
            } else {
                std::cout << "No BASIC code to translate!" << std::endl;
            }
        } else if (!line.empty()) {
            basicCode += line + "\n";
        }
    }
}

bool TranslateApp::validateBasicSyntax(const std::string& basicCode) {
    return translator.validateSyntax(basicCode);
}

void TranslateApp::showSupportedCommands() {
    std::cout << "\n=== SUPPORTED BASIC COMMANDS ===" << std::endl;
    auto keywords = translator.getSupportedKeywords();
    
    std::cout << "Supported BASIC keywords:" << std::endl;
    for (const auto& keyword : keywords) {
        std::cout << "  - " << keyword << std::endl;
    }
    
    std::cout << "\nCommand descriptions:" << std::endl;
    std::cout << "  PRINT    - Output text or variables" << std::endl;
    std::cout << "  LET      - Variable assignment" << std::endl;
    std::cout << "  INPUT    - Get user input" << std::endl;
    std::cout << "  IF/THEN  - Conditional statements" << std::endl;
    std::cout << "  FOR/NEXT - For loops" << std::endl;
    std::cout << "  GOTO     - Jump to line number" << std::endl;
    std::cout << "  REM      - Comments" << std::endl;
    std::cout << "  END      - End program" << std::endl;
}

int main() {
    TranslateApp::run();
    return 0;
}
