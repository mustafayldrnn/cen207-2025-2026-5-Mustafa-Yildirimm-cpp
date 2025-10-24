/**
 * @file parser.h
 * @brief Leksik belirteçlerden AST üreten sözdizim analizcisi
 * @author Mustafa Yıldırım
 * @date 2025
 * @version 1.0
 */
#pragma once
#include <vector>
#include <memory>
#include <cstddef>
#include "translator/token.h"
#include "translator/ast.h"

namespace translator {

/**
 * @brief BASIC benzeri dilin sözdizim çözümleyicisi
 * 
 * Bu sınıf, token dizisini alarak Abstract Syntax Tree (AST) üretir.
 * Recursive descent parsing algoritması kullanır.
 */
class Parser {
    const std::vector<Token> tokens_;  ///< Çözümlenecek token dizisi
    mutable std::size_t pos_ = 0;      ///< Mevcut pozisyon

    /**
     * @brief Mevcut token'ı döndürür (ilerlemeden)
     * @return Mevcut token'ın referansı
     */
    const Token& peek() const { return tokens_[pos_]; }
    
    /**
     * @brief Mevcut token'ı döndürür ve pozisyonu ilerletir
     * @return Mevcut token'ın referansı
     */
    const Token& advance() const { return tokens_[pos_++]; }
    
    /**
     * @brief Mevcut token'ın belirtilen türde olup olmadığını kontrol eder
     * @param t Kontrol edilecek token türü
     * @return true eğer token türü eşleşirse ve pozisyon ilerletilirse
     */
    bool match(TokenType t) const { if (peek().type == t) { ++pos_; return true; } return false; }
    
    /**
     * @brief Dosya sonuna gelinip gelinmediğini kontrol eder
     * @return true eğer dosya sonundaysa
     */
    bool at_eof() const { return peek().type == TokenType::Eof; }

    // Parsing helpers
    /**
     * @brief İfade çözümler
     * @return Çözümlenen ifade AST'i
     */
    std::unique_ptr<Expr> parse_expression() const;
    
    /**
     * @brief Terim çözümler
     * @return Çözümlenen terim AST'i
     */
    std::unique_ptr<Expr> parse_term() const;
    
    /**
     * @brief Faktör çözümler
     * @return Çözümlenen faktör AST'i
     */
    std::unique_ptr<Expr> parse_factor() const;

    /**
     * @brief Deyim çözümler
     * @param outLabel Çıktı etiketi referansı
     * @return Çözümlenen deyim AST'i
     */
    std::unique_ptr<Stmt> parse_statement(int& outLabel) const;

public:
    /**
     * @brief Belirteç dizisi ile parser oluşturur
     * @param toks Çözümlenecek token dizisi
     */
    explicit Parser(std::vector<Token> toks): tokens_(std::move(toks)) {}
    
    /**
     * @brief Girişin tamamını Program yapısına çözümler
     * @return Çözümlenen program AST'i
     */
    Program parseProgram() const;
};

} // namespace translator

