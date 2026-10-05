#include "graph.hpp"
#include <iostream>


int main()
{
    Graph::DirectedGraph<int, double> directed_graph;

    directed_graph.addEdge(1, 2, 3.5);
    
    std::unordered_map<int, double> map = directed_graph.getEdges(1);

    for (const std::pair<int, double>& edge : map) {
        std::cout << edge.first << " -> c: " << edge.second << std::endl;
    }

    // auto val = directed_graph.getVerticies();
    // for (const auto& v : val) {
    //     std::cout << v << std::endl;
    // }

    return 0;

}
