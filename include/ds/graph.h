/**
 * @file graph.h
 * @brief Basit yönlü/yönsüz grafik yardımcıları.
 */
#pragma once
#include <vector>
#include <queue>

namespace ds {

/** @brief Komşuluk listesi tabanlı grafik. */
class Graph {
    std::vector<std::vector<int>> adj_;
public:
    /** @brief n düğüm ile oluşturur. */
    explicit Graph(int n=0): adj_(n) {}
    /** @brief Düğüm sayısını ayarlar. */
    void resize(int n){ adj_.assign(n, {}); }
    /** @brief Kenar ekler (opsiyonel yönsüz). */
    void add_edge(int u, int v, bool undirected=false){ adj_[u].push_back(v); if (undirected) adj_[v].push_back(u); }
    /** @brief u’nun komşuları. */
    const std::vector<int>& neighbors(int u) const { return adj_[u]; }
    /** @brief Düğüm sayısı. */
    int size() const { return static_cast<int>(adj_.size()); }

    /** @brief s kaynağından BFS uzaklıkları. */
    std::vector<int> bfs_dist(int s) const {
        std::vector<int> dist(size(), -1); std::queue<int> q; dist[s]=0; q.push(s);
        while(!q.empty()){ int u=q.front(); q.pop(); for(int v:adj_[u]) if(dist[v]==-1){ dist[v]=dist[u]+1; q.push(v);} }
        return dist;
    }

    /** @brief DFS yardımcı. */
    void dfs_util(int u, std::vector<int>& vis, std::vector<int>& order) const {
        vis[u]=1; order.push_back(u); for(int v:adj_[u]) if(!vis[v]) dfs_util(v, vis, order);
    }
    /** @brief s’den DFS sırası. */
    std::vector<int> dfs_order(int s=0) const { std::vector<int> vis(size(),0), order; if(s<size()) dfs_util(s, vis, order); return order; }
};

} // namespace ds
