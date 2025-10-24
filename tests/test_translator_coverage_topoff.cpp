/**
 * @file test_translator_coverage_topoff.cpp
 * @brief Targeted tests to cover remaining uncovered lines in lexer/parser/codegen.
 */

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "../src/translator/lexer.h"
#include "../src/translator/parser.h"
#include "../src/translator/codegen.h"

using namespace translator;

// Covers: string literal scanning (multi-line), and single-char tokens -,*,/,),(
TEST(TranslatorCoverageTopOff, Lexer_StringAndPunctuators)
{
    // String without closing quote on same line to exercise newline handling inside string
    const std::string src = "PRINT \"hello\nworld\"\nA = 1-2*3/4,(5)\n";
    Lexer lx(src);
    auto toks = lx.tokenize();

    // Ensure we saw a String token and various punctuators
    bool sawString=false, sawMinus=false, sawStar=false, sawSlash=false, sawLParen=false, sawRParen=false, sawComma=false;
    for (const auto& t : toks) {
        sawString |= (t.type==TokenType::String);
        sawMinus  |= (t.type==TokenType::Minus);
        sawStar   |= (t.type==TokenType::Star);
        sawSlash  |= (t.type==TokenType::Slash);
        sawLParen |= (t.type==TokenType::LParen);
        sawRParen |= (t.type==TokenType::RParen);
        sawComma  |= (t.type==TokenType::Comma);
    }
    EXPECT_TRUE(sawString);
    EXPECT_TRUE(sawMinus);
    EXPECT_TRUE(sawStar);
    EXPECT_TRUE(sawSlash);
    EXPECT_TRUE(sawLParen);
    EXPECT_TRUE(sawRParen);
    EXPECT_TRUE(sawComma);
}

// Additional lexer micro-cases: bare identifier and same-line string termination
TEST(TranslatorCoverageTopOff, Lexer_Identifier_And_SimpleString)
{
    const std::string src = "foo\nPRINT \"x\"\n";
    auto toks = Lexer(src).tokenize();
    bool sawId=false, sawString=false;
    for (const auto& t : toks) {
        sawId |= (t.type==TokenType::Identifier && t.lexeme=="foo");
        sawString |= (t.type==TokenType::String && t.lexeme=="x");
    }
    EXPECT_TRUE(sawId);
    EXPECT_TRUE(sawString);
}

// Edge case: empty string literal to ensure closing-quote branch counted
TEST(TranslatorCoverageTopOff, Lexer_EmptyString)
{
    const std::string src = "PRINT \"\"\n";
    auto toks = Lexer(src).tokenize();
    int stringCount = 0;
    for (const auto& t : toks) if (t.type==TokenType::String) ++stringCount;
    EXPECT_EQ(stringCount, 1);
}

// Covers: parse_term() loop for * and /; and codegen Let with BinaryExpr and next-label branch
TEST(TranslatorCoverageTopOff, Parser_MulDiv_And_CodegenLet)
{
    const std::string src =
        "10 LET A = 2*3/4\n"
        "20 PRINT 1\n"; // ensure next_label exists after LET
    auto toks = Lexer(src).tokenize();
    Program prog = Parser(std::move(toks)).parseProgram();

    // Basic sanity
    ASSERT_EQ(prog.stmts.size(), 2u);

    // Emitting C++ should include the binary expression with both ops and the LET assignment
    std::string out = Codegen().emit_cpp(prog);
    EXPECT_NE(out.find("var[\"A\"] ="), std::string::npos);
    EXPECT_NE(out.find("*"), std::string::npos);
    EXPECT_NE(out.find("/"), std::string::npos);
}

// Covers: parser factor unexpected token throw (line with "Unexpected token in factor")
TEST(TranslatorCoverageTopOff, Parser_UnexpectedTokenInFactor)
{
    // PRINT THEN -> when parsing expression after PRINT, first token is THEN and triggers factor error
    const std::string src = "10 PRINT THEN\n";
    auto toks = Lexer(src).tokenize();
    Parser p(std::move(toks));
    EXPECT_THROW({ (void)p.parseProgram(); }, std::runtime_error);
}
