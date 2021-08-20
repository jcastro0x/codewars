#define BOOST_TEST_MODULE ComplemetaryDNA
#include <boost/test/included/unit_test.hpp>

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

BOOST_AUTO_TEST_CASE(UniqueTest)
{
    BOOST_TEST(DNAStrand("AAAA")    =="TTTT");
    BOOST_TEST(DNAStrand("ATTGC")   =="TAACG");
    BOOST_TEST(DNAStrand("GTAT")    =="CATA");
}