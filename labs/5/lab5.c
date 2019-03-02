#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>


#define RESET     "\33[0m"
#define RED       "\33[91m"
#define W_RED(x)  RED x RESET


typedef struct {
    int id;
    float salary;
    int age;
} Employee;


/*************************************************
 * Helper Funtions
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
 * Return a new Employee array.
 * @param len The length of the array.
 */
Employee **createArray(int len) {
    int *arr = malloc(2*sizeof(int) + len*sizeof(Employee*));
    if (arr == NULL) {
        error("Out of memory\n");
        exit(1);
    }
    *(arr++) = len;
    *(arr++) = 0;
    return (Employee**)arr;
}


/**
 * Return the maximum length of an Employee array.
 * @param arr The array to use.
 */
int arrayLen(Employee **arr) {
    return *( (int*)arr - 2 );
}


/**
 * Return the next available index in an Employee array.
 * @param arr The array to use.
 */
int arrayTailIndex(Employee **arr) {
    return *( (int*)arr - 1);
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
 * Return a pointer to the first Employee with age `age` in an Employee array.
 * @param arr The array to use.
 * @param age The age to search for.
 */
Employee *findByAge(Employee **arr, int age) {
    for (int i=0; i<arrayLen(arr); i++)
        if (arr[i]->age == age)
            return arr[i];
    return NULL;
}


/**
 * Free the memory allocated for an Employee array and all of its Employees.
 * @param arr The array to use.
 */
void freeArray(Employee **arr) {
    for (int i=0; i<arrayLen(arr); i++)
        free(arr[i]);
    free((int*)arr - 2);
    *arr = NULL;
}


/*************************************************
 * Core Functions
 ************************************************/


/**
 * Return an Employee pointer array filled with the data from a file.
 * @param fn The name of the file to use.
 */
Employee **loadData(char *fn) {
    if (!file_exists(fn))
        error("File does not exist: %s\n", fn);

    FILE *fp = fopen(fn, "r");
    if (fp == NULL)
        error("Could not open file: %s\n", fn);

    int nlines;
    if (fscanf(fp, "%d\n", &nlines) == EOF)
        // File is empty
        error("File contains no records: %s\n", fn);

    Employee **arr = createArray(nlines);

    int i;
    // Read data from the file into arr
    for (i=0; i<nlines; i++) {
        Employee *e = malloc(sizeof(Employee));
        if (e == NULL) {
            error("Out of memory\n");
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
    if (i <= nlines-1) {
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
 * Main
 ************************************************/


int main(void) {
    char *fn = "employee.csv";
    Employee **arr = loadData(fn);

    Employee *aged55 = findByAge(arr, 55);
    if (aged55 == NULL) {
        puts("None of the employees are aged 55.");
    } else {
        printf("Found employee aged 55:\n");
        printEmployee(aged55);
    }

    printf("\n");

    printf("Test overfilling the array:\n");
    Employee t = {0, 0.0, 0};
    if (addNewEmployee(&t, arr)) {
        freeArray(arr);
        error("Attempting to append Employee to full array\n");
    }

    freeArray(arr);
    return 0;
}
