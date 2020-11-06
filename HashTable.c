#include "HashTable.h"
#include "LinkedList.h"
#include<assert.h>
#include <math.h>

/**
 * If we have a positive size , we allocate the memory for a new hashtable.
 * @param size The size of HashTable
 * @return a pointer to the newly allocated HashTable. If size if zero or negative
 * we return NULL
 */
HASHTABLE *createHt(int size){

    HASHTABLE *ht;

    if(size < 1){
        return NULL;
    }

    //Allocating memory for the hash table
    ht = malloc(sizeof(HASHTABLE));
    if(ht == NULL){
        return NULL;
    }

    //Allocating memory for the list pointers
    ht->slot = (LIST **)malloc(size*sizeof(LIST *));
    if(ht->slot == NULL){
        return NULL;
    }

    //Allocating memory for lists
    for(int i=0;i<size;i++){
        ht->slot[i] = malloc(sizeof(*ht->slot[i]));
    }

    memset(ht->slot,0,size*sizeof(LIST *));

    ht->size = size;

    return ht;

}

/**
 * A function that takes the hash table index from the hash function and places
 * the word in the currect hash table slot
 * @param ht the hash table
 * @param index the hash table index to place the word
 * @param word the word
 */
void hashPlace(HASHTABLE *ht,int index,char word[]){

    //Find the correct list in the hash table
    LIST *l = ht->slot[index];

    //Insert the word in the correct list
    insert(&l->head, word);

}

 /**
  * The main hash function that hashes the data and calls the hashPlace
  * function to put the data in the correct Hash Table slot
  *
  * @param ht the hash table
  * @param word the current word
  * @param userLetter the current guess letter
  */
void hashFunction(HASHTABLE *ht,char word[],char userLetter){

    //We are hashing the word based on the user letter with a unique ID
    //If word is good and letter is o the hash id will be 6
    // 0000 , 0001 , 0010 , 0011 , 0100 , 0101 , 0110

    unsigned id = 0U;

    for (unsigned i = 0; i < strlen(word); ++i) {
        if (word[i] == userLetter) {
            id |= 1U << i;
        }
    }

    hashPlace(ht,id,word);
}

/**
  * Function that reads the data from the text file, ONLY  the first time and stores
  * them in the hash table in the appropriate slots
  * @param arg the text file parameter
  * @param wordLength the word length
  * @param userLetter the user current letter
  * @return a pointer to the filled hash table
  */
HASHTABLE *ReadFile(char *arg,int wordLength,char userLetter){

    //Creating the hash table
     HASHTABLE *ht = createHt(pow(2,wordLength));

     //Read the dna text file
     FILE *fp = NULL;
     fp = fopen(arg,"r");

     if(fp == NULL){
         printf("Unable to open");
         exit(-1);
     }

     char word[wordLength];

     //Just overwriting the wordLength so we read it from the file
     fscanf(fp,"%d",&wordLength);

     //While i have more lines to read
     while(fscanf(fp,"%s",word) == 1){

         //Every time i read a word i call hashFunction
         hashFunction(ht,word,userLetter);

     }

     return ht;

}

 /**
  * Function that reads the data from the array and stores them
  * in the hash table in the appropriate slots
  * @param array the array with the words
  * @param wordLength the word length
  * @param userLetter the user current letter
  * @param arraySize the array size which is equal to the max list size
  * @return a pointer to the filled hash table
  */
HASHTABLE *ReadFromArray(char **array,int wordLength,char userLetter,int arraySize){

    //Creatomg the hash table
    HASHTABLE *ht = createHt(pow(2,wordLength));

    //For every word call the hashFunction
    for(int i=0;i<arraySize;i++){

        hashFunction(ht,array[i],userLetter);

    }

    return ht;
}

/**
 * A function that finds the max list size from the hash table and also returns the list
 *
 * @param ht  the hash table
 * @param wordLength the size of the largest list
 * @param maxListSize the size of the largest list
 * @param guessedLetter the guess letter
 * @return a pointer to the largest list in the hash table
 */
LIST *findMaxList(HASHTABLE *ht,int wordLength,int *maxListSize,int *guessedLetter){

    int max = 0;

    HASHTABLE *p = ht;

    //Point the list on the 1st list
    LIST *l = p->slot[0];

    //Iterates through the hash table
    for(int i=0;i<pow(2,wordLength);i++){

        //Checks if the size of the list is the largest
        if(p->slot[i]->size >= max){
            //Change the max size of list
            max = p->slot[i]->size;
            //Point l to that list
            l = p->slot[i];
        }

        //Move to the next hash table slot
        (p->slot)++;

    }

    //If the list is the first letter, it means the user didnt guess a letter
    if(l == ht->slot[0]){
        *guessedLetter = 0;
    }
    //Else it guessed the letter correctly
    else{
        *guessedLetter = 1;
    }

    //Change the max size to return it to the main
    *maxListSize = max;

    return l;

}

/**
 * A function that saves the List that has the largest size into an array
 * to be used in the next hash table
 *
 * @param l a pointer to the largest list
 * @param arraySize the array size
 * @return a double pointer to a char array that includes the list elements
 */
char ** saveListToArray(LIST *l,int arraySize){

    //Create a pointer to go through the list
    NODE *pt = l->head;

    //Save the arraySize to use in ReadFromArray function
    arraySize = l->size;

    //Create an array to store all the words in
    char **array = calloc(l->size,sizeof(*array));

        //Go through the list and copy every element from list to the array
        for(int i=0;i<arraySize;i++){
            //Allocate the memory and return the pointer to that memory
            array[i] = strdup(pt->data);
            //Making sure the memory allocation happened and its not NULL
            assert(array[i]);
            pt = pt->next;
        }

        return array;
}

/**
 * A function that deletes the previous hash table fully from memory.
 * Firstly it frees the nodes then the lists and lastly the hash table
 * @param ht the filled hash table to be deleted
 */
void deletePreviousHash(HASHTABLE *ht){

    //For every hash slot, take the list pointer
    for(int i=0;i<ht->size-1;i++){

        LIST *l = ht->slot[i];

        //For every list go through all nodes
        NODE *n = l->head;
        for(int j=0;j<l->size;j++){

            //Free current node
            NODE *temp = n;
            free(temp);

            //Move to the next node
            n = n->next;
        }

        //Free current list
        LIST *ltemp = l;
        free(ltemp);

    }

    //Free the hash table
    free(ht);

}

//Used for debugging the HashTable
//#ifdef DEBUG
//int main(){
//
//
//
//    return 0;
//}
//#endif