#include <gtest/gtest.h>

#include <cstdint>
#include <set>

void spread(std::set<uint64_t> &hamming, const uint64_t n)
{
    constexpr auto umax = std::numeric_limits<uint64_t>::max();

    if (hamming.find(n) == hamming.end())
    {
        hamming.insert(n);

        if (n < umax / 2) spread(hamming, n * 2);
        if (n < umax / 3) spread(hamming, n * 3);
        if (n < umax / 5) spread(hamming, n * 5);
    }
}

uint64_t hamber(const int n)
{
    static std::vector<uint64_t> ordered;
    static bool initialize = false;

    if(!initialize)
    {
        std::set<uint64_t> hamming;
        spread(hamming, 1);
        ordered = std::vector<uint64_t>(hamming.begin(), hamming.end());
        initialize = true;
    }

    return ordered[n-1];
}

TEST(Codewars, hamming_numbers)
{
    EXPECT_EQ(hamber(5),    5);
    EXPECT_EQ(hamber(8),    9);
    EXPECT_EQ(hamber(11),  15);
    EXPECT_EQ(hamber(14),  20);
    EXPECT_EQ(hamber(17),  27);
    EXPECT_EQ(hamber(20),  36);
    EXPECT_EQ(hamber(23),  48);
    EXPECT_EQ(hamber(26),  60);
    EXPECT_EQ(hamber(29),  75);
    EXPECT_EQ(hamber(32),  90);
    EXPECT_EQ(hamber(35), 108);
    EXPECT_EQ(hamber(38), 128);
    EXPECT_EQ(hamber(41), 150);
    EXPECT_EQ(hamber(44), 180);
    EXPECT_EQ(hamber(47), 216);
    EXPECT_EQ(hamber(50), 243);
    EXPECT_EQ(hamber(53), 270);
    EXPECT_EQ(hamber(56), 320);
    EXPECT_EQ(hamber(59), 375);
    EXPECT_EQ(hamber(62), 405);
}
