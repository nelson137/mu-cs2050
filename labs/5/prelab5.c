#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int id;
    float salary;
    int age;
} Employee;


/*************************************************
 * Helper Funtions
 ************************************************/


void error(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(1);
}


void printEmployee(Employee *e) {
    printf("id:%d  salary:%.2f  age:%d\n", e->id, e->salary, e->age);
}


/*************************************************
 * Employee Array
 ************************************************/


Employee **createArray(int len) {
    int *arr = malloc(2*sizeof(int) + len*sizeof(Employee*));
    if (arr == NULL) {
        perror("malloc");
        exit(1);
    }
    *(arr++) = len;
    *(arr++) = 0;
    return (Employee**)arr;
}


int arrayLen(Employee **arr) {
    return *( (int*)arr - 2 );
}


int arrayTailIndex(Employee **arr) {
    return *( (int*)arr - 1);
}


int arrIncTailIndex(Employee **arr) {
    return *( (int*)arr - 1) += 1;
}


int addNewEmployee(Employee *e, Employee **arr) {
    int tailIndex = arrayTailIndex(arr);
    if (tailIndex < arrayLen(arr)) {
        arr[tailIndex] = e;
        arrIncTailIndex(arr);
        return 0;
    } else {
        return -1;
    }
}


void freeArray(Employee **arr) {
    for (int i=0; i<arrayLen(arr); i++)
        free(arr[i]);
    free((int*)arr - 2);
    *arr = NULL;
}


/*************************************************
 * Core Functions
 ************************************************/


Employee **loadData(char *fn) {
    FILE *fp = fopen(fn, "r");
    if (fp == NULL)
        error("Could not open file: %s\n", fn);

    int nlines;
    if (fscanf(fp, "%d\n", &nlines) == EOF)
        error("File contains no records: %s\n", fn);

    Employee **arr = createArray(nlines);

    int i;
    for (i=0; i<nlines; i++) {
        Employee *e = malloc(sizeof(Employee));
        if (e == NULL) {
            perror("malloc");
            freeArray(arr);
            exit(1);
        }
        if (fscanf(fp, "%d,%f,%d\n", &e->id, &e->salary, &e->age) == EOF)
            break;
        addNewEmployee(e, arr);
    }

    if (i <= nlines-1) {
        freeArray(arr);
        error("Too few records in file: %s\n", fn);
    }

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

    freeArray(arr);
    return 0;
}
