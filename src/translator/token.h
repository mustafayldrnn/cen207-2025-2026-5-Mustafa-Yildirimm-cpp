#pragma once
#include <string>

namespace translator {

enum class TokenType {
    Identifier, Number, String,
    KW_LET, KW_PRINT, KW_INPUT, KW_IF, KW_THEN, KW_GOTO, KW_FOR, KW_TO, KW_NEXT, KW_GOSUB, KW_RETURN,
    Plus, Minus, Star, Slash, Assign, LParen, RParen, Comma, Newline, Eof
};

struct Token { TokenType type; std::string lexeme; int line; };

} // namespace translator

