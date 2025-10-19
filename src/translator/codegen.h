#pragma once
#include <string>
#include "translator/ast.h"

namespace translator {

class Codegen {
public:
    static std::string emit_cpp(const Program& p);
};

} // namespace translator
