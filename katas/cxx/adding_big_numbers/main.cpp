// Kata: Adding Big Numbers

#include <charconv>
#include <gtest/gtest.h>
#include <string>
#include <vector>

template<typename T = int>
class BigNumber
{
    using Type = std::vector<T>;

public:
    BigNumber() = default;
    explicit BigNumber(const std::string& string)
        : digits_(extract_values(string))
    {
    }

    BigNumber operator+(const BigNumber& other) const
    {
        /*
        1. Get the bigger addend.
        2. Reverse out digits so index 0 get the less-most part of the digits.
        3. Iterate over each addend's digit:
            a. It has carry, increment 1 into output digit and disable carry.
            b. Increment output digit with our digit at current index.
            c. If index is less than other addend size, then increment that other digit into output digit.
            d. If the result is 10 or higher, then substract 10 and enable carry.
         */

        BigNumber result;
        result.digits_.reserve(std::max(size(), other.size()));

        bool carry = false;

        BigNumber copy_me(*this);
        BigNumber copy_other(other);

        copy_me.reverse_digits();
        copy_other.reverse_digits();

        const Type& addend_large = size() <= other.size() ? copy_other.digits_ : copy_me.digits_;
        const Type& addend_short = size() > other.size() ? copy_other.digits_ : copy_me.digits_;

        for (size_t i = 0; i < addend_large.size(); ++i)
        {
            T total = 0;

            if (carry)
            {
                total += 1;
                carry = false;
            }

            total += addend_large[i];
            if (i < addend_short.size())
            {
                total += addend_short[i];
            }

            if (total >= 10)
            {
                total -= 10;
                carry = true;
            }

            result.digits_.push_back(total);
        }

        if (carry)
        {
            result.digits_.push_back(1);
            carry = false;
        }

        result.reverse_digits();
        return result;
    }

    [[nodiscard]] size_t size() const
    {
        return digits_.size();
    }

    [[nodiscard]] std::string stringify() const
    {
        std::string result(digits_.size(), '\0');
        for (int i = 0; i < digits_.size(); ++i)
        {
            constexpr char zero_ascii = '0';
            result[i] = zero_ascii + digits_[i];
        }

        return result;
    }

private:
    Type extract_values(const std::string& string)
    {
        Type values(string.length());

        for (int i = 0; i < string.length(); ++i)
        {
            constexpr char zero_ascii = '0';
            values[i] = string[i] - zero_ascii;
        }

        return values;
    }

    void reverse_digits()
    {
        std::reverse(digits_.begin(), digits_.end());
    }

    Type digits_;
};



std::string add(const std::string& a, const std::string& b)
{
    const BigNumber augend(a);
    const BigNumber addend(b);

    const BigNumber result = augend + addend;
    std::cout << augend.stringify() << " + " << addend.stringify() << " = " << result.stringify() << std::endl;

    return result.stringify();
}

TEST(Codewars, adding_big_numbers)
{
    EXPECT_STREQ(add("123", "456").c_str(), "579");
    EXPECT_STREQ(add("0", "0").c_str(), "0");
    EXPECT_STREQ(add("99", "2").c_str(), "101");
    EXPECT_STREQ(add("10", "35679").c_str(), "35689");
    EXPECT_STREQ(add("", "5").c_str(), "5");
    EXPECT_STREQ(add("192", "").c_str(), "192");
    EXPECT_STREQ(add("9999", "1111").c_str(), "11110");
}
