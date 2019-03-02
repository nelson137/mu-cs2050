#include <stdio.h>
#include <stdlib.h>

#include "mylib.h"


/*************************************************
 * List Node
 ************************************************/


typedef struct _list {
    int value;
    int is_dummy;
    struct _list *next;
} List;


/**
 * Return a new node.
 * Memory is allocated with malloc.
 */
List *createNode(int value) {
    List *newNode = malloc(sizeof(List));
    if (newNode)
        newNode->is_dummy = 0;
    return newNode;
}


/*************************************************
 * Linked List
 ************************************************/


/**
 * Initialize a linked list.
 */
int initIntegerList(List **head) {
    List* dummyTail = createNode(0);
    if (dummyTail == NULL)
        return -1;
    dummyTail->is_dummy = 1;
    dummyTail->next = NULL;

    List *dummyHead = createNode(0);
    if (dummyHead == NULL)
        return -1;
    dummyHead->is_dummy = 1;
    dummyHead->next = dummyTail;

    *head = dummyHead;
    return 0;
}


/**
 * Prepend a new node to the linked list with the given data.
 */
int insertInteger(int value, List *head) {
    List *newNode = createNode(value);
    if (newNode == NULL)
        return -1;

    newNode->value = value;
    newNode->next = head->next;
    head->next = newNode;

    return 0;
}


/**
 * Print each element of the linked list on its own line to stdout.
 */
void printList(List *head) {
    for (List *p=head; p; p=p->next)
        if (!p->is_dummy)
            printf("%d\n", p->value);
}


/**
 * Frees all memory allocated for the linked list.
 */
void freeList(List *head) {
    List *curr, *next;
    for (curr=head; curr; curr=next) {
        next = curr->next;
        free(curr);
        curr = NULL;
    }
}


/*************************************************
 * Main
 ************************************************/


int main(void) {
    List *head;
    if (initIntegerList(&head) < 0)
        return 1;

    printf("%d\n", ((List*)(head->next))->value);

    freeList(head);
    return 0;
}
