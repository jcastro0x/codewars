#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

char* encrypt_this(const char* str)
{
    char input_str[strlen(str)];
    strcpy(input_str, str);

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
        char word_without_head[strlen(word)-1];
        strcpy(word_without_head, &word[1]);

        // swap first and last characters
        char temp = word_without_head[0];
        word_without_head[0] = word_without_head[strlen(word_without_head)-1];
        word_without_head[strlen(word_without_head)-1] = temp;

        // concatenate int-as-string and the left of the word
        unsigned long size_encryptedWord = strlen(word_without_head) + strlen(firstCharAsIntAsString);
        char encryptedWord[size_encryptedWord];
        memset(encryptedWord, 0, size_encryptedWord);
        strcat(encryptedWord, firstCharAsIntAsString);
        strcat(encryptedWord, word_without_head);

        // concatenate to the full phrase this word and add a space
        strcat(encryptPhrase, encryptedWord);
        strcat(encryptPhrase, " ");

        // looking for more words
        word = strtok (NULL, " ");
    }

    // if last character of the full phrase it's a space, remove it
    if(isspace(encryptPhrase[strlen(encryptPhrase) -1]))
    {
        encryptPhrase[strlen(encryptPhrase) -1] = '\0';
    }

    return encryptPhrase;
}


void do_test(const char* input, const char* expected_result)
{
    char* actual = encrypt_this(input);

    if(strcmp(actual, expected_result) == 0)
    {
        fprintf(stdout, "Input: %s == %s\n", actual, expected_result);
    }
    else
    {
        fprintf(stderr, "Input: %s != %s\n", actual, expected_result);
    }

    //free(actual);
}

int main()
{
    do_test("", "");
    do_test("A", "65");
    do_test("Ab", "65b");
    do_test("Abcd", "65dcb");
    do_test("  Abcd   Abcd", "65dcb 65dcb");
    do_test("Abcd Aahhhhhhhhhhhhhhhhz", "65dcb 65zhhhhhhhhhhhhhhhha");
    do_test(" Hello world ", "72olle 119drlo");
}
