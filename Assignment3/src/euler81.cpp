#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "dijkstra.hpp"

using Grid = std::vector<std::vector<int>>;

// Read a comma-separated matrix, one row per line
Grid readMatrix(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("Could not open " + path);
    }

    Grid grid;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string cell;
        std::vector<int> row;
        while (std::getline(ss, cell, ',')) {
            row.push_back(std::stoi(cell));
        }
        grid.push_back(row);
    }
    return grid;
}

// Minimal path sum from top-left to bottom-right moving only right and down
int minPathSum(const Grid& grid) {
    const int rows = static_cast<int>(grid.size());
    const int cols = static_cast<int>(grid[0].size());

    // Encode cell (r, c) as a single int so it works as a vertex
    auto id = [cols](int r, int c) { return r * cols + c; };
    // Pyton verions: cell_id = lambda r, c: r * cols + c

    // Build the graph: edge cost = value of the cell being moved into
    Graph::DirectedGraph<int, int> g;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            // moving left
            if (c + 1 < cols) g.addEdge(id(r, c), id(r, c + 1), grid[r][c + 1]);
            // moving down
            if (r + 1 < rows) g.addEdge(id(r, c), id(r + 1, c), grid[r + 1][c]);
        }
    }

    auto result = Graph::dijkstra(g, id(0, 0));

    // Edges only count cells we move into, so add the starting cell back
    return result.dist.at(id(rows - 1, cols - 1)) + grid[0][0];
}

int main(int argc, char* argv[]) {
    const std::string path = (argc > 1) ? argv[1] : "../data/0081_matrix.txt";

    Grid grid = readMatrix(path);
    std::cout << "Minimal path sum: " << minPathSum(grid) << "\n";

    return 0;
}