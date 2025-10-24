/**
 * @file token.h
 * @brief Leksik belirteç türleri ve veri yapısı
 * @author Mustafa Yıldırım
 * @date 2025
 * @version 1.0
 */
#pragma once
#include <string>

namespace translator {

/**
 * @brief Tüm belirteç türleri
 */
enum class TokenType {
    Identifier, Number, String,
    KW_LET, KW_PRINT, KW_INPUT, KW_IF, KW_THEN, KW_GOTO, KW_FOR, KW_TO, KW_NEXT, KW_GOSUB, KW_RETURN,
    Plus, Minus, Star, Slash, Assign, LParen, RParen, Comma, Newline, Eof
};

/**
 * @brief Belirteç kaydı
 * 
 * Her belirteç, türü, metni ve satır numarasını içerir.
 */
struct Token { 
    TokenType type;      ///< Belirteç türü
    std::string lexeme;  ///< Belirteç metni
    int line;            ///< Satır numarası
};

} // namespace translator

