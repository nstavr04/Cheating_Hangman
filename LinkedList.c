#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

typedef struct node{
    struct node *next;
    char data[];
}NODE;

typedef struct{
    NODE *head;
    int size;
}LIST;

/**
 * Printing the list contents
 * @param l The List
 */
void printList(LIST *l){
    NODE *pt = l->head;

    while(pt != NULL){
        printf("%s",pt->data);
        pt = pt->next;
    }
}

/**
 * Inserting a new node as the start of the linked list
 * @param head_ref head
 * @param new_data the data to be added
 */
void insert(NODE** head_ref, char new_data[]){
    NODE* new_node = (NODE*)malloc(sizeof(NODE));

    //New node data is equal to the new data
    strcpy(new_node->data,new_data);

    //New node next shows where current head is at
    new_node->next = (*head_ref);

    //Head points to new node now
    (*head_ref) = new_node;
}

/**
 * Deletes a note that has that key value
 * @param head_ref head
 * @param key the key value
 */
void delete(NODE **head_ref,char key[]){

    NODE *temp = *head_ref,*prev;

    //If head has the key
    if(temp != NULL && strcmp(temp->data,key) == 0){
        *head_ref = temp->next;
        free(temp);
        return;
    }

    //Searching for the key while keeping track of the previous node. (Prev->next is needed)
    while(temp != NULL && strcmp(temp->data,key) != 0){
        prev = temp;
        temp = temp->next;
    }

    //Key is not in the list
    if(temp == NULL) return;

    //The node that has the key is not unlinked from the list and we can free the memory
    prev->next = temp->next;

    free(temp);
}

int main(){

    return 0;
}

