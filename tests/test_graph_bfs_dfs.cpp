#include <gtest/gtest.h>
#include "ds/graph.h"

TEST(Graph, BFSandDFS){
    ds::Graph g(6);
    g.add_edge(0,1,true); g.add_edge(1,2,true); g.add_edge(2,3,true); g.add_edge(3,4,true); g.add_edge(4,5,true);
    auto dist = g.bfs_dist(0);
    EXPECT_EQ(dist[0],0); EXPECT_EQ(dist[5],5);
    auto order = g.dfs_order(0);
    ASSERT_FALSE(order.empty());
    EXPECT_EQ(order.front(), 0);
}

