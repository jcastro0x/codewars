![](https://cdn.icon-icons.com/icons2/2530/PNG/512/codewars_button_icon_151901.png)

My solutions to the katas in codewars.

Each directory it's a kata. In their directories are a README with the instructions of the kata, and the URL to it.

In addition to the requisites of each kata, I trie to do a more generic code in each of them. For example, creating a
code that still works even if add more variables to them.

# Boost unit test
I use boost to create the unit tests. If you want to build the code without this, just remove the boost includes and
the BOOST_AUTO_TEST_CASE section (or use boost 😜) and create your own entry point.

```c++
// Remove this two lines
#define BOOST_TEST_MODULE EncryptThis
#include <boost/test/included/unit_test.hpp>

// And this block
BOOST_AUTO_TEST_CASE(UniqueTest)
{
    ...
    BOOST_TEST(...);
    ...
}
```