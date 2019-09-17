#ifndef LAB13_H
#define LAB13_H


#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int id;
    float salary;
    int age;
} Employee;


typedef struct _node {
    int data;             // Node's data
    int size;             // The number of nodes in the sub-heap
    struct _node *left;   // Left sub-heap
    struct _node *right;  // Right sub-heap
} Node;


/**
 * Return an integer describing how to sort the given objects.
 * Return 1 if the first belongs before the second.
 * Return -1 if the first belongs after the second.
 * Return 0 if they are they same.
 */
int comparison(void *v_a, void *v_b);


/**
 * Return a new node with the given data.
 * Memory is allocated with malloc.
 * @param data The data to fill the node with.
 */
Node *createNode(int data);


/**
 * Insert a value into a binary search pq.
 * Nodes are created with createNode().
 * @param pq The binary search pq to insert into.
 * @param data The data to insert.
 */
Node *insertPQ(Node *pq, int data);


int deletemin(Node *pq);


/**
 * Free all memory allocated for a binary search pq.
 * @param pq The binary search pq to free.
 */
void deletePQ(Node *pq);


#endif
