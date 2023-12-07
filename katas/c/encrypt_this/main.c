#include <unity.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

void setUp(void) {}
void tearDown(void) {}

char* encrypt_this(const char* str)
{
    char* input_str = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(input_str, str);

    if(strlen(input_str) == 0) return input_str;

    char* encryptPhrase = malloc(sizeof(char) * 256);
    memset(encryptPhrase, 0, sizeof(char) * 256);

    char* word = strtok(input_str, " ");
    while(word != NULL)
    {
        // save first character as int
        const int firstCharAsInt = (unsigned char)word[0];

        // create string version of that int
        char firstCharAsIntAsString[4];
        sprintf(firstCharAsIntAsString, "%d", firstCharAsInt);

        // save word without first character
        char* word_without_head = malloc(sizeof(char) * strlen(word));
        strcpy(word_without_head, &word[1]);

        // swap first and last characters
        if(strlen(word_without_head) > 1)
        {
            char temp = word_without_head[0];
            word_without_head[0] = word_without_head[strlen(word_without_head)-1];
            word_without_head[strlen(word_without_head)-1] = temp;
        }

        // concatenate int-as-string and the left of the word
        unsigned long size_encryptedWord = strlen(word_without_head) + strlen(firstCharAsIntAsString);
        char* encryptedWord = malloc(sizeof(char) * (size_encryptedWord + 1));
        memset(encryptedWord, 0, size_encryptedWord + 1);
        strcat(encryptedWord, firstCharAsIntAsString);
        strcat(encryptedWord, word_without_head);

        // concatenate to the full phrase this word and add a space
        strcat(encryptPhrase, encryptedWord);
        strcat(encryptPhrase, " ");

        //free(encryptedWord);
        //free(word_without_head);

        // looking for more words
        word = strtok (NULL, " ");
    }

    // if last character of the full phrase it's a space, remove it
    if(isspace(encryptPhrase[strlen(encryptPhrase) -1]))
    {
        encryptPhrase[strlen(encryptPhrase) -1] = '\0';
    }

    //free(input_str);
    return encryptPhrase;
}


void test_encrypt_this(void)
{
     TEST_ASSERT_EQUAL_STRING("", encrypt_this(""));
     TEST_ASSERT_EQUAL_STRING("65", encrypt_this("A"));
     TEST_ASSERT_EQUAL_STRING("65b", encrypt_this("Ab"));
     TEST_ASSERT_EQUAL_STRING("65dcb", encrypt_this("Abcd"));
     TEST_ASSERT_EQUAL_STRING("65dcb 65dcb", encrypt_this("  Abcd   Abcd"));
     TEST_ASSERT_EQUAL_STRING("65dcb 65zhhhhhhhhhhhhhhhha", encrypt_this("Abcd Aahhhhhhhhhhhhhhhhz"));
     TEST_ASSERT_EQUAL_STRING("72olle 119drlo", encrypt_this(" Hello world "));
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_encrypt_this);
    return UNITY_END();
}
