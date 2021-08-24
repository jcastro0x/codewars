#define BOOST_TEST_MODULE EncryptThis
#include <boost/test/included/unit_test.hpp>

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
    for(auto & word : words)
    {
        const int firstCharAsInt = static_cast<unsigned char>(word.front());

        word = word.substr(1, word.size() - 1);
        {
            std::swap(word.front(), word.back());

            word = std::to_string(firstCharAsInt) + word;
            encrypted_string += word + " ";
        }
    }

    if(!encrypted_string.empty() && std::isspace(encrypted_string.back()))
        encrypted_string = encrypted_string.substr(0, encrypted_string.size() -1);

    return encrypted_string;
}

BOOST_AUTO_TEST_CASE(UniqueTest)
{
    BOOST_TEST(encrypt_this("") == "");
    BOOST_TEST(encrypt_this("A") == "65");
    BOOST_TEST(encrypt_this("Ab") == "65b");
    BOOST_TEST(encrypt_this("Abcd") == "65dcb");
    BOOST_TEST(encrypt_this("  Abcd   Abcd") == "65dcb 65dcb");
    BOOST_TEST(encrypt_this("Abcd Aahhhhhhhhhhhhhhhhz") == "65dcb 65zhhhhhhhhhhhhhhhha");
    BOOST_TEST(encrypt_this(" Hello world ") == "72olle 119drlo");
}
