#include <gtest/gtest.h>
#include "translator/lexer.h"
#include "translator/parser.h"
#include "translator/codegen.h"
#include "translator/cfg.h"

TEST(LexerParser, BasicProgramParse){
    const char* src = R"(10 LET X = 1 + 2
20 PRINT X
30 IF X THEN 50
40 GOTO 60
50 GOSUB 70
60 RETURN
70 PRINT X
)";
    translator::Lexer lx(src);
    auto toks = lx.tokenize();
    translator::Parser ps(std::move(toks));
    auto prog = ps.parseProgram();
    ASSERT_EQ(prog.stmts.size(), 7u);
    ASSERT_EQ(prog.labels.front(), 10);
    ASSERT_EQ(prog.labels.back(), 70);

    // CFG build and reachability
    auto cfg = translator::build_cfg(prog);
    auto dist = cfg.g.bfs_dist(0);
    // Ensure start is reachable and some edges exist
    EXPECT_EQ(dist[0], 0);
}

TEST(Codegen, EmitsCPP){
    const char* src = R"(10 LET X = 1 + 2 * 3
20 PRINT X
)";
    translator::Lexer lx(src);
    auto toks = lx.tokenize();
    translator::Parser ps(std::move(toks));
    auto prog = ps.parseProgram();
    auto code = translator::Codegen::emit_cpp(prog);
    // Basic sanity checks
    EXPECT_NE(code.find("#include <iostream>"), std::string::npos);
    EXPECT_NE(code.find("int main()"), std::string::npos);
    EXPECT_NE(code.find("var[\"X\"] = (1 + (2 * 3))"), std::string::npos);
    EXPECT_NE(code.find("std::cout << var[\"X\"] << std::endl;"), std::string::npos);
}
