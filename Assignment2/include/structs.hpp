#pragma once

#include <stdexcept>

// Notes
// - "->": dereference a pointer, then access a member / (*ptr).member
// - 

namespace Structs{

    template <typename T>
    class Stack{
        private:
            struct sNode {
                T data;
                sNode* next;
                sNode(T val, sNode* nxt): data(val), net(nxt) {}
            }

            sNode* top;
            size_t len;

        public:

            Stack() : top(nullptr), len(0) {}


            StackNode(T data, T* ptr &next);

            // Check if stack is empty
            bool isEmpty() const {
                // top points to null when stack is empty
                if (top == nullptr){
                    return true;
                }
                return false;
            };

            // Returns top (last) element w/o removing
            T peek() const {
                if (isEmpty()){
                    throw std::out_of_range("Stack is empty");
                }
                return top->data
            };

            // Add to top (last) of list
            void push(T new_data) {
                // new node should point to previous top of data
                sNode* new_node = new sNode(new_data, top);
                top = new_node;
                len++;
            };

            // Removes the top element, reassigns top pointer
            T pop() {
                if (isEmpty()){
                    throw std::out_of_range("Stack is empty");
                }
                sNode* old_top = top;
                T value = old_top->data;
                top = old_top->next; // move the top pointer to next node
                delete old_top;
                len--;
                return value;
            };
    }

    template <typename T>
    class Queue {
        private:
            struct qNode{
                T data;
                sNode* next;
                sNode(T val, sNode* nxt): data(val), net(nxt) {}
            }
    }
    

}