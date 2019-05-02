#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>


#define DATA_FILE  "employee.csv"
#define RESET      "\33[0m"
#define RED        "\33[91m"
#define W_RED(x)   RED x RESET


/*************************************************
 * Utility Funtions
 ************************************************/


/**
 * Print an error message to stderr then exit with status 1.
 * Is a wrapper for printf.
 */
void error(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, W_RED("Error: "));
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(1);
}


/**
 * Return whether a file exists.
 * @param fn The name of the file.
 */
int file_exists(char *fn) {
    struct stat s;
    return stat(fn, &s) == 0;
}


int randint(int min, int max) {
    return min + rand()%(max-min+1);
}


/*************************************************
 * Employee
 ************************************************/


typedef struct {
    int id;
    float salary;
    int age;
} Employee;


/**
 * Print the data associated with an employee.
 * @param e A pointer to an Employee.
 */
void printEmployee(Employee *e) {
    printf("id: %d   salary: $%.2f   age: %d\n", e->id, e->salary, e->age);
}


/*************************************************
 * Employee Array
 ************************************************/


/**
 * Return the next available index in an Employee array.
 * @param arr The array to use.
 */
int arrayTailIndex(Employee **arr) {
    return *( (int*)arr - 1);
}


/**
 * Free the memory allocated for an Employee array and all of its Employees.
 * @param arr The array to use.
 */
void freeArray(Employee **arr) {
    for (int i=0; i<arrayTailIndex(arr)-1; i++)
        free(arr[i]);
    free((int*)arr - 2);
    *arr = NULL;
}


/**
 * Return the maximum length of an Employee array.
 * @param arr The array to use.
 */
int arrayLen(Employee **arr) {
    return *( (int*)arr - 2 );
}


/**
 * Increment the next available index in an Employee array.
 * @param arr The array to use.
 */
int arrayIncTailIndex(Employee **arr) {
    return *( (int*)arr - 1) += 1;
}


/**
 * Append an Employee to an Employee array.
 * @param e The Employee to append.
 * @param arr The array to use.
 */
int addNewEmployee(Employee *e, Employee **arr) {
    int tailIndex = arrayTailIndex(arr);
    if (tailIndex < arrayLen(arr)) {
        arr[tailIndex] = e;
        arrayIncTailIndex(arr);
        return 0;
    } else {
        return -1;
    }
}


/**
 * Return an Employee pointer array filled with the data from a file.
 * @param fn The name of the file to use.
 */
Employee **createArray() {
    char *fn = DATA_FILE;

    if (!file_exists(fn))
        error("File does not exist: %s\n", fn);

    FILE *fp = fopen(fn, "r");
    if (fp == NULL)
        error("Could not open file: %s\n", fn);

    int nlines;
    if (fscanf(fp, "%d\n", &nlines) == EOF)
        // File is empty
        error("File contains no records: %s\n", fn);

    int *i_arr = malloc(2*sizeof(int) + nlines * sizeof(Employee*));
    if (i_arr == NULL)
        return NULL;
    *(i_arr++) = nlines;
    *(i_arr++) = 0;
    Employee **arr = (Employee**) i_arr;

    // Read data from the file into arr
    for (int i=0; i<nlines; i++) {
        Employee *e = malloc(sizeof(Employee));
        if (e == NULL) {
            perror("malloc");
            freeArray(arr);
            exit(1);
        }
        if (fscanf(fp, "%d,%f,%d\n", &e->id, &e->salary, &e->age) == EOF)
            break;
        if (addNewEmployee(e, arr) < 0) {
            // Should never happen
            freeArray(arr);
            error("Attempting to append Employee to full array\n");
        }
    }

    // EOF was reached before nlines of data were read
    if (arrayTailIndex(arr) <= nlines-1) {
        freeArray(arr);
        error("Too few records in file: %s\n", fn);
    }

    // File contains data after the nlines+1'th line
    if (!feof(fp)) {
        freeArray(arr);
        error("Too many records in file: %s\n", fn);
    }

    return arr;
}


/*************************************************
 * Core Functions
 ************************************************/


/**
 * Return the index of an integer in an array.
 * If the array does not contain the query, return -1.
 * @param query The integer to search for.
 * @param array The array to search.
 * @param begin The start index for the search.
 * @param end The end index for the search.
 */
int binary_search_age(Employee **array, int begin, int end, int query) {
    if (begin >= end)
        return -1;

    int mid = begin + (end-begin)/2 + 1;

    if (query < array[mid]->age)
        return binary_search_age(array, mid, end, query);
    else if (query > array[mid]->age)
        return binary_search_age(array, begin, mid, query);
    else
        return mid;
}


/**
 * Return the index of an integer in an array.
 * If the array does not contain the query, return -1.
 * @param query The integer to search for.
 * @param array The array to search.
 * @param begin The start index for the search.
 * @param end The end index for the search.
 */
int iterative_search(int query, int array[], int begin, int end) {
    for (int i=begin; i<end; i++)
        if (array[i] == query)
            return i;
    return -1;
}


/*************************************************
 * Main
 ************************************************/


int main(void) {
    Employee **arr = createArray();
    if (arr == NULL) {
        perror("malloc");
        return 1;
    }

    int index, ages[] = {32, 19, 5};
    for (int i=0; i<3; i++) {
        index = binary_search_age(arr, 0, arrayLen(arr)-1, ages[i]);
        if (index < 0)
            printf("Could not find any employee with age %d\n", ages[i]);
        else
            printf("Found employee with age %d and id %d\n",
                   ages[i], arr[index]->id);
    }

    freeArray(arr);
    return 0;
}
