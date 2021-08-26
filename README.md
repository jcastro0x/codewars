![](https://cdn.icon-icons.com/icons2/2530/PNG/512/codewars_button_icon_151901.png)

My solutions to the katas in codewars.

Each directory it's a kata. In their directories are a README with the instructions of the kata, and the URL to it.

In addition to the requisites of each kata, I trie to do a more generic code in each of them. For example, creating a
code that still works even if add more variables to them.

![](https://www.codewars.com/users/jcastro0x/badges/large)


# C++ tests
I use boost to create the unit tests. If you want to build the code without this, just remove the boost includes and
the BOOST_AUTO_TEST_CASE section (or use boost 😜) and create your own entry point.

```c++
// Remove this two lines
#define BOOST_TEST_MODULE EncryptThis
#include <boost/test/included/unit_test.hpp>

...

// And this block
BOOST_AUTO_TEST_CASE(UniqueTest)
{
    ...
}
```

# C tests
Katas writen in C hasn't any test library, so I created a custom main and do_test functions to check tests, so not any
action is required to build this, it's only ANSI C code that would compile with any C11 compiler.

```c
void do_test(...)
{
    ... actual = function(...);
    
    if(actual == expected_result)
    {
        fprintf(stdout, "Input: %s == %d\n", input, expected_result);
    }
    else
    {
        fprintf(stderr, "Input: %s != %d\n", input, expected_result);
    }
}

int main()
{
    do_test(...);
}
```
