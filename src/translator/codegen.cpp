/**
 * @file codegen.cpp
 * @brief AST'yi C++ kaynak koduna dönüştüren yordamların uygulaması.
 */
#include "translator/codegen.h"
#include <sstream>

namespace translator {

/**
 * \brief İfadeyi (Expr) C++ koduna yazar.
 * \param os Çıktı akışı
 * \param e  Yazdırılacak ifade düğümü
 */
static void emit_expr(std::ostream& os, const Expr* e){
    switch (e->kind()){
        case ExprKind::Number: os << static_cast<const NumberExpr*>(e)->value; break;
        case ExprKind::Variable: os << "var[\"" << static_cast<const VariableExpr*>(e)->name << "\"]"; break;
        case ExprKind::Binary: {
            auto* b = static_cast<const BinaryExpr*>(e);
            os << '('; emit_expr(os, b->lhs.get()); os << ' ' << b->op << ' '; emit_expr(os, b->rhs.get()); os << ')';
            break;
        }
    }
}

/**
 * \brief Verilen Program AST'sinden C++ kodu üretir.
 * \param p Etiketlenmiş deyimlerden oluşan Program
 * \return Derlenebilir C++ kaynak kodu
 */
std::string Codegen::emit_cpp(const Program& p){
    std::ostringstream ss;
    ss << "#include <iostream>\n";
    ss << "#include <string>\n";
    ss << "#include <unordered_map>\n";
    ss << "#include <stack>\n\n";
    ss << "int main(){\n";
    ss << "  std::unordered_map<std::string,double> var;\n";
    ss << "  std::stack<int> call;\n";
    if (p.stmts.empty()) { ss << "  return 0;\n}"; return ss.str(); }
    int start = p.labels.front();
    ss << "  int pc = " << start << ";\n";
    ss << "  while(true){\n";
    ss << "    switch(pc){\n";
    for (std::size_t i=0;i<p.stmts.size();++i){
        int lbl = p.labels[i];
        ss << "    case " << lbl << ": {\n";
        const auto& st = p.stmts[i];
        auto next_label = (i+1<p.stmts.size()) ? p.labels[i+1] : -1;
        switch (st->kind()){
            case StmtKind::Let: {
                auto* s = static_cast<LetStmt*>(st.get());
                ss << "      var[\"" << s->name << "\"] = "; emit_expr(ss, s->expr.get()); ss << ";\n";
                if (next_label!=-1) ss << "      pc = " << next_label << "; break;\n"; else ss << "      return 0;\n";
                break;
            }
            case StmtKind::Print: {
                auto* s = static_cast<PrintStmt*>(st.get());
                ss << "      std::cout";
                for (std::size_t k=0;k<s->items.size();++k){
                    ss << " << "; emit_expr(ss, s->items[k].get());
                }
                ss << " << std::endl;\n";
                if (next_label!=-1) ss << "      pc = " << next_label << "; break;\n"; else ss << "      return 0;\n";
                break;
            }
            case StmtKind::Input: {
                auto* s = static_cast<InputStmt*>(st.get());
                ss << "      { double tmp; std::cin >> tmp; var[\"" << s->name << "\"] = tmp; }\n";
                if (next_label!=-1) ss << "      pc = " << next_label << "; break;\n"; else ss << "      return 0;\n";
                break;
            }
            case StmtKind::Goto: {
                auto* s = static_cast<GotoStmt*>(st.get());
                ss << "      pc = " << s->target << "; break;\n";
                break;
            }
            case StmtKind::IfGoto: {
                auto* s = static_cast<IfGotoStmt*>(st.get());
                ss << "      if ("; emit_expr(ss, s->cond.get()); ss << ") pc = " << s->target << "; else ";
                if (next_label!=-1) ss << "pc = " << next_label << ";\n"; else ss << "return 0;\n";
                ss << "      break;\n";
                break;
            }
            case StmtKind::Gosub: {
                auto* s = static_cast<GosubStmt*>(st.get());
                if (next_label!=-1) ss << "      call.push(" << next_label << "); pc = " << s->target << "; break;\n"; else ss << "      return 0;\n";
                break;
            }
            case StmtKind::Return: {
                ss << "      if (call.empty()) return 0; pc = call.top(); call.pop(); break;\n";
                break;
            }
        }
        ss << "    }\n";
    }
    ss << "    default: return 0;\n";
    ss << "    }\n";
    ss << "  }\n";
    ss << "}\n";
    return ss.str();
}

} // namespace translator
