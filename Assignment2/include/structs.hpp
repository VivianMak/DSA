#pragma once

#include "DoublyLinkedList.hpp"
#include <optional>

// Notes
// - "->": dereference a pointer, then access a member / (*ptr).member
// - 

namespace Structs{

    // Last in first out
    template <typename T>
    class Stack{
        private:
            DoublyLinkedList<T> list_;

        public:
            //  Add [data] to the top (last) of the stack
            void push(T data){
                list_.pushBack(data);
            }

            // Remove element at top (last) of queue
            // @return value at tail or null
            std::optional<T> pop(){
                return list.popBack();
            }

            // @return value at tail or null
            std::optional<T> peek(){
                return list.peekBack();
            }

            // Check if list is empty
            bool isEmpty(){
                return list_.isEmpty();
            }

            size_t getSize() const{
                return list_.getSize();
            }
    };

    template <typename T>
    class Queue {
        private:
            DoublyLinkedList<T> list_;

        public:

            // Add [data] to end of queue
            void enqueue(T data){
                list_.pushBack(data);
            }

            // Remove element at front of queue
            // @return value at head or null
            std::optional<T> dequeue(){
                return list_.popFront();
            }
            
            // @return value at head or null
            std::optional<T> peek(){
                return list_.peekFront();
            }

            // Check if list is empty
            bool isEmpty(){
                return list_.isEmpty();
            }

            size_t getSize() const{
                return list_.getSize();
            }

    };
}