# Assignment 8: KD-Trees and Nearest Neighbor Search

## Building the KD-Tree

You should support the following capabilities.

- Starting from an empty tree and given a list of k-dimensional points, build a K-D tree.
- Given a single, k-dimensional query point, return the nearest neighbor in the K-D tree (you must use the structure of your tree and not default to brute force search).

You DO NOT need to support any of the following capabilities

- Incrementally add new points to your K-D tree
- Delete points from your K-D tree
- Look for nearest neighbors of multiple points simultaneously

### Quick Select Implementation (1pt Extra Credit)

File: [include/quick_select.hpp](include/quick_select.hpp)


## Benchmarking Infrastructure

File: [include/benchmark.hpp](include/benchmark.hpp)

- generate

### Experiment Results

K-d tree nearest neighbor search vs. brute force search for K = 2. Each row is the average of 3 runs. Every query time covers searching for 1,000 random test points. All coordinates are random in [0, 1), and the random seed is fixed, so every run uses the same points.

| K | numPoints | KD Build Time (ms) | KD Query Time (ms) | Brute Force (ms) |
|--:|--:|--:|--:|--:|
| 2 | 10 | 0.0051 | 0.0622 | 0.0376 |
| 2 | 100 | 0.0155 | 0.1310 | 0.2498 |
| 2 | 1,000 | 0.1630 | 0.2264 | 1.1202 |
| 2 | 10,000 | 1.3475 | 0.1958 | 7.6678 |
| 2 | 100,000 | 14.4589 | 0.5766 | 78.3134 |