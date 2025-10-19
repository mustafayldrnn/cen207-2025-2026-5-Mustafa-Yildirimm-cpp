#pragma once
#include <string>
#include "ds/hash_table.h"

namespace translator {

class SymbolTable {
    ds::HashTable<std::string, double> table_;
public:
    bool define(const std::string& name, double value){ return table_.insert(name, value); }
    bool assign(const std::string& name, double value){ return table_.insert(name, value); }
    const double* lookup(const std::string& name) const { return table_.find(name); }
};

} // namespace translator

