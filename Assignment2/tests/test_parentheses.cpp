#include <gtest/gtest.h>
#include <string>
 
#include "valid_parentheses.hpp"

TEST(ValidParenthesis, CheckPairingCase)
{
    std::string str = "()";

    bool valid = isValid(str);
    EXPECT_EQ(valid, 1);
}

TEST(ValidParenthesis, NestedCase)
{
    std::string str = "([{}])";

    bool valid = isValid(str);
    EXPECT_EQ(valid, 1);
}

TEST(ValidParenthesis, SequentialCase)
{
    std::string str = "()[]{}";

    bool valid = isValid(str);
    EXPECT_EQ(valid, 1);
}

TEST(ValidParenthesis, AlternateNestingCase)
{
    std::string str = "([)]";

    bool valid = isValid(str);
    EXPECT_EQ(valid, 0);
}

TEST(ValidParenthesis, WrongMatchCase)
{
    std::string str = "(]";

    bool valid = isValid(str);
    EXPECT_EQ(valid, 0);
}