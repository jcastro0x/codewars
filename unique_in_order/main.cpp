#define BOOST_TEST_MODULE UniqueInOrder
#include <boost/test/included/unit_test.hpp>

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


BOOST_AUTO_TEST_CASE(UniqueTest)
{
    using VI = std::vector<int>;
    using VC = std::vector<char>;

    BOOST_TEST(uniqueInOrder("")==(VC{}));
    BOOST_TEST(uniqueInOrder("AA")==(VC{'A'}));
    BOOST_TEST(uniqueInOrder("A")==(VC{'A'}));
    BOOST_TEST(uniqueInOrder("AAAABBBCCDAABBB")==(VC{'A', 'B', 'C', 'D', 'A', 'B'}));
    BOOST_TEST(uniqueInOrder("AADD")==(VC{'A', 'D'}));
    BOOST_TEST(uniqueInOrder("AAD")==(VC{'A', 'D'}));
    BOOST_TEST(uniqueInOrder("ADD")==(VC{'A', 'D'}));
    BOOST_TEST(uniqueInOrder("ABBCcAD")==(VC{'A', 'B', 'C', 'c', 'A', 'D'}));
    BOOST_TEST(uniqueInOrder(VI{1,2,3,3})==(VI{1,2,3}));
    BOOST_TEST(uniqueInOrder(VI{0,0,1,2,3,3})==(VI{0, 1,2,3}));
    BOOST_TEST(uniqueInOrder(VC{'a','b','b'})==(VC{'a','b'}));
}