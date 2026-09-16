#include <iostream>
#include "valid_parentheses.hpp"

int main()
{   
    std::string str = "([])";
    bool valid = isValid(str);

    std::cout << str << ": " << (valid ? "true" : "false") << std::endl;

    return 0;
}
