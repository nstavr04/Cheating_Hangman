#ifndef HW3_HASHTABLE_H
#define HW3_HASHTABLE_H
#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int size;
    LIST **slot;
}HASHTABLE;

/**
 * If we have a positive size , we allocate the memory for a new hashtable.
 * @param size The size of HashTable
 * @return a pointer to the newly allocated HashTable. If size if zero or negative
 * we return NULL
 */
HASHTABLE *createHt(int size);

/**
 * A function that takes the hash table index from the hash function and places
 * the word in the currect hash table slot
 * @param ht the hash table
 * @param index the hash table index to place the word
 * @param word the word
 */
void hashPlace(HASHTABLE *ht,int index,char word[]);

/**
 * The main hash function that hashes the data and calls the hashPlace
 * function to put the data in the correct Hash Table slot
 */
void hashFunction(HASHTABLE *ht,char word[],char userLetter);

/**
  * Function that reads the data from the text file, ONLY  the first time and stores
  * them in the hash table in the appropriate slots
  * @param arg the text file parameter
  * @param wordLength the word length
  * @param userLetter the user current letter
  */
void ReadFile(char *arg,int wordLength,char userLetter);

/**
  * Function that reads the data from the array and stores them
  * in the hash table in the appropriate slots
  * @param array the array with the words
  * @param wordLength the word length
  * @param userLetter the user current letter
  */
void ReadFromArray(char **array,int wordLength,char userLetter,int arraySize);

/**
 * A function that saves the List that has the largest size into an array
 * to be used in the next hash table
 */
char ** saveListToArray(LIST *l,int wordLength,int arraySize);

/**
 * A function that deletes the previous hash table fully from memory.
 * Firstly it frees the nodes then the lists and lastly the hash table
 */
void deletePreviousHash(HASHTABLE *ht);

#endif //HW3_HASHTABLE_H
