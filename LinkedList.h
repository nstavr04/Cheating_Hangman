#ifndef HW3_LINKEDLIST_H
#define HW3_LINKEDLIST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node{
    struct node *next;
    char data[];
}NODE;

typedef struct{
    NODE *head;
    int size;
}LIST;

/**
 * Function to create an empty linked list
 * @param l list pointer
 */
void createEmptyList(LIST *l);

/**
 * Printing the list contents
 * @param l The List
 */
void printList(LIST *l);

/**
 * Function used to pass the list pointer so we can increment
 * the size as well
 * @param l the list pointer
 * @param data the data
 */
void insert_list(LIST *l,char *data);

/**
 * Inserting a new node as the start of the linked list
 * @param head_ref head
 * @param new_data the data to be added
 */
void insert(NODE** head_ref, char new_data[]);

/**
 * Deletes a note that has that key value
 * @param head_ref head
 * @param key the key value
 */
void delete(NODE **head_ref,char key[]);

#endif //HW3_LINKEDLIST_H