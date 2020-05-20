// Implements a dictionary's functionality

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

// Number of buckets in hash table
// 26 for 26 alphabet chars
const unsigned int N = 65536;

// Hash table
node *table[N];

// Word counter
int wordCount = 0;


/*
** Functions **
*/

// Returns true if word is in dictionary else false
// Fourth
bool check(const char *word)
{

    // Lowercase word
    char lcword[LENGTH + 1];

    // Iterate and converts array to lowercase for lookup
    // Don't forget about adding "\0" key
    int n = strlen(word);

    for (int i = 0; i < n; i++)
    {
        lcword[i] = tolower(word[i]);
    }
    lcword[n] = '\0';

    // Get hash value from hash function
    int index = hash(lcword);

    // Check at beginning of index
    if (table[index] == NULL)
    {
        return false;
    }

    // Cursor pointer to hold word and compare
    node *cursor = table[index];

    // Access linked list at the index
    // Traverse list, looking for word
    while (cursor != NULL)
    {
        // if cursor finds word, return true
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        // move cursor to next address of linked list
        else
        {
            cursor = cursor->next;
        }
    }

    return false;
}

// Hashes word to a number
// From: https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/cf9nlkn/
// Second
unsigned int hash(const char *word)
{

    unsigned int hashing = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hashing = (hashing << 2) ^ word[i];
    }
    return hashing % 65536;
}

// Loads dictionary into memory, returning true if successful else false
// First
bool load(const char *dictionary)
{

    // char buffer for word
    char buffer[LENGTH + 1];

    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Cannot read file.\n");
        return false;
    }

    //Read strings from file one at a time
    while (fscanf(file, "%s", buffer) != EOF)
    {

        // Count number of words used
        wordCount++;

        // Create a new node for each word
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            unload();
            printf("Ran out of memory.\n");
            return false;
        }

        // Copy word to node
        strcpy(new_node->word, buffer);

        // Hash word to obtain a hash value
        // Determines which array to go to
        int index = hash(new_node->word);

        // Insert node into hash table
        // Check for collision
        if (table[index] == NULL)
        {
            table[index] = new_node;
            new_node->next = NULL;
        }
        // There IS collision
        else
        {
            new_node->next = table[index];
            table[index] = new_node;
        }

    }

    // Close dictionary
    fclose(file);

    // Returns true if successful
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
// Third
unsigned int size(void)
{

    if (wordCount > 0)
    {
        return wordCount;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false
// Fifth
bool unload(void)
{

    // Two pointers, one cursor and one "releaser"
    node *cursor, *releaser;

    // Iterate over whole array
    for (int i = 0; i < N; i++)
    {
        // Have pointers at head of linked list
        cursor = table[i];

        // Keep looping until reach tail of linked list
        while (cursor != NULL)
        {
            // Move cursor to next node (to keep track)
            // Free node releaser is pointing at (previous node)
            releaser = cursor;
            cursor = cursor->next;
            free(releaser);
        }
    }

    return true;
}
