/**
 * @file lexer.h
 * @brief BASIC benzeri dil için leksik analizci arabirimi.
 */
#pragma once
#include <string>
#include <vector>
#include "translator/token.h"

namespace translator {

/** @brief Kaynaktan belirteç (Token) üreten sınıf. */
class Lexer {
    /** Kaynak metin (tam içerik). */
    const std::string src_;
public:
    /** @brief Kaynağı alarak bir lexer oluşturur. */
    explicit Lexer(std::string src): src_(std::move(src)) {}
    /** @brief Girdi kaynağını belirteçlere dönüştürür. */
    std::vector<Token> tokenize() const;
};

} // namespace translator
