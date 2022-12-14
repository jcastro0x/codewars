#include <gtest/gtest.h>

#include <string>
#include <vector>
#include <numeric>

// Parse integer into vector of ints that represent each
// digit.
std::vector<int> split_number(int n)
{
    const std::string string_number = std::to_string(n);
    std::vector<int> numbers;
    numbers.reserve(string_number.size());

    for(const char& sn : string_number)
        numbers.emplace_back(sn - '0');

    return numbers;
}

int digital_root(int n)
{
    const auto numbers = split_number(n);
    const auto total   = std::accumulate(numbers.begin(), numbers.end(), 0);

    return total >= 10
    ? digital_root(total)
    : total;

    // Clever solution:
    return --n % 9 + 1;
}

TEST(Codewars, digital_root)
{
    EXPECT_EQ(digital_root(16),     7);
    EXPECT_EQ(digital_root(195),    6);
    EXPECT_EQ(digital_root(992),    2);
    EXPECT_EQ(digital_root(167346), 9);
    EXPECT_EQ(digital_root(0),      0);
}
