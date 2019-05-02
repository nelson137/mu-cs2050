#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int randint(int min, int max) {
    return rand() % (max+1-min) + min;
}


double average(time_t arr[], int size) {
    static time_t sum;
    sum = 0;
    for (int i=0; i<size; i++)
        sum += arr[i];
    return (double) sum/size;
}


time_t time_func(int(*func)(int,int[],int,int),
                 int q, int arr[], int b, int e) {
    static time_t start, end;

    start = time(NULL);
    func(q, arr, b, e);
    end = time(NULL);

    printf("start: %ld\n", start);
    printf("end:   %ld\n", end);

    return end - start;
}


double time_repeat_func(int repeat, int(*func)(int,int[],int,int),
                        int q, int arr[], int b, int e) {
    time_t runtimes[repeat];

    for (int i=0; i<repeat; i++)
        runtimes[i] = time_func(func, q, arr, b, e);

    return average(runtimes, repeat);
}


int main(void) {
    srand(time(NULL));

    /* int size = 10000; */
    /* int array[size]; */
    /* for (int i=0; i<size; i++) */
        /* array[i] = randint(10, 25); */

    /* time_t t = time_func(binary_search, 20, array, 0, size); */
    /* printf("binary_search runtime: %ld\n", t); */

    return 0;
}
