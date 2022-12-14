#include <check.h>

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdint.h>


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

START_TEST(test_money_create)
{
    ck_assert_int_eq(IsIsogram("a_string"),         1);
    ck_assert_int_eq(IsIsogram("Dermatoglyphics"),  1);
    ck_assert_int_eq(IsIsogram("aba"),              0);
    ck_assert_int_eq(IsIsogram("moOse"),            0);
}
END_TEST

int main()
{
    return 0;
}
