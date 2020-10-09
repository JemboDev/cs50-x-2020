// https://cs50.harvard.edu/x/2020/psets/2/caesar/
// Caesar Algorithm (10.04.20)

#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main(int argc, string argv[])
{
    // Counting Command-Line Arguments (we need exactly 1 arg)
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Validating the Key (we need only numbers)
    for (int i = 0, s = strlen(argv[1]); i < s; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Getting the key for encryption
    int key = atoi(argv[1]) % 26;

    // Getting user's input
    string plaintext = get_string("plaintext: ");

    // String encoding
    printf("ciphertext: ");
    for (int i = 0, s = strlen(plaintext); i < s; i++)
    {
        if (isalpha(plaintext[i]))
        {
            int ASCII_char = (int) plaintext[i] + key;

            if ((isupper(plaintext[i]) && ASCII_char > 90) ||
                (islower(plaintext[i]) && ASCII_char > 122))
            {
                ASCII_char -= 26;
            }
            printf("%c", (char) ASCII_char);
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}