#include <gtest/gtest.h>

#include <string>
#include <vector>


template <typename T>
std::vector<T> uniqueInOrder(const std::vector<T>& iterable){

    std::vector<T> values;
    values.reserve(iterable.size());    // I prefer more memory allocated
                                        // than geometric reserved

    T lastValue = { };
    for(const auto& e : iterable)
    {
        if(values.size() > 0 && e == lastValue) continue;
        lastValue = e;

        values.emplace_back(lastValue);
    }

    return values;

    // Clever solution
    //std::vector<T> values;
    //values.reserve(iterable.size());
    //std::unique_copy(iterable.begin(), iterable.end(), std::back_inserter(values));
    //return values;
}

std::vector<char> uniqueInOrder(const std::string& iterable){

    std::vector<char> chars;
    std::copy(iterable.begin(), iterable.end(), std::back_inserter(chars));
    return uniqueInOrder<char>(chars);

    // Clever solution
    // return uniqueInOrder<char>(std::vector<char>(iterable.begin(), iterable.end()));
}


TEST(Codewars, unique_in_order)
{
    using VI = std::vector<int>;
    using VC = std::vector<char>;

    EXPECT_EQ(uniqueInOrder(""), (VC{}));
    EXPECT_EQ(uniqueInOrder("AA"), (VC{'A'}));
    EXPECT_EQ(uniqueInOrder("A"), (VC{'A'}));
    EXPECT_EQ(uniqueInOrder("AAAABBBCCDAABBB"), (VC{'A', 'B', 'C', 'D', 'A', 'B'}));
    EXPECT_EQ(uniqueInOrder("AADD"), (VC{'A', 'D'}));
    EXPECT_EQ(uniqueInOrder("AAD"), (VC{'A', 'D'}));
    EXPECT_EQ(uniqueInOrder("ADD"), (VC{'A', 'D'}));
    EXPECT_EQ(uniqueInOrder("ABBCcAD"), (VC{'A', 'B', 'C', 'c', 'A', 'D'}));
    EXPECT_EQ(uniqueInOrder(VI{1,2,3,3}), (VI{1,2,3}));
    EXPECT_EQ(uniqueInOrder(VI{0,0,1,2,3,3}), (VI{0, 1,2,3}));
    EXPECT_EQ(uniqueInOrder(VC{'a','b','b'}), (VC{'a','b'}));
}
