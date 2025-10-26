/**
 * @file parser.cpp
 * @brief Parser uygulaması: Token dizisinden AST üretir.
 */
#include "translator/parser.h"
#include <stdexcept>

namespace translator {

/**
 * \brief Toplama/çıkarma operatörü mü?
 * \param t Token türü
 * \return Plus veya Minus ise true
 */
static bool is_add_op(TokenType t){ return t==TokenType::Plus || t==TokenType::Minus; }

/**
 * \brief Çarpma/bölme operatörü mü?
 * \param t Token türü
 * \return Star veya Slash ise true
 */
static bool is_mul_op(TokenType t){ return t==TokenType::Star || t==TokenType::Slash; }

/**
 * \brief Toplama/çıkarma önceliğiyle bir ifadeyi çözümler.
 * \return Çözümlenen ifade düğümü
 */
std::unique_ptr<Expr> Parser::parse_expression() const {
    auto left = parse_term();
    while (is_add_op(peek().type)) {
        char op = (peek().type==TokenType::Plus)?'+':'-'; advance();
        auto right = parse_term();
        left = std::make_unique<BinaryExpr>(op, std::move(left), std::move(right));
    }
    return left;
}

/**
 * \brief Çarpma/bölme önceliğiyle bir terimi çözümler.
 * \return Çözümlenen terim düğümü
 */
std::unique_ptr<Expr> Parser::parse_term() const {
    auto left = parse_factor();
    while (is_mul_op(peek().type)) {
        char op = (peek().type==TokenType::Star)?'*':'/'; advance();
        auto right = parse_factor();
        left = std::make_unique<BinaryExpr>(op, std::move(left), std::move(right));
    }
    return left;
}

/**
 * \brief Sayı, değişken veya parantezli ifade çözümler.
 * \return Çözümlenen faktör düğümü
 */
std::unique_ptr<Expr> Parser::parse_factor() const {
    const Token& t = peek();
    if (t.type == TokenType::Number) { advance(); return std::make_unique<NumberExpr>(std::stod(t.lexeme)); }
    if (t.type == TokenType::Identifier) { advance(); return std::make_unique<VariableExpr>(t.lexeme); }
    if (t.type == TokenType::LParen) { advance(); auto e = parse_expression(); if (!match(TokenType::RParen)) throw std::runtime_error("Expected )"); return e; }
    throw std::runtime_error("Unexpected token in factor");
}

/**
 * \brief Tek bir deyimi (ve varsa satır etiketini) çözümler.
 * \param[out] outLabel Deyimin satır etiketi; yoksa -1 olur.
 * \return Çözümlenen deyim düğümü
 */
std::unique_ptr<Stmt> Parser::parse_statement(int& outLabel) const {
    outLabel = -1;
    // Optional line label at start of a line: Number ...
    if (peek().type == TokenType::Number) {
        // Only treat as label if followed by something other than Eof/Newline
        int label = std::stoi(peek().lexeme);
        // Lookahead without consuming statement token kinds
        // We'll accept this as label and move on
        advance();
        outLabel = label;
    }

    // Skip any extra newlines between label and statement
    while (match(TokenType::Newline)) {}

    const Token& t = peek();
    if (t.type == TokenType::KW_LET) {
        advance();
        if (peek().type != TokenType::Identifier) throw std::runtime_error("Expected identifier after LET");
        std::string name = advance().lexeme;
        if (!match(TokenType::Assign)) throw std::runtime_error("Expected = in LET");
        auto e = parse_expression();
        // consume optional trailing newline
        if (peek().type == TokenType::Newline) advance();
        return std::make_unique<LetStmt>(std::move(name), std::move(e));
    }
    if (t.type == TokenType::KW_PRINT) {
        advance(); std::vector<std::unique_ptr<Expr>> items;
        items.push_back(parse_expression());
        while (match(TokenType::Comma)) items.push_back(parse_expression());
        if (peek().type == TokenType::Newline) advance();
        return std::make_unique<PrintStmt>(std::move(items));
    }
    if (t.type == TokenType::KW_INPUT) {
        advance(); if (peek().type != TokenType::Identifier) throw std::runtime_error("Expected identifier after INPUT");
        std::string name = advance().lexeme; if (peek().type == TokenType::Newline) advance();
        return std::make_unique<InputStmt>(std::move(name));
    }
    if (t.type == TokenType::KW_GOTO) {
        advance(); if (peek().type != TokenType::Number) throw std::runtime_error("Expected line number after GOTO");
        int target = std::stoi(advance().lexeme); if (peek().type == TokenType::Newline) advance();
        return std::make_unique<GotoStmt>(target);
    }
    if (t.type == TokenType::KW_IF) {
        advance(); auto cond = parse_expression();
        if (peek().type != TokenType::KW_THEN) throw std::runtime_error("Expected THEN");
        advance();
        if (peek().type == TokenType::KW_GOTO) advance();
        if (peek().type != TokenType::Number) throw std::runtime_error("Expected line number after THEN");
        int target = std::stoi(advance().lexeme);
        if (peek().type == TokenType::Newline) advance();
        return std::make_unique<IfGotoStmt>(std::move(cond), target);
    }
    if (t.type == TokenType::KW_GOSUB) {
        advance(); if (peek().type != TokenType::Number) throw std::runtime_error("Expected line number after GOSUB");
        int target = std::stoi(advance().lexeme); if (peek().type == TokenType::Newline) advance();
        return std::make_unique<GosubStmt>(target);
    }
    if (t.type == TokenType::KW_RETURN) {
        advance(); if (peek().type == TokenType::Newline) advance();
        return std::make_unique<ReturnStmt>();
    }

    throw std::runtime_error("Unknown statement");
}

/**
 * \brief Girdi akışının tamamını Program yapısına çözümler.
 * \return Etiketlenmiş deyimlerden oluşan Program
 */
Program Parser::parseProgram() const {
    Program prog; prog.labels.clear(); prog.stmts.clear();
    // Consume possible leading newlines
    while (peek().type == TokenType::Newline) advance();
    while (!at_eof()){
        int lbl = -1;
        auto st = parse_statement(lbl);
        if (lbl == -1) {
            // Synthesize a label by stepping +10 from last or start at 10
            int prev = prog.labels.empty() ? 0 : prog.labels.back();
            lbl = prev + 10;
        }
        prog.labels.push_back(lbl);
        prog.stmts.push_back(std::move(st));
        // Skip possible blank lines between statements
        while (peek().type == TokenType::Newline) advance();
        if (peek().type == TokenType::Eof) break;
    }
    return prog;
}

} // namespace translator
