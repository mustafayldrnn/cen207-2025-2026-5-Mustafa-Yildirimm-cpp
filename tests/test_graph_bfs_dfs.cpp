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

TEST(Graph, DirectedGraph){
    ds::Graph g(4);
    g.add_edge(0, 1, false); // directed edge
    g.add_edge(1, 2, false);
    g.add_edge(2, 3, false);
    
    auto dist = g.bfs_dist(0);
    EXPECT_EQ(dist[0], 0);
    EXPECT_EQ(dist[1], 1);
    EXPECT_EQ(dist[2], 2);
    EXPECT_EQ(dist[3], 3);
}

TEST(Graph, DisconnectedComponents){
    ds::Graph g(6);
    // First component: 0-1-2
    g.add_edge(0, 1, true);
    g.add_edge(1, 2, true);
    // Second component: 3-4-5
    g.add_edge(3, 4, true);
    g.add_edge(4, 5, true);
    
    auto dist = g.bfs_dist(0);
    EXPECT_EQ(dist[0], 0);
    EXPECT_EQ(dist[1], 1);
    EXPECT_EQ(dist[2], 2);
    // Nodes 3,4,5 should be unreachable from 0
    EXPECT_EQ(dist[3], -1);
    EXPECT_EQ(dist[4], -1);
    EXPECT_EQ(dist[5], -1);
}

TEST(Graph, DFSOrder){
    ds::Graph g(5);
    g.add_edge(0, 1, true);
    g.add_edge(0, 2, true);
    g.add_edge(1, 3, true);
    g.add_edge(2, 4, true);
    
    auto order = g.dfs_order(0);
    EXPECT_EQ(order.front(), 0); // Start node
    EXPECT_EQ(order.back(), 4); // Should reach the end
}

