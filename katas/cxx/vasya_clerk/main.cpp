#include <gtest/gtest.h>

#include <string>
#include <vector>
#include <algorithm>
#include <array>

// Help constexpr to yes or no values
constexpr const char* YES = "YES";
constexpr const char* NO  = "NO";

// How much cost the ticket?
constexpr int ticketCost  = 25;

using billsArray_t = std::array<int,3>;
constexpr billsArray_t billsTypes = { 25, 50, 100 };


constexpr int indexOfBill(int bill)
{
    for(size_t i = 0; i < billsTypes.size(); i++)
        if(bill == billsTypes[i]) return static_cast<int>(i);
    throw 1;
}

inline bool removeBillsFrom(int money, billsArray_t& savedBills)
{
    int index = billsTypes.size() -1;
    while(money > 0 && index >= 0)
    {
        const int billAmount = billsTypes[index];
        if(savedBills[index] > 0 && money >= billAmount)
        {
            money -= billAmount;
            --savedBills[index];
        }
        else index--;
    }

    return money == 0;
}

std::string tickets(const std::vector<int>& bills)
{
    billsArray_t savedBills { };
    for(const auto& bill : bills)
    {
        ++savedBills[indexOfBill(bill)];
        if(const int difference = bill - ticketCost; difference != 0)
        {
            if(!removeBillsFrom(difference, savedBills))
                return NO;
        }
    }

    return YES;
}



TEST(Codewars, vasya_clerk)
{
    EXPECT_STREQ(tickets({25,25,50}).c_str(),        YES);
    EXPECT_STREQ(tickets({25,25,50,100}).c_str(),    YES);
    EXPECT_STREQ(tickets({25,25,50,50}).c_str(),     YES);
    EXPECT_STREQ(tickets({25,50,25,25,100}).c_str(), YES);
    EXPECT_STREQ(tickets({25,100}).c_str(),           NO);
    EXPECT_STREQ(tickets({25,25,100}).c_str(),        NO);
    EXPECT_STREQ(tickets({50,25}).c_str(),            NO);
    EXPECT_STREQ(tickets({25,25,25,100}).c_str(),    YES);
}
