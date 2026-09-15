#pragma once

#include <vector>

namespace Structs{

    template <typename T>
    class StackNode{
        public:

            StackNode(T data, T* ptr &next);

            // Check if stack is empty
            bool isEmpty();

            // Returns top (last) element w/o removing
            T peek();

            // Add to top (last) of list
            void push();

            // Removes the top element, reassigns top pointer
            T pop();

            

        private:
            std::vector<T> stack;

    }
    

}