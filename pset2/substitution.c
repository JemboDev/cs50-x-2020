// https://cs50.harvard.edu/x/2020/psets/2/substitution/
// Implements a substitution cipher (10.04.20)

#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>


int main(int argc, string argv[])
{
    string abc = "abcdefghijklmnopqrstuvwxyz";

    // Counting Command-Line Arguments (we need exactly 1 arg)
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Validating the Key (we need exactly 26 non-repeatable alphabetic characters)
    int key_len = strlen(argv[1]);

    if (key_len != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Checking for alphabetical chars and repetitions
    for (int i = 0; i < key_len; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
        for (int j = i + 1; j < key_len; j++)
        {
            if (tolower(argv[1][i]) == tolower(argv[1][j]))
            {
                printf("Key must contain non-repeatable characters.\n");
                return 1;
            }
        }
    }

    // Getting user's input
    string plaintext = get_string("plaintext: ");

    // String encoding
    printf("ciphertext: ");
    for (int i = 0, s = strlen(plaintext); i < s; i++)
    {
        char symbol = plaintext[i];
        int index;

        if (isupper(symbol))
        {
            index = strchr(abc, tolower(symbol)) - abc;
            printf("%c", toupper(argv[1][index]));
        }
        else if (islower(symbol))
        {
            index = strchr(abc, symbol) - abc;
            printf("%c", tolower(argv[1][index]));
        }
        else
        {
            printf("%c", symbol);
        }
    }
    printf("\n");
}