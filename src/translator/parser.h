#pragma once
#include <vector>
#include <memory>
#include <cstddef>
#include "translator/token.h"
#include "translator/ast.h"

namespace translator {

class Parser {
    const std::vector<Token> tokens_;
    mutable std::size_t pos_ = 0;

    const Token& peek() const { return tokens_[pos_]; }
    const Token& advance() const { return tokens_[pos_++]; }
    bool match(TokenType t) const { if (peek().type == t) { ++pos_; return true; } return false; }
    bool at_eof() const { return peek().type == TokenType::Eof; }

    // Parsing helpers
    std::unique_ptr<Expr> parse_expression() const;
    std::unique_ptr<Expr> parse_term() const;
    std::unique_ptr<Expr> parse_factor() const;

    std::unique_ptr<Stmt> parse_statement(int& outLabel) const;

public:
    explicit Parser(std::vector<Token> toks): tokens_(std::move(toks)) {}
    Program parseProgram() const;
};

} // namespace translator
