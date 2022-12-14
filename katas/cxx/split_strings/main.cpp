#include <gtest/gtest.h>

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

bool do_test(const std::string& str, const std::vector<std::string>& vector)
{
    auto result = solution(str);
    return std::equal(result.begin(), result.end(), vector.begin());
}

TEST(Codewars, split_strings)
{
    //Even
    EXPECT_TRUE(do_test("abcdef", {"ab", "cd", "ef"}));
    EXPECT_TRUE(do_test("HelloWorld", {"He", "ll", "oW", "or", "ld"}));

    //Odd
    EXPECT_TRUE(do_test("abcde", {"ab", "cd", "e_"}));
    EXPECT_TRUE(do_test("LovePizza", {"Lo", "ve", "Pi", "zz", "a_"}));
}
