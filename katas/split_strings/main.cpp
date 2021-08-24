#define BOOST_TEST_MODULE SplitStrings
#include <boost/test/included/unit_test.hpp>

#include <string>
#include <vector>
#include <cmath>

std::vector<std::string> solution(const std::string& string)
{
    int number_of_elements = string.size() / 2;
    bool isOdd = string.size() % 2 != 0;

    std::vector<std::string> result(number_of_elements + (isOdd ? 1 : 0), "");
    for(int i = 0; i < number_of_elements; i++)
    {
        result[i] = std::string(string.begin() + (2*i), string.begin() + (2*i + 2));
    }

    if(isOdd)
    {
        result.back() = std::string(string.end() -1, string.end()) + "_";
    }

    return result;
}


//std::vector<std::string> solution(const std::string& string)
//{
//    size_t number_of_elements = std::ceil(string.size() / 2);
//    bool isOdd = string.size() % 2 != 0;
//
//    std::vector<std::string> result;
//    result.reserve(number_of_elements);
//
//    for(size_t i = 0; i < number_of_elements; i++)
//    {
//        std::string s(string.begin() + 2*i, string.begin() + 2*i + 2);
//        result.emplace_back(s);
//    }
//
//    if(isOdd)
//    {
//        std::string s(string.end() -1, string.end());
//        s.append("_");
//        result.emplace_back(s);
//    }
//
//    return result;
//}

bool do_test(const std::string& str, const std::vector<std::string>& vector)
{
    auto result = solution(str);
    return std::equal(result.begin(), result.end(), vector.begin());
}

BOOST_AUTO_TEST_CASE(UniqueTest)
{
    //Even
    BOOST_TEST(do_test("abcdef", {"ab", "cd", "ef"}));
    BOOST_TEST(do_test("HelloWorld", {"He", "ll", "oW", "or", "ld"}));

    //Odd
    BOOST_TEST(do_test("abcde", {"ab", "cd", "e_"}));
    BOOST_TEST(do_test("LovePizza", {"Lo", "ve", "Pi", "zz", "a_"}));
}