#pragma once
#include <string>
#include <vector>
#include "translator/token.h"

namespace translator {

class Lexer {
    const std::string src_;
public:
    explicit Lexer(std::string src): src_(std::move(src)) {}
    std::vector<Token> tokenize() const;
};

} // namespace translator

