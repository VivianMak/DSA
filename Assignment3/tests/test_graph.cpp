#include <gtest/gtest.h>
#include "graph.hpp"

TEST(DirectedGraph, getVerticies)
{
    Graph::DirectedGraph<int, double> g;
    
    // Initial graph with no verticies
    EXPECT_TRUE(g.getVerticies().empty());

    // Add an Edge, should have 2 verticies now
    g.addEdge(1,2,6);

    std::unordered_set<int> val = g.getVerticies();
    EXPECT_EQ(val.size(), 2);

    // Add an Edge, should have 3 verticies now
    g.addEdge(3,2,5);

    val = g.getVerticies();
    EXPECT_EQ(val.size(), 3);
}

TEST(DirectedGraph, getEdgesFromVertex2) {
    Graph::DirectedGraph<int, double> g;
    g.addEdge(2,1,6);
    g.addEdge(2,3,5);

    std::unordered_map<int, double> edges = g.getEdges(2);
    ASSERT_EQ(edges.size(), 2);
    EXPECT_EQ(edges.at(1), 6);
    EXPECT_EQ(edges.at(3), 5);
}

TEST(DirectedGraph, clear){
    Graph::DirectedGraph<int, double> g;
    g.addEdge(1,2,6);
    g.addEdge(3,2,5);
    g.clear();

    EXPECT_TRUE(g.getVerticies().empty());
}