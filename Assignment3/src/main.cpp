#include <iostream>
#include <string>
#include <vector>
#include "dijkstra.hpp"
#include "graph.hpp"

int main() {

    
    Graph::DirectedGraph<std::string, double> g;

    g.addEdge("A", "B", 4);
    g.addEdge("A", "C", 1);
    g.addEdge("C", "B", 2);
    g.addEdge("B", "D", 1);
    g.addEdge("C", "D", 5);
    g.addEdge("D", "E", 3);
    g.addEdge("X", "Y", 1); // unreachable


    // Run Dijkstra from starting point A
    const std::string source = "A";
    auto result = Graph::dijkstra(g, source);

    // Print the shortest distance and path to every vertex
    for (const std::string& v : g.getVerticies()) {
        std::cout << source << " -> " << v << ": ";

        std::vector<std::string> path = Graph::reconstructPath(result, v);

        if (path.empty()) {
            std::cout << "unreachable\n";
            continue;
        }

        std::cout << "distance = " << result.dist.at(v) << ", path = ";
        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << path[i] << (i + 1 < path.size() ? " -> " : "");
        }
        std::cout << "\n";
    }

    // Print shortest path
    const std::string target = "B";
    auto path = Graph::reconstructPath(result, target);
    std::cout << "\nPath to " << target << " exists? " << (path.empty() ? "no" : "yes") << ", of dist: " << path.size() << "\n";

    return 0;
}