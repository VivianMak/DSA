#pragma once
#include "min_heap.hpp"
#include <optional>

namespace PriorityQueue{
/**
 * ``MinPriorityQueue`` maintains a priority queue where the lower
 *  the priority value, the sooner the element will be removed from
 *  the queue.
 *  @param T the representation of the items in the queue
 */
    
    template <typename T, typename Priority = double>
    class MinPriorityQueue{

        private:
            MinHeap::MinHeap<T, Priority> queue;

        public:

            /*
            * @return true if the queue is empty, false otherwise
            */
            bool isEmpty(){
                return queue.empty();
            }   
            
            /*
            * Add [elem] with at level [priority]
            */
            void addWithPriority(T elem, Priority priority){
                return queue.insert(elem, priority);
            }

            /*
            * Get the next (highest priority) element and remove this element from the queue.
            * @return the next element in terms of priority.  If empty, return null.
            */
           std::optional<T> next(){
                if (queue.empty()){
                    return std::nullopt;
                }
                return queue.getMin();
           }

           /*
           * @param elem: whose priority should change
           * @param new_priority: the priority to use for element
           * the lower the priority the earlier the element in the order
           */
           void adjustPriority(T elem, Priority new_priority){
                return queue.adjustHeapNumber(elem, newPriority);
           }

    };
}