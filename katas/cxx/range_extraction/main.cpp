#include <gtest/gtest.h>

#include <string>
#include <vector>

template<typename T = int>
std::string range_extraction(const std::vector<T>& args) {

    std::string string;
    std::vector<T> range;
    bool bNextItemIsConsecutive = false;

    for(size_t i = 0; i < args.size(); i++)
    {
        // Empty current range
        range.clear();

        // Find next range length
        do
        {
            range.push_back(args[i]);
            if(i == args.size()-1) break;

            bNextItemIsConsecutive = args[i] - args[i + 1] == -1;
            if(bNextItemIsConsecutive)
            {
                ++i;
            }
        }
        while(bNextItemIsConsecutive);

        // Print range
        if(range.size() >= 3)
        {
            string.append(std::to_string(range.front()) + "-" + std::to_string(range.back()) + ",");
        }
        else
        {
            for(auto& v : range)
            {
                string.append(std::to_string(v) + ",");
            }
        }
    }

    // Instead of query at every iteration, we remove last comma here
    string.pop_back();
    return string;
}

TEST(Codewars, range_extraction)
{
    for(auto const& [vec, str] : std::map<std::vector<int>, std::string>{
//        {{-6,-3,-2,-1,0,1,3,4,5,7,8,9,10,11,14,15,17,18,19,20}, "-6,-3-1,3-5,7-11,14,15,17-20"},
//        {{-3,-2,-1,2,10,15,16,18,19,20},                        "-3--1,2,10,15,16,18-20"},
//        {{198,205,206,207,209,210},                             "198,205-207,209,210"},
        {{205,206,207,209},                                     "205-207,209"}

         //"47-51,54,55,57,58,60-65,68-70,72,73,76-79,82-85,87,89-93,95,96,99,100,102,105-108,110-112,114,116,118-121,125-128,132-150,152-155,157-159,162,163,166,168,170-190,192,193,195,196,198,200-207,209"}
    })
    {
        EXPECT_STREQ(range_extraction(vec).c_str(), str.c_str());
    }
}
