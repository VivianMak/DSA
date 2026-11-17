#pragma once

#include <chrono>
#include <cstddef>
#include <random>
#include <stdexcept>
#include <tuple>
#include <vector>

#include "kd_tree.hpp"


namespace Benchmark
{
    // Elapsed time in milliseconds, stored as a double so small times keep their decimals
    using Duration = std::chrono::duration<double, std::milli>;

    /**
     * Generate random K dimensional points, each coordinate uniform in [0, 1).
     *
     * @tparam K: the dimensionality of each point
     * @param n: how many points to make
     * @param rng: random number generator, passed by reference so each call
     *   continues the same random sequence instead of restarting it
     *
     * @return vector of n random points
     */
    template <std::size_t K>
    std::vector<KDTree::Point<K>> randomPoints(int n, std::mt19937& rng){

        // Every coordinate is drawn from the same range
        std::uniform_real_distribution<double> coord(0.0, 1.0);

        std::vector<KDTree::Point<K>> points(n);

        // Fill each coordinate of each point
        for (KDTree::Point<K>& p : points){
            for (std::size_t d = 0; d < K; d++){
                p[d] = coord(rng);
            }
        }

        return points;
    }

    /**
     * Benchmark [KDTree] against brute force nearest neighbor.
     * 1000 test points will be generated to test against the training
     * points.
     *
     * @tparam K: the dimensionality of the dataset to create
     *   (a template parameter because KDTree<K> needs it at compile time)
     * @param numPoints: the number of points to use to match against
     *   (1000 test points will be used)
     * @return the triple of [Duration] objects where the first specifies
     * the time to build the tree, the second specifies the time it takes
     * to query the tree with 1,000 points, and the third is the time it
     * takes to find the nearest neighbor to these points using the brute
     * force approach.
     */
    template <std::size_t K>
    std::tuple<Duration, Duration, Duration> runExperiment(int numPoints){

        // Fixed seed
        std::mt19937 rng(42);

        // Points stored in the tree, and points we search for
        std::vector<KDTree::Point<K>> trainPoints = randomPoints<K>(numPoints, rng);
        std::vector<KDTree::Point<K>> testPoints = randomPoints<K>(1000, rng);

        using Clock = std::chrono::steady_clock;

        // Reserve space for results
        std::vector<KDTree::Point<K>> treeResults;
        std::vector<KDTree::Point<K>> bruteForceResults;

        treeResults.reserve(testPoints.size());
        bruteForceResults.reserve(testPoints.size());


        // Time to build tree
        auto start = Clock::now();
        KDTree::KDTree<K> tree(trainPoints);
        auto end = Clock::now();
        Duration buildTime = end - start;


        // Nearest neighbors on kd tree
        start = Clock::now();
        for (const KDTree::Point<K>& target : testPoints){
            treeResults.push_back(tree.nearest(target));
        }
        end = Clock::now();
        Duration queryTime = end - start;


        // Brute force searching 
        start = Clock::now();
        for (const KDTree::Point<K>& target : testPoints){
            bruteForceResults.push_back(tree.nearestBF(target));
        }
        end = Clock::now();
        Duration bruteForceTime = end - start;


        return {buildTime, queryTime, bruteForceTime};
    }

} // namespace Benchmark
