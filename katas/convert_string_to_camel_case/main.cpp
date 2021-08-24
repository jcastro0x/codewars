#define BOOST_TEST_MODULE ConvertStringToCamelCase
#include <boost/test/included/unit_test.hpp>

#include <string>
#include <array>

// reuse string to avoid string appends
// 7.4 faster than append string approach
std::string to_camel_case(std::string text) {

    // Add any delimiter. The code will still work!
    constexpr std::array<char,2> delimiters = { '_', '-' };

    if(!text.empty()) for(int i = 1; i < text.size() - 1; i++)
    {
        if(std::any_of(delimiters.begin(), delimiters.end(), [&](const auto& d) {
            return d == text[i];
        }))
        {
            std::copy(&text[i+1], &text[text.size()], &text[i]);
            text[i] = static_cast<decltype(text)::value_type>(std::toupper(text[i]));
            text.pop_back();
        }
    }

    return text;
}

BOOST_AUTO_TEST_CASE(UniqueTest)
{
    BOOST_TEST(to_camel_case("")                    == "");
    BOOST_TEST(to_camel_case("the_stealth_warrior") == "theStealthWarrior");
    BOOST_TEST(to_camel_case("The-Stealth-Warrior") == "TheStealthWarrior");
    BOOST_TEST(to_camel_case("A-B-C")               == "ABC");
}









//#define BOOST_TEST_MODULE ConvertStringToCamelCase
//#include <boost/test/included/unit_test.hpp>
//
//#include <string>
//#include <array>
//
//void camel2(std::string& string)
//{
//    for(auto i = 1; i < string.size() - 1; i++)
//    {
//        if(string[i] == '_' || string[i] == '-')
//        {
//            std::copy(&string[i+1], &string[string.size()], &string[i]);
//            string[i] = static_cast<char>(std::toupper(string[i]));
//            string.pop_back();
//        }
//    }
//}
//
//std::string to_camel_case(const std::string& text) {
//
//    if(!text.empty())
//    {
//        std::string s = text;
//        camel2(s);
//        int i = 0;
//    }
//
//
//    constexpr std::array<char,2> delimiters = { '_', '-' };
//    auto isDelimiter = [&](char c){
//        return std::any_of(delimiters.begin(), delimiters.end(), [c](const auto& d) {
//            return d == c;
//        });
//    };
//
//    std::string output;
//    bool bCapitalizeNextCharacter = false;
//    for(const auto& c : text)
//    {
//        if(bCapitalizeNextCharacter)
//        {
//            bCapitalizeNextCharacter = false;
//            output += static_cast<char>(std::toupper(c));
//        }
//        else if(isDelimiter(c))
//        {
//            bCapitalizeNextCharacter = true;
//        }
//        else
//        {
//            output += c;
//        }
//    }
//
//    return output;
//}
//
//BOOST_AUTO_TEST_CASE(UniqueTest)
//{
//    BOOST_TEST(to_camel_case("")                    == "");
//    BOOST_TEST(to_camel_case("the_stealth_warrior") == "theStealthWarrior");
//    BOOST_TEST(to_camel_case("The-Stealth-Warrior") == "TheStealthWarrior");
//    BOOST_TEST(to_camel_case("A-B-C")               == "ABC");
//}
