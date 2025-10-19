#include <iostream>
#include <fstream>
#include <string>
#include "translator/lexer.h"
#include "translator/parser.h"
#include "translator/codegen.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: translator <input.bas> [-o output.cpp]" << std::endl;
        return 1;
    }
    std::string inputPath = argv[1];
    std::string outputPath;
    for (int i = 2; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-o" && i + 1 < argc) {
            outputPath = argv[++i];
        }
    }

    std::ifstream in(inputPath);
    if (!in) {
        std::cerr << "Cannot open input: " << inputPath << std::endl;
        return 1;
    }

    std::string source((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

    translator::Lexer lexer(source);
    auto tokens = lexer.tokenize();
    translator::Parser parser(tokens);
    auto program = parser.parseProgram();
    auto code = translator::Codegen::emit_cpp(program);
    if (!outputPath.empty()) { std::ofstream out(outputPath); out << code; }
    else { std::cout << code << std::endl; }
    return 0;
}
