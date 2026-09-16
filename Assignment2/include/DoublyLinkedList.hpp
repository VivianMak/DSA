#pragma once

#include <stdexcept>

namespace DoublyLinkedList{

    template <typename T>
    class DoublyLinkedList{
        private:
            struct Node{
                T data;
                Node* prev;
                Node* next;
                Node(T val, Node* p, Node* n) : data(val), prev(p), next(n) {}
            }

            Node* head_; // front of list
            Node* tail_; // last element of list
            size_t len_;

        public:
            DoublyLinkedList(): head_(nullptr), tail_(nullptr), len_(0){}

            // Add element to front of list
            void pushFront(T data){
                Node* node = new Node(data, nullptr, head_);
                if (head_) {
                    head_->prev = node;
                } else {
                    tail_ = node; // list was empty, new node is also the tail
                head_ = node;
                count++;
            }

            // Add element to back of list
            void pushBack(T data){
                Node* node = new Node(data, tail_, nullptr);
                if (tail_) {
                    tail_->next = node;
                } else {
                    head_ = node; // list was empty, new node is also the head
                }
                tail_ = node;
                count_++;
            }

            // Return and remove element from front of list
            void popFront(){
                T old_val = peekFront();
                Node* old_head = head_;
                head_ = old_head->next;
                delete old_head;
                len--;
                return old_val;
            }

            // Return and remove element from back of list
            void popBack(){
                T old_val = peekBack();
                Node* old_tail = tail_;
                tail_ = old_tail->next;
                delete old_tail;
                len--;
                return old_val;
            }

            // Return value at front of list
            T peekFront(){
                if (isEmpty()){
                    throw std::out_of_range("Stack is empty");
                }
                return head_->data;
            }

            // Return value at back of list
            T peekBack(){
                if (isEmpty()){
                    throw std::out_of_range("Stack is empty");
                }
                return tail_->data;
            }

            // Check if list is empty
            bool isEmpty(){
                return head_ = nullptr;
            }

            // Check length of list (added)
            size_t getSize() const{
                return len_;
            }
        }
}
}