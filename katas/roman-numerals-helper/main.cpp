#define BOOST_TEST_MODULE RomanNumeralsHelper
#define NOMINMAX
#include <boost/test/included/unit_test.hpp>

#include <string>
#include <array>
#include <cstdint>
#include <limits>

/*

 REGLA 1º:
 Si se escribe una cifra igual o menor a la derecha de la otra, estas se suman

 REGLA 2º:
 Si se escribe a la izquierda una cifra menor (pero no igual) entonces resta

 REGLA 3º:
 La 1º y 2º regla no se pueden usar si existe un digito para el resultado que generaria

 REGLA 4º:
 No se puede repetir mas de 3 veces el mismo simbolo

*/

class RomanHelper{
    typedef unsigned RomanNumberSize_t;

public:
    static std::string to_roman(RomanNumberSize_t n);
    static RomanNumberSize_t from_roman(std::string_view rn);

private:
    inline static constexpr std::array<RomanNumberSize_t,7>  decimals  = {  1,   5,  10,  50,  100, 500, 1000 };
    inline static constexpr std::array<char,7>               letters   = { 'I', 'V', 'X', 'L', 'C', 'D',  'M' };

} RomanNumerals;




std::string RomanHelper::to_roman(RomanNumberSize_t number) {

    std::string roman;

    int decimalIndex         = decimals.size() - 1;
    int previousDecimalIndex = decimalIndex - 2;
    while(number > 0)
    {
        for(; decimalIndex > 0; decimalIndex--, previousDecimalIndex = std::max<int>(0,--previousDecimalIndex))
        {
            if(decimals[decimalIndex] <= number) break;
            else if(decimals[decimalIndex] - decimals[previousDecimalIndex] <= number)
            {
                roman.push_back(letters[previousDecimalIndex]);
                number += decimals[previousDecimalIndex];
                break;
            }
        }

        number -= decimals[decimalIndex];
        roman.push_back(letters[decimalIndex]);
    }

    return roman;
}

RomanHelper::RomanNumberSize_t RomanHelper::from_roman(std::string_view rn) {

    RomanNumberSize_t total = 0;
    RomanNumberSize_t lastDecimalValue = std::numeric_limits<RomanNumberSize_t>::max();

    size_t decimalValue = 0;
    for(const auto& c : rn)
    {
        decimalValue
        = decimals[static_cast<size_t>(std::distance(letters.begin(), std::find(letters.begin(), letters.end(), c)))];

        if(decimalValue <= lastDecimalValue) total += decimalValue;
        else                                 total += decimalValue - lastDecimalValue - 1;

        lastDecimalValue = decimalValue;
    }

    return total;
}




BOOST_AUTO_TEST_CASE(UniqueTest)
{
    BOOST_TEST(RomanNumerals.to_roman(1000)         == "M");
    BOOST_TEST(RomanNumerals.to_roman(4)            == "IV");
    BOOST_TEST(RomanNumerals.to_roman(1)            == "I");
    BOOST_TEST(RomanNumerals.to_roman(9)            == "IX");
    BOOST_TEST(RomanNumerals.to_roman(1990)         == "MCMXC");
    BOOST_TEST(RomanNumerals.to_roman(2008)         == "MMVIII");
    BOOST_TEST(RomanNumerals.to_roman(3999)         == "MMMCMXCIX");
    BOOST_TEST(RomanNumerals.to_roman(21)           == "XXI");
    BOOST_TEST(RomanNumerals.to_roman(2004)         == "MMIV");

    BOOST_TEST(RomanNumerals.from_roman("XXI")      == 21);
    BOOST_TEST(RomanNumerals.from_roman("I")        == 1);
    BOOST_TEST(RomanNumerals.from_roman("IX")       == 9);
    BOOST_TEST(RomanNumerals.from_roman("XI")       == 11);
    BOOST_TEST(RomanNumerals.from_roman("VIII")     == 8);
    BOOST_TEST(RomanNumerals.from_roman("IV")       == 4);
    BOOST_TEST(RomanNumerals.from_roman("MMVIII")   == 2008);
    BOOST_TEST(RomanNumerals.from_roman("MDCLXVI")  == 1666);

    BOOST_TEST(RomanNumerals.from_roman("MMIV")   == 2004);
    BOOST_TEST(RomanNumerals.from_roman("MMIX")   == 2009);
    BOOST_TEST(RomanNumerals.from_roman("MMXXI")   == 2021);
}
