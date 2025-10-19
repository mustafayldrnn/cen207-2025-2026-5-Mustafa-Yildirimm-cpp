#pragma once
#include "ds/graph.h"
#include "translator/ast.h"
#include <unordered_map>

namespace translator {

struct CFG {
    ds::Graph g;
    // label -> index mapping for convenience
    std::unordered_map<int, int> label_to_index;
};

inline CFG build_cfg(const Program& p){
    CFG cfg; int n = static_cast<int>(p.stmts.size()); cfg.g.resize(n);
    for (int i=0;i<n;i++){ cfg.label_to_index[p.labels[i]] = i; }
    auto next_index = [&](int i)->int{ return (i+1<n)?(i+1):-1; };
    for (int i=0;i<n;i++){
        auto& s = p.stmts[i];
        int ni = next_index(i);
        switch (s->kind()){
            case StmtKind::Goto: {
                int tgt = static_cast<GotoStmt*>(s.get())->target;
                auto it = cfg.label_to_index.find(tgt);
                if (it!=cfg.label_to_index.end()) cfg.g.add_edge(i, it->second);
                break;
            }
            case StmtKind::IfGoto: {
                int tgt = static_cast<IfGotoStmt*>(s.get())->target;
                auto it = cfg.label_to_index.find(tgt);
                if (it!=cfg.label_to_index.end()) cfg.g.add_edge(i, it->second);
                if (ni!=-1) cfg.g.add_edge(i, ni);
                break;
            }
            case StmtKind::Gosub: {
                int tgt = static_cast<GosubStmt*>(s.get())->target;
                auto it = cfg.label_to_index.find(tgt);
                if (it!=cfg.label_to_index.end()) cfg.g.add_edge(i, it->second);
                if (ni!=-1) cfg.g.add_edge(i, ni);
                break;
            }
            case StmtKind::Return: {
                // No default successor
                break;
            }
            default: {
                if (ni!=-1) cfg.g.add_edge(i, ni);
                break;
            }
        }
    }
    return cfg;
}

} // namespace translator
