#include <iomanip>
#include <iostream>
#include <vector>

#include "benchmark.hpp"
#include "kd_tree.hpp"

int main()
{

    // TESTING KD-TREE USAGE //

    // 2D points
    // constexpr std::size_t K = 2;
    // std::vector<KDTree::Point<K>> points = {
    //     {2, 3}, {5, 4}, {9, 6}, {4, 7}, {8, 1}, {7, 2}
    // };

    // KDTree::KDTree<K> tree(points);

    // KDTree::Point<K> target = {4.1, 7};

    // KDTree::Point<K> best = tree.nearest(target);

    // std::cout << "Target:  (" << target[0] << ", " << target[1] << ")\n";
    // std::cout << "Nearest: (" << best[0] << ", " << best[1] << ")\n";


    // 3D points
    // constexpr std::size_t K = 3;
    // std::vector<KDTree::Point<K>> points = {
    //     {2, 3, 4}, {5, 4, 1}, {9, 6, 11}, {4, 7, 6}, {8, 1, 3}, {7, 2, 9}
    // };

    // KDTree::KDTree<K> tree(points);

    // KDTree::Point<K> target = {2, 3, 100};

    // KDTree::Point<K> best = tree.nearest(target);

    // std::cout << "Target:  (" << target[0] << ", " << target[1] << ", " << target[2] << ")\n";
    // std::cout << "Nearest: (" << best[0] << ", " << best[1] << ", " << best[2] << ")\n";

    // // Brute Force Comparison
    // KDTree::Point<K> bestBF = tree.nearestBF(target);
    // std::cout << "Nearest (BF): (" << bestBF[0] << ", " << bestBF[1] << ", " << bestBF[2] << ")\n";


    // Benchmarking KDTree vs brute force //

    // Configs
    constexpr std::size_t K = 10;
    const int numRuns = 5;
    std::vector<int> numPointsList = {10, 100, 1000, 10000, 100000, 1000000};

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "K | numPoints | buildTime (ms) | queryTime (ms) | bruteForceTime (ms)\n";

    for (int numPoints : numPointsList){

        Benchmark::Duration buildTotal{0};
        Benchmark::Duration queryTotal{0};
        Benchmark::Duration bruteForceTotal{0};

        for (int run = 0; run < numRuns; run++){
            auto [buildTime, queryTime, bruteForceTime] = Benchmark::runExperiment<K>(numPoints);
            buildTotal += buildTime;
            queryTotal += queryTime;
            bruteForceTotal += bruteForceTime;
        }

        // Average over all runs
        std::cout << K << " | " << numPoints
                  << " | " << (buildTotal / numRuns).count()
                  << " | " << (queryTotal / numRuns).count()
                  << " | " << (bruteForceTotal / numRuns).count() << "\n";
    }

    return 0;
}
