#pragma once
#include <vector>
#include <memory>
#include "translator/token.h"

namespace translator {

struct ASTNode { virtual ~ASTNode() = default; };
using AST = std::vector<std::unique_ptr<ASTNode>>;

class Parser {
    const std::vector<Token> tokens_;
public:
    explicit Parser(std::vector<Token> toks): tokens_(std::move(toks)) {}
    AST parseProgram() const; // skeleton
};

} // namespace translator

