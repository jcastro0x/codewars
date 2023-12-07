#include <unity.h>

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdint.h>

void setUp(void) {}
void tearDown(void) {}

bool IsIsogram(const char *str)
{
    char* strInput = malloc(sizeof(char) * strlen(str) + 1);
    strcpy(strInput, str);

    uint32_t flags = 0;

    int index = 0;
    while(strInput[index] != '\0')
    {
        if(isalpha(strInput[index]))
        {
            if(isupper(strInput[index])) strInput[index] = (char)tolower(strInput[index]);
            int asciiIndex = ((unsigned char)strInput[index]) - 'a';

            int mask = 1 << asciiIndex;
            if((flags & mask) > 0)
            {
                return false;
            }
            else
            {
                flags |= mask;
            }
        }

        index++;
    }

    free(strInput);
    return true;
}

void test_isograms(void)
{
    TEST_ASSERT_TRUE(IsIsogram("a_string"));
    TEST_ASSERT_TRUE(IsIsogram("Dermatoglyphics"));
    TEST_ASSERT_FALSE(IsIsogram("aba"));
    TEST_ASSERT_FALSE(IsIsogram("moOse"));
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_isograms);
    return UNITY_END();
}
