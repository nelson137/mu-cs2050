#include <stdio.h>
#include <stdlib.h>


void *createArray(int n, int elemSize) {
    int *array = malloc(sizeof(int) + n*elemSize);
    array[0] = n;
    return (void*)(array+1);
}


int arraySize(void *array) {
    return ((int*)array)[-1];
}


void freeArray(void *array) {
    free( ((int*)array) - 1 );
}


int main(void) {
    int *arr = createArray(3, sizeof(int));
    printf("arr len: %d\n", arraySize(arr));
    freeArray(arr);

    return 0;
}
