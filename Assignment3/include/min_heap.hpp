/*Ported from https://github.com/OlinDSA2024/Assignment03/blob/main/src/main/kotlin/MinHeap.kt#L11 */
#pragma once

#include <vector>
#include <unordered_map>
#include <optional>
#include <utility>

namespace MinHeap {

    template <typename T>
    class MinHeap {
    private:
        std::vector<std::pair<T, double>> vertices;
        std::unordered_map<T, int> indexMap;

        /** Bubble down from startIndex if needed */
        void bubbleDown(int startIndex) {
            const int size = static_cast<int>(vertices.size());
            const double startNumber = vertices[startIndex].second;
            const int leftIndex = getLeftIndex(startIndex);
            const int rightIndex = getRightIndex(startIndex);

            const bool hasLeft = leftIndex < size;
            const bool hasRight = rightIndex < size;

            // Case 1: every existing child is larger, so we're done
            if ((!hasLeft || startNumber < vertices[leftIndex].second) &&
                (!hasRight || startNumber < vertices[rightIndex].second)) {
                return;
            }
            // Case 2: swap with left since it is the smallest child
            else if (!hasRight || (hasLeft && vertices[leftIndex].second < vertices[rightIndex].second)) {
                swap(leftIndex, startIndex);
                bubbleDown(leftIndex);
            }
            // Case 3: swap with right since it is the smallest child
            else {
                swap(rightIndex, startIndex);
                bubbleDown(rightIndex);
            }
        }

        /** Swap index1 and index2 in the tree, keeping indexMap in sync */
        void swap(int index1, int index2) {
            indexMap[vertices[index1].first] = index2;
            indexMap[vertices[index2].first] = index1;
            std::swap(vertices[index1], vertices[index2]);
        }

        /** Percolate up from startIndex if needed */
        void percolateUp(int startIndex) {
            const int parentIndex = getParentIndex(startIndex);
            if (parentIndex < 0) {
                return; // at the root
            } else if (vertices[startIndex].second < vertices[parentIndex].second) {
                swap(parentIndex, startIndex);
                percolateUp(parentIndex);
            }
        }

        static int getParentIndex(int of) {
            // Note: in C++ (and Kotlin), (0 - 1) / 2 == 0 because integer
            // division truncates toward zero, so the root must be special-cased.
            return of == 0 ? -1 : (of - 1) / 2;
        }

        static int getLeftIndex(int of)  { return of * 2 + 1; }
        static int getRightIndex(int of) { return of * 2 + 2; }

    public:
        bool isEmpty() const {
            return vertices.empty();
        }

        /**
         * Insert data into the heap with value heapNumber
         * @return true if data is added, false if it was already there
         */
        bool insert(const T& data, double heapNumber) {
            if (contains(data)) {
                return false;
            }
            vertices.push_back({data, heapNumber});
            indexMap[data] = static_cast<int>(vertices.size()) - 1;
            percolateUp(static_cast<int>(vertices.size()) - 1);
            return true;
        }

        /**
         * Removes and returns the minimum element
         * @return the minimum element, or std::nullopt if the heap is empty
         */
        std::optional<T> getMin() {
            if (vertices.empty()) {
                return std::nullopt;
            }
            T result = vertices[0].first;
            if (vertices.size() > 1) {
                swap(0, static_cast<int>(vertices.size()) - 1);
            }
            vertices.pop_back();
            indexMap.erase(result);
            if (!vertices.empty()) {
                bubbleDown(0);
            }
            return result;
        }

        /**
         * Change the number of an element
         * @return true if the element exists and was updated, false otherwise
         */
        bool adjustHeapNumber(const T& vertex, double newNumber) {
            std::optional<int> index = getIndex(vertex);
            if (!index) {
                return false;
            }
            vertices[*index].second = newNumber;
            // do both to avoid explicitly testing which way to go
            percolateUp(*index);
            bubbleDown(indexMap[vertex]); // element may have moved during percolateUp
            return true;
        }

        bool contains(const T& vertex) const {
            return indexMap.find(vertex) != indexMap.end();
        }

        /** @return the index where the element is stored, or std::nullopt if not there */
        std::optional<int> getIndex(const T& of) const {
            auto it = indexMap.find(of);
            if (it == indexMap.end()) {
                return std::nullopt;
            }
            return it->second;
        }
    };

} // namespace MinHeap