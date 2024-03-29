#include <gtest/gtest.h>

#include <vector>
#include <numeric>

std::vector<int> get_multiples(int number)
{
    std::vector<int> multiples;
    for(int i = 1; i < number; i++)
    {
        if(i % 3 == 0 || i % 5 == 0)
            multiples.emplace_back(i);
    }

    return multiples;
}

int solution(int number)
{
    int total = 0;
    std::vector<int> multiples;
    for(int i = 1; i < number; i++)
    {
        if(i % 3 == 0 || i % 5 == 0)
            total += i;
    }

    return total;
}

TEST(Codewars, multiples_of_3_or_5)
{
    EXPECT_EQ(solution(10), 23);
}
