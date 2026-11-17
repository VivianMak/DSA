#pragma once

#include <chrono>
#include <cstddef>
#include <tuple>

#include "kd_tree.hpp"


namespace Benchmark
{
    // Elapsed time in milliseconds, stored as a double so small times keep their decimals
    using Duration = std::chrono::duration<double, std::milli>;

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

        // TODO: generate numPoints random training points
        // TODO: generate 1000 random test points

        // TODO: time building the tree
        Duration buildTime{0};

        // TODO: time tree.nearest() on every test point
        Duration queryTime{0};

        // TODO: time tree.nearestBF() on every test point
        Duration bruteForceTime{0};

        return {buildTime, queryTime, bruteForceTime};
    }

} // namespace Benchmark
