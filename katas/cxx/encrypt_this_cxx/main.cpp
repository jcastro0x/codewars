#include <gtest/gtest.h>

#include <string>
#include <vector>

std::vector<std::string> get_words(const std::string& str)
{
    std::vector<std::string> words;
    std::string word;
    std::stringstream iss(str);

    while(iss >> word)
        words.emplace_back(word);

    return words;
}

std::string encrypt_this(const std::string& str)
{
    std::string encrypted_string;
    auto words = get_words(str);
    for(auto& word : words)
    {
        const int firstCharAsInt = static_cast<unsigned char>(word.front());

        word = word.substr(1, word.size() - 1);
        {
            if(!word.empty())
                std::swap(word.front(), word.back());

            word = std::to_string(firstCharAsInt) + word;
            encrypted_string += word + " ";
        }
    }

    if(!encrypted_string.empty() && std::isspace(encrypted_string.back()))
        encrypted_string = encrypted_string.substr(0, encrypted_string.size() -1);

    return encrypted_string;
}

TEST(Codewars, encrypt_this_cxx)
{
    EXPECT_STREQ(encrypt_this("").c_str(), "");
    EXPECT_STREQ(encrypt_this("A").c_str(), "65");
    EXPECT_STREQ(encrypt_this("Ab").c_str(), "65b");
    EXPECT_STREQ(encrypt_this("Abcd").c_str(), "65dcb");
    EXPECT_STREQ(encrypt_this("  Abcd   Abcd").c_str(), "65dcb 65dcb");
    EXPECT_STREQ(encrypt_this("Abcd Aahhhhhhhhhhhhhhhhz").c_str(), "65dcb 65zhhhhhhhhhhhhhhhha");
    EXPECT_STREQ(encrypt_this(" Hello world ").c_str(), "72olle 119drlo");
}
