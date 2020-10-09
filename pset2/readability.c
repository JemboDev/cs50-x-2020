// https://cs50.harvard.edu/x/2020/psets/2/readability/
// Readability index computation (xx.04.20)

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int readability_index(float L, float S);

int main(void)
{
    int letters, words, sentences, index;
    float L, S;

    // Getting input from user
    string text = get_string("Text: ");

    // Getting # of ... in text
    letters = count_letters(text);
    words = count_words(text);
    sentences = count_sentences(text);

    // L - average number of letters per 100 words
    L = letters * 100 / (float) words;

    // S - average number of sentences per 100 words
    S = sentences * 100 / (float) words;

    // Getting readability index for given text
    index = readability_index(L, S);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

// Returns number of letters in text
int count_letters(string text)
{
    int letters = 0;

    for (int i = 0, s = strlen(text); i < s; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    return letters;
}

// Returns number of words in text
int count_words(string text)
{
    int words = 0;

    if (text[0] == '\0')
    {
        return 0;
    }

    for (int i = 0, s = strlen(text); i < s; i++)
    {
        if (isblank(text[i]))
        {
            words++;
        }
    }
    return words + 1;
}

// Returns number of sentences in text
int count_sentences(string text)
{
    int sentences = 0;

    for (int i = 0, s = strlen(text); i < s; i++)
    {
        if (text [i] == '.' ||
            text [i] == '!' ||
            text [i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}

// Coleman-Liau readability index
int readability_index(float L, float S)
{
    return round(0.0588 * L - 0.296 * S - 15.8);
}