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

void do_test(const char* input, bool expected_result)
{
    bool actual = IsIsogram(input);

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
    do_test("a_string", true);
    do_test("Dermatoglyphics", true);
    do_test("aba", false);
    do_test("moOse", false);
}
