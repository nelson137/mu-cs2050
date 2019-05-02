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
    void *data;           // Node's data
    struct _node *left;   // Left sub-tree
    struct _node *right;  // Right sub-tree
} Node;


/**
 * Return an Employee pointer of the data from the next record from a file.
 * @param fp The file to read from.
 */
Employee *readRecord(FILE *fp);


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
Node *createNode(void *data);


/**
 * Insert a value into a binary search tree.
 * Nodes are created with createNode().
 * @param tree The binary search tree to insert into.
 * @param data The data to insert.
 */
Node *insertBST(Node *tree, void *data);


/**
 * Print all employees' salaries in a binary search tree in ascending order.
 * @param tree The binary search tree to print.
 */
void inOrderPrintSalary(Node *tree);


/**
 * Free all memory allocated for a binary search tree.
 * @param tree The binary search tree to free.
 */
void deleteTree(Node *tree);


#endif
