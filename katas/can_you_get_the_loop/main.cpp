#define BOOST_TEST_MODULE CanYouGetTheLoop
#include <boost/test/included/unit_test.hpp>

#include <vector>
struct Node
{
    void setNext(Node* n) { next = n; }
    [[nodiscard]] const Node* getNext() const  { return next; }

    private: Node* next = nullptr;
};

size_t getLoopSize(const Node* node)
{
    std::vector<const Node*> nodes;
    nodes.reserve(20);

    while(std::find(nodes.begin(), nodes.end(), node) == nodes.end())
    {
        nodes.push_back(node);
        node = node->getNext();
    }

    return nodes.size() - ( std::find(nodes.begin(), nodes.end(), nodes.back()->getNext())
                          - nodes.begin() );
}


BOOST_AUTO_TEST_CASE(UniqueTest)
{
    //case 1
    {
        Node n1, n2, n3, n4;
        n1.setNext(&n2);
        n2.setNext(&n3);
        n3.setNext(&n4);
        n4.setNext(&n2);

        int actual = getLoopSize(&n1);
        BOOST_TEST(actual == 3);
    }

    //case 2
    {
        Node n1, n2, n3, n4;
        n1.setNext(&n2);
        n2.setNext(&n3);
        n3.setNext(&n4);
        n4.setNext(&n4);

        int actual = getLoopSize(&n1);
        BOOST_TEST(actual == 1);
    }

    //case 3
    {
        Node n;
        n.setNext(&n);

        int actual = getLoopSize(&n);
        BOOST_TEST(actual == 1);
    }
}