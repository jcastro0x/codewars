#define BOOST_TEST_MODULE CreatePhoneNumber
#include <boost/test/included/unit_test.hpp>

#include <string>

std::string createPhoneNumber(std::vector<int> arr){
//std::string createPhoneNumber(const int arr [10]){

    std::string phoneNumber(14, ' ');
    phoneNumber[0] = '(';
    phoneNumber[4] = ')';
    phoneNumber[9] = '-';

    for(int i = 0; i < 4; i++) phoneNumber[i+10] = static_cast<char>('0' + arr[i+6]);
    for(int i = 0; i < 3; i++)
    {
        phoneNumber[i+1]  = static_cast<char>('0' + arr[i]);
        phoneNumber[i+6]  = static_cast<char>('0' + arr[i+3]);
    }

    return phoneNumber;
}


BOOST_AUTO_TEST_CASE(UniqueTest)
{
    BOOST_TEST(createPhoneNumber({1, 2, 3, 4, 5, 6, 7, 8, 9, 0}) == "(123) 456-7890");
    BOOST_TEST(createPhoneNumber({1, 1, 1, 1, 1, 1, 1, 1, 1, 1}) == "(111) 111-1111");
    BOOST_TEST(createPhoneNumber({1, 2, 3, 4, 5, 6, 8, 8, 0, 0}) == "(123) 456-8800");
    BOOST_TEST(createPhoneNumber({0, 2, 3, 0, 5, 6, 0, 8, 9, 0}) == "(023) 056-0890");
    BOOST_TEST(createPhoneNumber({0, 0, 0, 0, 0, 0, 0, 0, 0, 0}) == "(000) 000-0000");
}