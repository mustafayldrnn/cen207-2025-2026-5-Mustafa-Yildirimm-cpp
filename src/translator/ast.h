#pragma once
#include <memory>
#include <string>
#include <vector>

namespace translator {

enum class ExprKind { Number, Variable, Binary };

struct Expr {
    virtual ~Expr() = default;
    virtual ExprKind kind() const = 0;
};

struct NumberExpr : Expr {
    double value;
    explicit NumberExpr(double v) : value(v) {}
    ExprKind kind() const override { return ExprKind::Number; }
};

struct VariableExpr : Expr {
    std::string name;
    explicit VariableExpr(std::string n) : name(std::move(n)) {}
    ExprKind kind() const override { return ExprKind::Variable; }
};

struct BinaryExpr : Expr {
    char op;
    std::unique_ptr<Expr> lhs;
    std::unique_ptr<Expr> rhs;
    BinaryExpr(char op, std::unique_ptr<Expr> l, std::unique_ptr<Expr> r)
        : op(op), lhs(std::move(l)), rhs(std::move(r)) {}
    ExprKind kind() const override { return ExprKind::Binary; }
};

enum class StmtKind { Let, Print, Input, Goto, IfGoto, Gosub, Return };

struct Stmt { virtual ~Stmt() = default; virtual StmtKind kind() const = 0; };

struct LetStmt : Stmt {
    std::string name; std::unique_ptr<Expr> expr;
    LetStmt(std::string n, std::unique_ptr<Expr> e) : name(std::move(n)), expr(std::move(e)) {}
    StmtKind kind() const override { return StmtKind::Let; }
};

struct PrintStmt : Stmt {
    std::vector<std::unique_ptr<Expr>> items;
    explicit PrintStmt(std::vector<std::unique_ptr<Expr>> xs) : items(std::move(xs)) {}
    StmtKind kind() const override { return StmtKind::Print; }
};

struct InputStmt : Stmt {
    std::string name; explicit InputStmt(std::string n) : name(std::move(n)) {}
    StmtKind kind() const override { return StmtKind::Input; }
};

struct GotoStmt : Stmt {
    int target; explicit GotoStmt(int t) : target(t) {}
    StmtKind kind() const override { return StmtKind::Goto; }
};

struct IfGotoStmt : Stmt {
    std::unique_ptr<Expr> cond; int target;
    IfGotoStmt(std::unique_ptr<Expr> c, int t) : cond(std::move(c)), target(t) {}
    StmtKind kind() const override { return StmtKind::IfGoto; }
};

struct GosubStmt : Stmt {
    int target; explicit GosubStmt(int t) : target(t) {}
    StmtKind kind() const override { return StmtKind::Gosub; }
};

struct ReturnStmt : Stmt {
    StmtKind kind() const override { return StmtKind::Return; }
};

struct Program {
    // Parallel arrays: one statement per label index
    std::vector<int> labels; // e.g., 10, 20, 30
    std::vector<std::unique_ptr<Stmt>> stmts;
    // Label -> index map will be provided via lookup helper.
};

} // namespace translator
