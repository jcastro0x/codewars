#include <check.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

char* encrypt_this(const char* str)
{
    char* input_str = malloc(sizeof(char) * strlen(str));
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
        char* word_without_head = malloc(sizeof(char) * strlen(word)-1);
        strcpy(word_without_head, &word[1]);

        // swap first and last characters
        char temp = word_without_head[0];
        word_without_head[0] = word_without_head[strlen(word_without_head)-1];
        word_without_head[strlen(word_without_head)-1] = temp;

        // concatenate int-as-string and the left of the word
        unsigned long size_encryptedWord = strlen(word_without_head) + strlen(firstCharAsIntAsString);
        char* encryptedWord = malloc(sizeof(char) * size_encryptedWord);
        memset(encryptedWord, 0, size_encryptedWord);
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


START_TEST(test_money_create)
{
     ck_assert_str_eq(encrypt_this(""), "");
     ck_assert_str_eq(encrypt_this("A"), "65");
     ck_assert_str_eq(encrypt_this("Ab"), "65b");
     ck_assert_str_eq(encrypt_this("Abcd"), "65dcb");
     ck_assert_str_eq(encrypt_this("  Abcd   Abcd"), "65dcb 65dcb");
     ck_assert_str_eq(encrypt_this("Abcd Aahhhhhhhhhhhhhhhhz"), "65dcb 65zhhhhhhhhhhhhhhhha");
     ck_assert_str_eq(encrypt_this(" Hello world "), "72olle 119drlo");
}

int main()
{
    return 0;
}
