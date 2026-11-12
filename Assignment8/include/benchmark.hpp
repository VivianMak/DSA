

namespace Benchmark
{
    /**
     * Benchmark [KDTree] against brute force nearest neighbor.
     * 1000 test points will be generated to test against the training
     * points.
     *
     * @param k: the dimensionality of the dataset to create
     * @param numPoints: the number of points to use to match against
     *   (1000 test points will be used)
     * @return the triple of [Duration] objects where the first specifies
     * the time to build the tree, the second specifies the time it takes
     * to query the tree with 1,000 points, and the third is the time it
     * takes to find the nearest neighbor to these points using the brute
     * force approach.
     */
    void runExperiment(k: Int, numPoints: Int): Triple<Duration, Duration, Duration> {
        // your implementation here
    }


    int main(){

        return 0;
    }

} // namespace Benchmark
