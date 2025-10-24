/**
 * @file codegen.h
 * @brief AST'ten C++ kodu üretimi için arabirim
 * @author Mustafa Yıldırım
 * @date 2025
 * @version 1.0
 */
#pragma once
#include <string>
#include "translator/ast.h"

namespace translator {

/**
 * @brief C++ kaynak çıktısı üreten yardımcı sınıf
 * 
 * Bu sınıf, Abstract Syntax Tree'i alarak C++ kaynak kodu üretir.
 * BASIC benzeri dildeki programları C++ koduna dönüştürür.
 */
class Codegen {
public:
    /**
     * @brief Verilen Program'dan C++ kodu üretir
     * @param p Çevrilecek program AST'i
     * @return Üretilen C++ kaynak kodu
     */
    static std::string emit_cpp(const Program& p);
};

} // namespace translator
