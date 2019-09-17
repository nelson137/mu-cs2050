#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int id;
    float salary;
    int age;
} Employee;


typedef struct _Node {
    Employee data;
    int size;
    struct _Node *left;
    struct _Node *right;
} Node;


Employee readRecord(FILE*);

Node* createNode(Employee);

Node* insertMinHeap(Node*, Employee);

Employee removeMin(Node*);

void findMin(Node*, Employee*);

void findMax(Node*, Employee*);

int findHeight(Node*);
