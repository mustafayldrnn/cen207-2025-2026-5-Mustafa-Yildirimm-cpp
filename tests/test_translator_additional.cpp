// Ek kapsama: parser hata yolları, otomatik etiketler ve codegen dalları
// Bu testler, lexer/parser/codegen için eksik kalan akışları hedefler.

#include <gtest/gtest.h>
#include <string>
#include "translator/lexer.h"
#include "translator/parser.h"
#include "translator/codegen.h"
#include "translator/ast.h"

using namespace translator;

// Yardımcı: kaynak metnini parse edip Program döndür
static Program parse_program_from(const char* src){
    Lexer lx(src);
    auto toks = lx.tokenize();
    Parser ps(std::move(toks));
    return ps.parseProgram();
}

TEST(ParserErrors, MissingRParen){
    const char* src = "10 PRINT (1 + 2\n"; // ')' eksik
    Lexer lx(src);
    auto toks = lx.tokenize();
    Parser ps(std::move(toks));
    EXPECT_THROW((void)ps.parseProgram(), std::runtime_error);
}

TEST(ParserErrors, UnknownStatement){
    const char* src = "10 FOOBAR\n"; // desteklenmeyen ifade
    Lexer lx(src);
    auto toks = lx.tokenize();
    Parser ps(std::move(toks));
    EXPECT_THROW((void)ps.parseProgram(), std::runtime_error);
}

TEST(ParserErrors, LetMissingAssign){
    const char* src = "10 LET X 5\n"; // '=' eksik
    Lexer lx(src);
    auto toks = lx.tokenize();
    Parser ps(std::move(toks));
    EXPECT_THROW((void)ps.parseProgram(), std::runtime_error);
}

TEST(ParserErrors, InputNeedsIdentifier){
    const char* src = "10 INPUT 123\n";
    Lexer lx(src);
    auto toks = lx.tokenize();
    Parser ps(std::move(toks));
    EXPECT_THROW((void)ps.parseProgram(), std::runtime_error);
}

TEST(ParserErrors, IfRequiresThen){
    const char* src = "10 IF 1 20\n"; // THEN eksik
    Lexer lx(src);
    auto toks = lx.tokenize();
    Parser ps(std::move(toks));
    EXPECT_THROW((void)ps.parseProgram(), std::runtime_error);
}

TEST(ParserErrors, IfThenRequiresNumber){
    const char* src = "10 IF 1 THEN X\n"; // sayı yerine kimlik
    Lexer lx(src);
    auto toks = lx.tokenize();
    Parser ps(std::move(toks));
    EXPECT_THROW((void)ps.parseProgram(), std::runtime_error);
}

TEST(ParserErrors, GotoRequiresNumber){
    const char* src = "10 GOTO X\n";
    Lexer lx(src);
    auto toks = lx.tokenize();
    Parser ps(std::move(toks));
    EXPECT_THROW((void)ps.parseProgram(), std::runtime_error);
}

TEST(ParserProgram, AutoLabelsWhenMissing){
    // Satır numarası yoksa 10,20,... üretir
    const char* src = "LET X = 1\nPRINT X\n";
    auto prog = parse_program_from(src);
    ASSERT_EQ(prog.stmts.size(), 2u);
    ASSERT_EQ(prog.labels.size(), 2u);
    EXPECT_EQ(prog.labels[0], 10);
    EXPECT_EQ(prog.labels[1], 20);
}

TEST(Lexer, UnknownCharIsIgnored){
    // '@' bilinmeyen — token üretilmeden atlanmalı
    Lexer lx("10 LET X = 1 @ 2\n");
    auto toks = lx.tokenize();
    // Number tokenlarının en az iki kez gelmesini bekleriz
    int number_count = 0;
    for (auto& t : toks) if (t.type == TokenType::Number) ++number_count;
    EXPECT_GE(number_count, 2);
}

TEST(CodegenPaths, EmptyProgramReturnsEarly){
    // Boş program
    Program p; // labels ve stmts boş
    auto out = Codegen::emit_cpp(p);
    // erken return içermeli
    EXPECT_NE(out.find("return 0;"), std::string::npos);
}

TEST(CodegenPaths, InputGotoIfGosubReturn){
    const char* src =
        "10 INPUT X\n"
        "20 IF X THEN 40\n"
        "30 GOTO 50\n"
        "40 GOSUB 60\n"
        "50 PRINT X\n"
        "60 RETURN\n";
    auto prog = parse_program_from(src);
    auto out = Codegen::emit_cpp(prog);
    // INPUT üretimi
    EXPECT_NE(out.find("std::cin >> tmp"), std::string::npos);
    // IF THEN else bir sonraki etikete gidiş
    EXPECT_NE(out.find("if (var[\"X\"])"), std::string::npos);
    EXPECT_NE(out.find("else pc = 30;"), std::string::npos); // 20'den sonraki etiket 30
    // GOSUB çağrısı ve dönüş
    EXPECT_NE(out.find("call.push(50); pc = 60;"), std::string::npos);
    EXPECT_NE(out.find("if (call.empty()) return 0; pc = call.top(); call.pop();"), std::string::npos);
}

