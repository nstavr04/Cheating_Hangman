#ifndef HW3_HASHTABLE_H
#define HW3_HASHTABLE_H
#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<assert.h>
#include <math.h>

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
 *
 * @param ht the hash table
 * @param word the current word
 * @param userLetter the current guess letter
 */
void hashFunction(HASHTABLE *ht,char word[],char userLetter);

/**
  * Function that reads the data from the text file, ONLY  the first time and stores
  * them in the hash table in the appropriate slots
  * @param arg the text file parameter
  * @param wordLength the word length
  * @param userLetter the user current letter
  */
HASHTABLE * ReadFile(char *arg,int wordLength,char userLetter);

/**
 * Function that reads the data from the array and stores them
 * in the hash table in the appropriate slots
 * @param array the array with the words
 * @param wordLength the word length
 * @param userLetter the user current letter
 * @param arraySize the array size which is equal to the max list size
 * @return a pointer to the filled hash table
 */
HASHTABLE *ReadFromArray(char **array,int wordLength,char userLetter,int arraySize);

/**
 * A function that finds the max list size from the hash table and also returns the list
 *
 * @param ht  the hash table
 * @param wordLength the size of the largest list
 * @param maxListSize the size of the largest list
 * @return a pointer to the largest list in the hash table
 */
LIST *findMaxList(HASHTABLE *ht,int wordLength,int *maxListSize);

/**
 * A function that saves the List that has the largest size into an array
 * to be used in the next hash table
 *
 * @param l a pointer to the largest list
 * @param arraySize the array size
 * @return a double pointer to a char array that includes the list elements
 */
char ** saveListToArray(LIST *l,int arraySize);

/**
 * A function that deletes the previous hash table fully from memory.
 * Firstly it frees the nodes then the lists and lastly the hash table
 * @param ht the filled hash table to be deleted
 */
void deletePreviousHash(HASHTABLE *ht);

#endif //HW3_HASHTABLE_H
