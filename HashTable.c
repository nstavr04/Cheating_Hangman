#include "HashTable.h"
#include "LinkedList.h"

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

    ht = malloc(sizeof(HASHTABLE));
    if(ht == NULL){
        return NULL;
    }

    ht->slot = (LIST **)malloc(size*sizeof(LIST));
    if(ht->slot == NULL){
        return NULL;
    }

    memset(ht->slot,0,size*sizeof(LIST));

    ht->size = size;

    return ht;

}

/**
 * Function that reads the data from the text file, ONLY  the first time and stores
 * them in the hash table in the appropriate slots
 */
void ReadFirst(){

}

/**
 * Function that reads the data from the array and stores them
 * in the hash table in the appropriate slots
 */
void ReadFromArray(){

}

/**
 * A function that saves the List that has the largest size into an array
 * to be used in the next hash table
 */
void saveListToArray(LIST *l){


}

/**
 * The main hash function that hashes the data into the correct Hash Table slot
 */
void hashFunction(HASHTABLE *ht,char word[],char letter){

}

/**
 * A function that deletes the previous hash table fully from memory.
 * Firstly it frees the nodes then the lists and lastly the hash table
 */
void deletePreviousHash(){

}

//Used for debugging the HashTable
//#ifdef DEBUG
int main(){



    return 0;
}
//#endif