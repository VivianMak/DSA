#include <unordered_map>
#include <string>
#include <optional>

#include "structs.hpp"

bool isValid(std::string& s){

    // static - reuses the built map
    static const std::unordered_map<char, char> map = 
    { // key, value
        {')', '('},
        {']', '['},
        {'}', '{'}
    };

    Structs::Stack<char> stack;

    for (char c : s){
        if (c == '(' || c == '{' || c == '['){
            stack.push(c); // add to back of list
        } else{
            // Check mapping pair (could return char or null)
            std::optional<char> key = stack.pop();

            // if key has no value OR wrong mapping
            if (!key || *key != map.at(c)){
                return false;
            }
        }
    }
    // return when we have checked the entire string
    return stack.isEmpty();
}