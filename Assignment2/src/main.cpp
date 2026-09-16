#include <iostream>
#include "valid_parenthesis.hpp"

int main()
{   
    std::string str = "([])";
    bool valid = isValid(str);

    std::cout << str << ": " << (valid ? "true" : "false") << std::endl;

    return 0;
}
