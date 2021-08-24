#define BOOST_TEST_MODULE ValidBraces
#include <boost/test/included/unit_test.hpp>

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

BOOST_AUTO_TEST_CASE(UniqueTest)
{
    BOOST_TEST(valid_braces("(){}[]")   == true);
    BOOST_TEST(valid_braces("([{}])")   == true);
    BOOST_TEST(valid_braces("(}")       == false);
    BOOST_TEST(valid_braces("[(])")     == false);
    BOOST_TEST(valid_braces("[({})](]") == false);
    BOOST_TEST(valid_braces("()")       == true);
    BOOST_TEST(valid_braces("{}")       == true);
    BOOST_TEST(valid_braces("[]")       == true);
    BOOST_TEST(valid_braces("[(])")     == false);
    BOOST_TEST(valid_braces("){}")      == false);
    BOOST_TEST(valid_braces("")         == true);
    BOOST_TEST(valid_braces(" ")        == true);
}
