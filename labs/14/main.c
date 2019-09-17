#include "lab14.h"

int main(void) {
    int size;
    FILE *fp = fopen("employee.csv", "r"); // open file
    if (fp){
        fscanf(fp,"%d\n", &size);
    }
    else {
        printf("Cannot find the file\n"); // error checking
        return -1;
    }

    Employee* array = (Employee*)malloc(sizeof(Employee)*size);
    if (array == NULL){ // error check for malloc
        printf("Allocating memory failed\n");
        return -1;
    }

    // read data into array
    for (int i = 0; i < size; i++){
        array[i] = readRecord(fp);
    }
    fclose(fp);

    Node* heap = NULL;
    for (int i = 0; i < size; i++){
        heap = insertMinHeap(heap, array[i]);
    }

    // test whether it's balanced
    printf("Total number of records in the heap is %d, sub-left side contains %d records, sub-right side contains %d records, and the height of this heap is %d\n\n", heap->size, heap->left->size, heap->right->size, findHeight(heap));

    // test findMax
    Employee maxValue, minValue;
    //maxValue.ssn = 0;
    minValue.salary = 999999999;
    maxValue.salary = 0;

    findMax(heap,&maxValue);
    findMin(heap,&minValue);

    printf("The maximum salary is %.2f\n\n",maxValue.salary);
    printf("The minimum salary is %.2f\n\n",minValue.salary);

    // test removeMin
    Employee min;
    for (int i = 0; i < 5; i++){
        // test the first 5 removeMin
        min = removeMin(heap);
        printf("Number of records after removal = %d, sub-left side = %d, sub-right side = %d\nRemoved record salary = %.2f, and current minimum salary = %.2f\n\n", heap->size, heap->left->size, heap->right->size, min.salary, heap->data.salary);
    }

    return 0;
}
