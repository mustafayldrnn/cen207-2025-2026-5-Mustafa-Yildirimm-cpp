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
    Identifier,   ///< Değişken adları
    Number,       ///< Sayısal sabitler
    String,       ///< Çift tırnak içindeki metinler
    KW_LET,       ///< LET anahtar sözcüğü
    KW_PRINT,     ///< PRINT anahtar sözcüğü
    KW_INPUT,     ///< INPUT anahtar sözcüğü
    KW_IF,        ///< IF anahtar sözcüğü
    KW_THEN,      ///< THEN anahtar sözcüğü
    KW_GOTO,      ///< GOTO anahtar sözcüğü
    KW_FOR,       ///< FOR anahtar sözcüğü
    KW_TO,        ///< TO anahtar sözcüğü
    KW_NEXT,      ///< NEXT anahtar sözcüğü
    KW_GOSUB,     ///< GOSUB anahtar sözcüğü
    KW_RETURN,    ///< RETURN anahtar sözcüğü
    Plus,         ///< '+'
    Minus,        ///< '-'
    Star,         ///< '*'
    Slash,        ///< '/'
    Assign,       ///< '='
    LParen,       ///< '('
    RParen,       ///< ')'
    Comma,        ///< ','
    Newline,      ///< Satır sonu
    Eof           ///< Girdi sonu (end-of-file)
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
