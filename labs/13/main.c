#include "lab13.h"


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

    Node* BST = NULL;
    for (int i = 0; i < size; i++){
        BST = insertBST(BST,(void*)array[i]);
    }

    inOrderPrintSalary(BST);
    deleteTree(BST);

    for (int i = 0; i < size; i++){
        free(array[i]);
    }
    free(array);

    return 0;
}
