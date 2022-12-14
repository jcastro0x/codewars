#include <gtest/gtest.h>

#include <string>
#include <unordered_map>

std::string DNAStrand(const std::string& dna)
{
    const std::unordered_map<char,char> complements = {
        { 'A', 'T' } ,
        { 'G', 'C' } ,
    };

    std::string string = dna;
    for(auto& c : string)
    {
        for(auto&[first,second] : complements)
        {
            if(first == c)       c = second;
            else if(second == c) c = first;
        }
    }

    return string;
}

TEST(Codewars, complementary_dna)
{
    EXPECT_STREQ(DNAStrand("AAAA").c_str(),  "TTTT");
    EXPECT_STREQ(DNAStrand("ATTGC").c_str(), "TAACG");
    EXPECT_STREQ(DNAStrand("GTAT").c_str(),  "CATA");
}
