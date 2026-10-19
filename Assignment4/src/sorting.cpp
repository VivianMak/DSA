#include "sorting.hpp"

#include <algorithm>
#include <vector>
#include <utility>
#include <iostream>
#include <print>

namespace Sorting
{   
    /*
    * Insertion Sort
    * - inserting each element of an unsorted list into its correct position
    *   in a sorted portion of the list
    */
    void insertion_sort(std::vector<int>& array){
        if (array.empty()) return;

        // begin with the 1st element 
        // (assume a list of 1 element is already sorted)
        for (int i = 1; i < array.size(); i++){

            // key is current value to be sorted
            int key = array[i];

            int j = i-1;

            // while the sorted list hasnt ended, moving down
            // and the prev index is still greater than curr value key
            while(j>=0 && array[j] > key){
                // shift element to the right
                array[j+1] = array[j];
                j = j-1;
            }
            // replace shifted element with the curr value
            array[j+1] = key;
        }
    }

    /*
    * Selection Sort
    * - selecting smallest element and swapping with first unsorted element
    */
    void selection_sort(std::vector<int>& array){
        if (array.empty()) return;

        for (int i = 0; i < array.size()-1; i++){

            // start with first unsorted element
            int min_idx = i;

            // from first unsorted element + 1 until end of list
            // find the smallest element and keep track of index
            for (int j = i+1; j < array.size(); j++){
                if (array[min_idx] > array[j]){
                    min_idx = j;
                }
            }
            
            // swap the first unsorted and min element
            int swap_val = array[i];
            array[i] = array[min_idx];
            array[min_idx] = swap_val;

            // iterate n-1 times
        }
    }

    /*
    * Heap Sort
    */
    void heapify(std::vector<int>& array, int n, int root){
        // Initialize largest as root
        int largest = root;

        // left index = 2*i + 1
        int l = 2 * root + 1;

        // right index = 2*i + 2
        int r = 2 * root + 2;

        // If left child is larger than root
        if (l < n && array[l] > array[largest])
            largest = l;

        // If right child is larger than largest so far
        if (r < n && array[r] > array[largest])
            largest = r;

        // If largest is not root
        if (largest != root) {
            std::swap(array[root], array[largest]);

            // Recursively heapify the affected sub-tree
            heapify(array, n, largest);
        }
        
    }

    void heap_sort(std::vector<int>& array){
        if (array.empty()) return;

        int n = array.size();

        // Build heap (rearrange vector)
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(array, n, i);
        
        // One by one extract an element from heap
        for (int i = n - 1; i > 0; i--) {

            // Move current root to end
            std::swap(array[0], array[i]);

            // std::println("Loop ...");
            // std::print("[");
            // for (std::size_t j = 0; j < array.size(); ++j)
            //     std::print("{}{}", j ? ", " : "", array[j]);
            // std::println("]");

            // Call max heapify on the reduced heap
            heapify(array, i, 0);
        }

    }

    void sort_by_digits_place(std::vector<int>& array, long long digits){

        // Create output array
        int n = array.size();
        std::vector<int> output(n);

        // Set the count of 0-9 digits to 0
        int count[10] = {}; 

        // Count how many numbers have each digit (0-9)
        for (int i = 0; i < n; i++)
            count[(array[i] / digits) % 10]++;

        // Prefix sums: count[d] = the position in output arr
        for (int d = 1; d < 10; d++)
            count[d] += count[d - 1];

        // Place numbers into output, walking backward to keep the prev sorted digits
        for (int i = n - 1; i >= 0; i--) {
            int digit = (array[i] / digits) % 10;
            output[--count[digit]] = array[i];
        }

        array = output;

    }

    /*
    * Radix Sort
    * - sort by 1s, 10s, 100s digits place
    */
    void radix_sort(std::vector<int>& array){
        if (array.empty()) return;

        int max = *std::max_element(array.begin(), array.end());

        for (long long digits_place = 1; max/digits_place > 0; digits_place *= 10){
            sort_by_digits_place(array, digits_place);

            // std::println("processing digits = {:<3} ", digits_place);
            // // Show vector
            // std::print("[");
            // for (std::size_t i = 0; i < array.size(); ++i)
            //     std::print("{}{}", i ? ", " : "", array[i]);
            // std::println("]");
        }

    }  // non-negative ints
}
