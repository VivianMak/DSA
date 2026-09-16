#pragma once

#include <iostream>
#include <optional>


namespace DoublyLinkedList{

    template <typename T>
    class DoublyLinkedList{
        private:
            struct Node{
                T data;
                Node* prev;
                Node* next;
                Node(T val, Node* p, Node* n) : data(val), prev(p), next(n) {}
            };

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
                len_++;
                }
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
                len_++;
            }

            // Return and remove element from front of list
            std::optional<T> popFront(){
                if (isEmpty()) {
                    return std::nullopt;
                }

                Node* old_head = head_;
                T old_val = old_head->data;

                head_ = old_head->next;
                if (head_) {
                    head_->prev = nullptr;
                } else {
                    tail_ = nullptr; // list is now empty
                }

                delete old_head;
                len_--;
                return old_val;
            }

            // Return and remove element from back of list
            std::optional<T> popBack(){
                if (isEmpty()) {
                    return std::nullopt;
                }

                Node* old_tail = tail_;
                T value = old_tail->data;

                tail_ = old_tail->prev;
                if (tail_) {
                    tail_->next = nullptr;
                } else {
                    head_ = nullptr; // list is now empty
                }

                delete old_tail;
                len_--;
                return value;
            }

            // Return value at front of list
            std::optional<T> peekFront(){
                if (isEmpty()){
                    std::cout << "List is empty." << std::endl;
                    return std::nullopt;
                }
                return head_->data;
            }

            // Return value at back of list
            std::optional<T> peekBack(){
                if (isEmpty()){
                    std::cout << "List is empty" << std::endl;
                    return std::nullopt;
                }
                return tail_->data;
            }

            // Check if list is empty
            bool isEmpty(){
                return head_ == nullptr;
            }

            // Check length of list (added)
            size_t getSize() const{
                return len_;
            }
        };
}