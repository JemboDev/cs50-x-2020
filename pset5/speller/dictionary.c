// https://cs50.harvard.edu/x/2020/psets/5/speller/
// Implements a dictionary's functionality (23.05.20)

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table (20% of the whole dict)
const unsigned long N = 28618;

// Hash table
node *table[N];

// Number of words loaded
unsigned int word_count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int hash_value = hash(lower(word));
    node *cursor = table[hash_value];

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // DJB2 from hea http://www.cse.yorku.ca/~oz/hash.html
    unsigned long hash = 5381;
    int c;

    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // word[] is placeholder for string from file
    char word[LENGTH + 1];
    unsigned int hash_value;

    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Reading strings from a file one by one
    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        hash_value = hash(word);

        // Inserting new node at the beginning
        strcpy(n->word, word);
        n->next = table[hash_value];
        table[hash_value] = n;

        word_count++;
    }

    // Close dictionary
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            destroy(table[i]);
        }
    }

    return true;
}

// Recursively frees all the nodes
void destroy(node *list)
{
    if (list == NULL)
    {
        return;
    }
    destroy(list->next);
    free(list);
}

// Converts a string tolower()
const char *lower(const char *string)
{
    static char word_to_lower[LENGTH + 1];

    for (int i = 0; i < LENGTH + 1; i++)
    {
        if (string[i] == '\0')
        {
            word_to_lower[i] = '\0';
            break;
        }
        else if (isalpha(string[i]))
        {
            word_to_lower[i] = tolower(string[i]);
        }
        else
        {
            word_to_lower[i] = string[i];
        }
    }

    return word_to_lower;
}