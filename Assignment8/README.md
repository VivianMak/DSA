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

My implementation of quick select is in reference to [wikipedia](https://en.wikipedia.org/wiki/Quickselect) and [geeks for geeks](https://www.geeksforgeeks.org/dsa/quickselect-algorithm/). Essentially, the goal of the quick select algortihm is to find the median by choosing a pivot element and moving smaller numbers to the left and bigger numbers to the right. As you balance out the numbers on each side (doesn't matter if unsorted), you have found the median. This resursive algorithm runs on average, in log n time.

### Brute force Implementation

The brute force implemntation lives in the KD-Tree class as another function. This loops over the entire list of points and files the nearest point based on distance.


```cpp
/** Find the point in the tree closes to target, using brute force
 * 
 * @param points: all points 
 * @param target: target point
 * 
 * @return closest point
 */
Point<K> nearestBF(const Point<K>& target){

    // check empty list
    if (all_points.empty())
        throw std::out_of_range("Tree is empty.");

    Point<K> best = all_points[0];

    for (std::size_t i = 1; i < all_points.size(); i++){
        // call closest with point params
        best = closest(target, all_points[i], best);
    }

    return best;
}
```

## Benchmarking Infrastructure

File: [include/benchmark.hpp](include/benchmark.hpp)

The goal is to compare the KD tree data structure and brute force searching when solvign the nearest neighbor problem. I have used node dimentions of `K=2` and `K=3`, searching over point lengths of `{10, 100, 1000, 10000, 100000, 1000000}`, and searching for 1,000 random test points. The results below are averaged over 5 runs each. The use of the destroyer node clears up memory to prevent leakage.

### Experiment Results

| K | numPoints | KD Build Time (ms) | KD Query Time (ms) | Brute Force (ms) |
|--:|--:|--:|--:|--:|
| 2 | 10 | 0.0044 | 0.0844 | 0.0504 |
| 2 | 100 | 0.0238 | 0.2043 | 0.4123 |
| 2 | 1,000 | 0.2247 | 0.2516 | 1.7817 |
| 2 | 10,000 | 1.2739 | 0.1706 | 7.7636 |
| 2 | 100,000 | 14.3317 | 0.3480 | 76.2749 |
| 2 | 1,000,000 | 164.9299 | 0.8065 | 827.5976 |

| K | numPoints | KD Build Time (ms) | KD Query Time (ms) | Brute Force (ms) |
|--:|--:|--:|--:|--:|
| 3 | 10 | 0.0072 | 0.1475 | 0.0780 |
| 3 | 100 | 0.0102 | 0.1367 | 0.1610 |
| 3 | 1,000 | 0.1159 | 0.2687 | 1.3522 |
| 3 | 10,000 | 1.4493 | 0.4425 | 12.2622 |
| 3 | 100,000 | 16.3472 | 0.8234 | 120.8086 |
| 3 | 1,000,000 | 194.6365 | 1.4316 | 1481.6258 |

Below is a graphical representation of the data above:

![](data/plot.png)

-You provide an interpretation of your benchmarking results and provide conclusions as to when brute force versus k-d trees would work better.

## AI Acknowledgement
- AI used for generating python script to plot data