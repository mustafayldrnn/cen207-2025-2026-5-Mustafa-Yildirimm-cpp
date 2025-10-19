#include "translator/lexer.h"
#include <cctype>

namespace translator {

static bool is_ident_start(char c){ return std::isalpha(static_cast<unsigned char>(c)) || c=='_'; }
static bool is_ident_char(char c){ return std::isalnum(static_cast<unsigned char>(c)) || c=='_'; }

std::vector<Token> Lexer::tokenize() const {
    std::vector<Token> out; int line=1; std::size_t i=0, n=src_.size();
    auto add=[&](TokenType t, const std::string& lx){ out.push_back({t,lx,line}); };
    while (i<n){ char c = src_[i];
        if (c=='\r'){ ++i; continue; }
        if (c=='\n'){ add(TokenType::Newline, "\n"); ++i; ++line; continue; }
        if (std::isspace(static_cast<unsigned char>(c))){ ++i; continue; }
        if (c=='"'){
            ++i; std::string s; while(i<n && src_[i] != '"'){ if(src_[i]=='\n') ++line; s.push_back(src_[i++]); }
            if (i<n && src_[i]=='"') ++i; add(TokenType::String, s); continue;
        }
        if (std::isdigit(static_cast<unsigned char>(c))){ std::string num; while(i<n && std::isdigit(static_cast<unsigned char>(src_[i]))) num.push_back(src_[i++]); add(TokenType::Number, num); continue; }
        if (is_ident_start(c)){
            std::string id; while(i<n && is_ident_char(src_[i])) id.push_back(src_[i++]);
            std::string up; up.reserve(id.size()); for(char ch:id) up.push_back(std::toupper(static_cast<unsigned char>(ch)));
            if (up=="LET") add(TokenType::KW_LET, id);
            else if (up=="PRINT") add(TokenType::KW_PRINT, id);
            else if (up=="INPUT") add(TokenType::KW_INPUT, id);
            else if (up=="IF") add(TokenType::KW_IF, id);
            else if (up=="THEN") add(TokenType::KW_THEN, id);
            else if (up=="GOTO") add(TokenType::KW_GOTO, id);
            else if (up=="FOR") add(TokenType::KW_FOR, id);
            else if (up=="TO") add(TokenType::KW_TO, id);
            else if (up=="NEXT") add(TokenType::KW_NEXT, id);
            else if (up=="GOSUB") add(TokenType::KW_GOSUB, id);
            else if (up=="RETURN") add(TokenType::KW_RETURN, id);
            else add(TokenType::Identifier, id);
            continue;
        }
        switch(c){
            case '+': add(TokenType::Plus, "+"); ++i; break;
            case '-': add(TokenType::Minus, "-"); ++i; break;
            case '*': add(TokenType::Star, "*"); ++i; break;
            case '/': add(TokenType::Slash, "/"); ++i; break;
            case '=': add(TokenType::Assign, "="); ++i; break;
            case '(': add(TokenType::LParen, "("); ++i; break;
            case ')': add(TokenType::RParen, ")"); ++i; break;
            case ',': add(TokenType::Comma, ","); ++i; break;
            default: ++i; break;
        }
    }
    out.push_back({TokenType::Eof, "", line});
    return out;
}

} // namespace translator

