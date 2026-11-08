#pragma once

#include <vector>
#include <stdexcept>

namespace QS{

    /**
     * Given an array with left-most and right-most element,
     * move smaller elements to the left and bigger elements to the right.
     * 
     * @return the index of the median
     */
    template <typename T>
    int partition(std::vector<T>& arr, int l, int r, int dim){

        // Assigns x as the right most element, as pivot
        int x = arr[r][dim];

        int i = l;

        // Loop through l to r sub array
        for (int j = l; j <= r - 1; j++) {

            // if element is less than pivot
            // case 1: swap itself when i=j
            // case 2: swap the biggest seen element
            if (arr[j][dim] <= x) {
                std::swap(arr[i], arr[j]);
                i++;
            }
        }

        // Finally swap the pivot with the big/small divider
        swap(arr[i], arr[r]);

        return i;
    }

    /**
     * Find the kth smallest/largest element in array
     * 
     * @param arr: array to find element in
     * @param l: left most element
     * @param r: right most element
     * @param k: kth element you are looking for (ie k is the median index)
     * 
     * Return index of smalles/targest element in array
     */
    template <typename T>
    int quick_select(std::vector<T>& arr, int l, int r, int k, int dim){

        // Make sure kth element is within size of arr
        if (k > 0 && k <= r-l+1){

            // Get the index of the last element after partitioning
            int index = partition(arr, l, r);

            // If position is the same as k, found -> return
            if (index - l == k - 1)
                return arr[index];

            // If position is too high, partition left subarray
            if (index - l > k - 1) 
                return quick_select(arr, l, index - 1, k);

            // If position is too low, parition right subarray 
            return quick_select(arr, index + 1, r, k - (index - l - 1));
        }

        throw std::out_of_range("k out of range");

    }

} // namespace QS