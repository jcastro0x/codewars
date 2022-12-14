#include <gtest/gtest.h>

#include <string>
#include <array>
#include <algorithm>

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

TEST(Codewars, convert_string_to_camel_case)
{
    EXPECT_STREQ(to_camel_case("").c_str(), "");
    EXPECT_STREQ(to_camel_case("the_stealth_warrior").c_str(), "theStealthWarrior");
    EXPECT_STREQ(to_camel_case("The-Stealth-Warrior").c_str(), "TheStealthWarrior");
    EXPECT_STREQ(to_camel_case("A-B-C").c_str(), "ABC");
}
