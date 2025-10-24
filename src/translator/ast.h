/**
 * @file ast.h
 * @brief Basit ifade ve deyim ağaçları (AST) tanımları
 * @author Mustafa Yıldırım
 * @date 2025
 * @version 1.0
 */
#pragma once
#include <memory>
#include <string>
#include <vector>

namespace translator {

/**
 * @brief İfade türleri
 */
enum class ExprKind { 
    Number,     ///< Sayısal sabit
    Variable,   ///< Değişken referansı
    Binary      ///< İkili işlem
};

/**
 * @brief Tüm ifade türleri için taban tür
 * 
 * Abstract Syntax Tree'deki tüm ifadeler bu sınıftan türetilir.
 */
struct Expr {
    virtual ~Expr() = default;
    /**
     * @brief İfade türünü döndürür
     * @return İfade türü
     */
    virtual ExprKind kind() const = 0;
};

/**
 * @brief Sayısal sabit ifadesi
 */
struct NumberExpr : Expr {
    double value;  ///< Sayısal değer
    
    /**
     * @brief Sayısal sabit oluşturur
     * @param v Sayısal değer
     */
    explicit NumberExpr(double v) : value(v) {}
    
    /**
     * @brief İfade türünü döndürür
     * @return Number türü
     */
    ExprKind kind() const override { return ExprKind::Number; }
};

/**
 * @brief Değişken ifadesi
 */
struct VariableExpr : Expr {
    std::string name;  ///< Değişken adı
    
    /**
     * @brief Değişken ifadesi oluşturur
     * @param n Değişken adı
     */
    explicit VariableExpr(std::string n) : name(std::move(n)) {}
    
    /**
     * @brief İfade türünü döndürür
     * @return Variable türü
     */
    ExprKind kind() const override { return ExprKind::Variable; }
};

/**
 * @brief İkili işlem ifadesi
 */
struct BinaryExpr : Expr {
    char op;                        ///< İşlem operatörü
    std::unique_ptr<Expr> lhs;      ///< Sol operand
    std::unique_ptr<Expr> rhs;      ///< Sağ operand
    
    /**
     * @brief İkili işlem ifadesi oluşturur
     * @param op İşlem operatörü
     * @param l Sol operand
     * @param r Sağ operand
     */
    BinaryExpr(char op, std::unique_ptr<Expr> l, std::unique_ptr<Expr> r)
        : op(op), lhs(std::move(l)), rhs(std::move(r)) {}
    
    /**
     * @brief İfade türünü döndürür
     * @return Binary türü
     */
    ExprKind kind() const override { return ExprKind::Binary; }
};

/**
 * @brief Deyim türleri
 */
enum class StmtKind { 
    Let,        ///< Atama deyimi
    Print,      ///< Yazdırma deyimi
    Input,      ///< Giriş deyimi
    Goto,       ///< Atlama deyimi
    IfGoto,     ///< Koşullu atlama deyimi
    Gosub,      ///< Alt program çağırma deyimi
    Return      ///< Alt programdan dönüş deyimi
};

/**
 * @brief Tüm deyimler için taban tür
 * 
 * Abstract Syntax Tree'deki tüm deyimler bu sınıftan türetilir.
 */
struct Stmt { 
    virtual ~Stmt() = default; 
    
    /**
     * @brief Deyim türünü döndürür
     * @return Deyim türü
     */
    virtual StmtKind kind() const = 0; 
};

/**
 * @brief LET atama deyimi
 */
struct LetStmt : Stmt {
    std::string name;                    ///< Değişken adı
    std::unique_ptr<Expr> expr;          ///< Atanacak ifade
    
    /**
     * @brief Atama deyimi oluşturur
     * @param n Değişken adı
     * @param e Atanacak ifade
     */
    LetStmt(std::string n, std::unique_ptr<Expr> e) : name(std::move(n)), expr(std::move(e)) {}
    
    /**
     * @brief Deyim türünü döndürür
     * @return Let türü
     */
    StmtKind kind() const override { return StmtKind::Let; }
};

/**
 * @brief PRINT deyimi
 */
struct PrintStmt : Stmt {
    std::vector<std::unique_ptr<Expr>> items;  ///< Yazdırılacak ifadeler
    
    /**
     * @brief Yazdırma deyimi oluşturur
     * @param xs Yazdırılacak ifadeler
     */
    explicit PrintStmt(std::vector<std::unique_ptr<Expr>> xs) : items(std::move(xs)) {}
    
    /**
     * @brief Deyim türünü döndürür
     * @return Print türü
     */
    StmtKind kind() const override { return StmtKind::Print; }
};

/**
 * @brief INPUT deyimi
 */
struct InputStmt : Stmt {
    std::string name;  ///< Giriş alınacak değişken adı
    
    /**
     * @brief Giriş deyimi oluşturur
     * @param n Değişken adı
     */
    explicit InputStmt(std::string n) : name(std::move(n)) {}
    
    /**
     * @brief Deyim türünü döndürür
     * @return Input türü
     */
    StmtKind kind() const override { return StmtKind::Input; }
};

/**
 * @brief GOTO deyimi
 */
struct GotoStmt : Stmt {
    int target;  ///< Hedef satır numarası
    
    /**
     * @brief Atlama deyimi oluşturur
     * @param t Hedef satır numarası
     */
    explicit GotoStmt(int t) : target(t) {}
    
    /**
     * @brief Deyim türünü döndürür
     * @return Goto türü
     */
    StmtKind kind() const override { return StmtKind::Goto; }
};

/**
 * @brief IF THEN GOTO deyimi
 */
struct IfGotoStmt : Stmt {
    std::unique_ptr<Expr> cond;  ///< Koşul ifadesi
    int target;                  ///< Hedef satır numarası
    
    /**
     * @brief Koşullu atlama deyimi oluşturur
     * @param c Koşul ifadesi
     * @param t Hedef satır numarası
     */
    IfGotoStmt(std::unique_ptr<Expr> c, int t) : cond(std::move(c)), target(t) {}
    
    /**
     * @brief Deyim türünü döndürür
     * @return IfGoto türü
     */
    StmtKind kind() const override { return StmtKind::IfGoto; }
};

/**
 * @brief GOSUB deyimi
 */
struct GosubStmt : Stmt {
    int target;  ///< Hedef alt program satır numarası
    
    /**
     * @brief Alt program çağırma deyimi oluşturur
     * @param t Hedef satır numarası
     */
    explicit GosubStmt(int t) : target(t) {}
    
    /**
     * @brief Deyim türünü döndürür
     * @return Gosub türü
     */
    StmtKind kind() const override { return StmtKind::Gosub; }
};

/**
 * @brief RETURN deyimi
 */
struct ReturnStmt : Stmt {
    /**
     * @brief Deyim türünü döndürür
     * @return Return türü
     */
    StmtKind kind() const override { return StmtKind::Return; }
};

/**
 * @brief Etiketlenmiş deyimlerden oluşan program
 * 
 * Program, paralel diziler kullanarak etiket-deyim çiftlerini tutar.
 */
struct Program {
    std::vector<int> labels;                      ///< Satır etiketleri (örn: 10, 20, 30)
    std::vector<std::unique_ptr<Stmt>> stmts;     ///< Her etikete karşılık gelen deyimler
    // Label -> index map will be provided via lookup helper.
};

} // namespace translator
