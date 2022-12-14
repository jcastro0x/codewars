#include <gtest/gtest.h>

#include <string>
#include <unordered_map>
#include <queue>

bool valid_braces(std::string_view string)
{
    const std::unordered_map<char,char> braces_map = {
        {'(', ')'},
        {'[', ']'},
        {'{', '}'}
    };

    auto getBraceInfo = [&](char c) {
        for(const auto&[open,close] : braces_map)
        {
            if(c == close) return std::make_pair(true, open);
        }
        return std::make_pair(false, c);
    };

    std::deque<char> braces;
    for(const auto& c : string)
    {
        auto[isClose, otherChar] = getBraceInfo(c);
        if(isClose)
        {
            if(braces.empty()) return false;

            char back = braces.back(); braces.pop_back();
            if(back != otherChar) return false;
        }
        else braces.push_back(otherChar);
    }

    return true;
}

TEST(Codewars, valid_braces)
{
    EXPECT_TRUE(valid_braces("(){}[]"));
    EXPECT_TRUE(valid_braces("([{}])"));
    EXPECT_TRUE(valid_braces("()"));
    EXPECT_TRUE(valid_braces("{}"));
    EXPECT_TRUE(valid_braces("[]"));
    EXPECT_TRUE(valid_braces(""));
    EXPECT_TRUE(valid_braces(" "));

    EXPECT_FALSE(valid_braces("(}"));
    EXPECT_FALSE(valid_braces("[(])"));
    EXPECT_FALSE(valid_braces("[({})](]"));
    EXPECT_FALSE(valid_braces("[(])"));
    EXPECT_FALSE(valid_braces("){}"));
}
