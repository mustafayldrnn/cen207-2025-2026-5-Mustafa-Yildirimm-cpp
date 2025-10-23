#include <iostream>
#include "../../src/LanguageTranslator/header/LanguageTranslator.h"

int main() {
    try {
        Coruh::LanguageTranslator::LanguageTranslatorApp app;
        app.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}