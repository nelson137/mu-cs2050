#include <stdio.h>
#include <stdlib.h>


/*************************************************
 * Employee
 ************************************************/


typedef struct {
    int ID;
    float salary;
    int age;
} Employee;


/**
 * Print the data associated with an employee.
 * @param e A pointer to an Employee.
 */
void printEmployee(Employee *e) {
    printf("id: %d   salary: $%.2f   age: %d\n", e->ID, e->salary, e->age);
}


/*************************************************
 * Core Functions
 ************************************************/


/**
 * Return an Employee pointer of the data from the next record from a file.
 * @param fp The file to read from.
 */
Employee *readRecord(FILE *fp) {
    Employee *e = malloc(sizeof(Employee));

    if (e == NULL)
        return e;

    if (fscanf(fp, "%d,%f,%d\n", &e->ID, &e->salary, &e->age) == EOF) {
        free(e);
        return NULL;
    }

    return e;
}


/**
 * Return an integer describing how to sort the given objects.
 * Return 1 if the first belongs before the second.
 * Return -1 if the first belongs after the second.
 * Return 0 if they are they same.
 */
int comparison(void *a, void *b) {
    Employee *e_a = a, *e_b = b;
    if (e_a->age > e_b->age)
        return 1;
    else if (e_a->age < e_b->age)
        return -1;
    else
        return 0;
}


/**
 * Return the index of an integer in an array.
 * If the array does not contain the query, return -1.
 */
int binarySearch(void **array, int begin, int end, void *query) {
    if (begin >= end)
        return -1;

    int mid = begin + (end-begin)/2 + 1;

    switch (comparison(array[mid], query)) {
        case 1:  return binarySearch(array, mid, end, query);
        case -1: return binarySearch(array, begin, mid, query);
        default: return mid;
    }
}


void merge(void **array, int l, int m, int r) {
    int a;  // Left index
    int b;  // Right index
    int i;  // Merged index
    int len1 = m - l + 1;
    int len2 =  r - m;

    // Copy data into temp arrays
    void *left[len1], *right[len2];
    for (a=0; a<len1; a++)
        left[a] = array[l+a];
    for (b=0; b<len2; b++)
        right[b] = array[m+1+b];

    // Merge the temp arrays
    a = 0; // Beginning of left array
    b = 0; // Beginning of right array
    i = l; // Beginning of merged array
    while (a < len1 && b < len2) {
        if (comparison(left[a], right[b]) > 0)
            array[i] = left[a++];
        else
            array[i] = right[b++];
        i++;
    }

    // Copy any remaining elements of left
    while (a < len1)
        array[i++] = left[a++];

    // Copy any remaining elements of right
    while (b < len2)
        array[i++] = right[b++];
}


void mergesort(void **array, int begin, int end) {
    if (begin >= end)
        return;
    int mid = (begin+end)/2;
    mergesort(array, begin, mid);
    mergesort(array, mid+1, end);
    merge(array, begin, mid, end);
}


void printResult(Employee** array, int index, Employee* query) {
    if (index == -1)
        printf("Age %d doesn't exist in array\n", query->age);
    else
        printf("Age %d exists in the following record: ID: %d, Salary: %.2f, Age: %d\n", query->age,array[index]->ID,array[index]->salary,array[index]->age);
}


/*************************************************
 * Main
 ************************************************/


int main(void) {
    int size, index;
    FILE *fp = fopen("employee.csv", "r"); // open file
    if (fp){
        fscanf(fp,"%d\n", &size);
    }
    else {
        printf("Cannot find the file\n"); // error checking
        return -1;
    }

    Employee** array = (Employee**)malloc(sizeof(Employee*)*size);
    if (array == NULL){ // error check for malloc
        printf("Allocating memory failed\n");
        return -1;
    }

    // read data into array
    for (int i = 0; i < size; i++){
        array[i] = readRecord(fp);
    }
    fclose(fp);

    // sort array based on employee's ages in descending order
    mergesort((void**)array,0,size-1);

    Employee query;
    // search for employee with age 20
    query.age = 20;
    index = binarySearch((void**)array, 0, size-1, &query);
    printResult(array,index,&query);

    // search for employee with age 35
    query.age = 35;
    index = binarySearch((void**)array, 0, size-1, &query);
    printResult(array,index,&query);

    // search for employee with age 5
    query.age = 5;
    index = binarySearch((void**)array, 0, size-1, &query);
    printResult(array,index,&query);

    // free all memories
    for (int i = 0; i < size; i++){
        free(array[i]);
    }
    free(array);

    return 0;
}
