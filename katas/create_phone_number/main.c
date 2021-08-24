#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* createPhoneNumber(const int arr [10]){
    
    char* number = malloc(sizeof(char) * 15);
    sprintf(number, "(%d%d%d) %d%d%d-%d%d%d%d"
    , arr[0], arr[1], arr[2]
    , arr[3], arr[4], arr[5]
    , arr[6], arr[7], arr[8], arr[9]);
    
    return number;
}


void do_test(const int input[10], const char* expected_result)
{
    char* actual = createPhoneNumber(input);

    if(strcmp(actual, expected_result) == 0)
    {
        fprintf(stdout, "Input: %s == %s\n", actual, expected_result);
    }
    else
    {
        fprintf(stderr, "Input: %s != %s\n", actual, expected_result);
    }

    free(actual);
}

int main()
{
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    do_test(arr, "(123) 456-7890");
}
