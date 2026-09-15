#include "structs.hpp"

#include <iostream>
#include <vector>

namespace Structs{

    template <typename T>
    StackNode::StackNode(
        T data, T* ptr &next
    ){};

    bool isEmpty(){
        if (stack.empty()){
            return true;
        }
        return false;
    };

    T peek(){
        return stack.back()
    }

    void push(int new_data){
        int x = StackNode(new_data, next = top)
        top = x;
    };

    int pop(){
        T top_value = peek();
        // delete first, then re reference
        stack.erase(stack.begin() + top_value);
        top = top.next;
        return top_value
    };


}   // namespace Structs