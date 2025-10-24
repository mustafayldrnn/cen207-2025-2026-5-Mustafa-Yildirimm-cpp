/**
 * @file cfg.h
 * @brief Programdan kontrol akışı grafiği (CFG) üretimi yardımcıları
 * @author Mustafa Yıldırım
 * @date 2025
 * @version 1.0
 */
#pragma once
#include "ds/graph.h"
#include "translator/ast.h"
#include <unordered_map>

namespace translator {

/**
 * @brief CFG yapısı (graf + etiket→indeks eşlemesi)
 * 
 * Control Flow Graph, programın kontrol akışını temsil eden graf yapısıdır.
 * Her düğüm bir deyimi, her kenar ise kontrol akışını temsil eder.
 */
struct CFG {
    ds::Graph g;                                    ///< Kontrol akışı grafı
    std::unordered_map<int, int> label_to_index;    ///< Etiket→indeks eşlemesi
};

/**
 * @brief Programdan basit CFG oluşturur
 * @param p Girdi programı
 * @return Üretilen CFG
 * 
 * Bu fonksiyon, BASIC programındaki GOTO, IF-GOTO, GOSUB ve RETURN
 * deyimlerini analiz ederek kontrol akışı grafını oluşturur.
 */
inline CFG build_cfg(const Program& p){
    CFG cfg; 
    int n = static_cast<int>(p.stmts.size()); 
    cfg.g.resize(n);
    
    // Etiket→indeks eşlemesini oluştur
    for (int i=0;i<n;i++){ 
        cfg.label_to_index[p.labels[i]] = i; 
    }
    
    // Bir sonraki indeksi hesaplayan lambda
    auto next_index = [&](int i)->int{ return (i+1<n)?(i+1):-1; };
    
    // Her deyim için kontrol akışını analiz et
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
                // Return deyiminde varsayılan ardıl yok
                break;
            }
            default: {
                // Diğer deyimler için varsayılan ardıl
                if (ni!=-1) cfg.g.add_edge(i, ni);
                break;
            }
        }
    }
    return cfg;
}

} // namespace translator
