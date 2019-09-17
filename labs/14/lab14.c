#include "lab14.h"


Employee readRecord(FILE* fp){
    Employee record;
    // scan file and get inputs
    fscanf(fp, "%d,%f,%d\n", &record.id, &record.salary, &record.age);
    return record;
}


Node *createNode(Employee data) {
    Node *new = malloc(sizeof(Node));
    new->data = data;
    new->size = 1;
    new->left = new->right = NULL;
    return new;
}


Node *insertMinHeap(Node *pq, Employee data) {
    // There is no pq
    if (pq == NULL)
        return createNode(data);

    if (pq->data.salary <= data.salary) {
        // Insert into smallest sub-heap

        pq->size++;

        if (pq->left == NULL) {
            pq->left = insertMinHeap(pq->left, data);
        } else if (pq->right == NULL) {
            pq->right = insertMinHeap(pq->right, data);
        } else {  // Neither are NULL
            if (pq->left->size < pq->right->size)
                pq->left = insertMinHeap(pq->left, data);
            else
                pq->right = insertMinHeap(pq->right, data);
        }
    } else {  // p->data > data
        // Replace root with data
        Employee old_root = pq->data;
        pq->data = data;
        pq = insertMinHeap(pq, old_root);
    }

    return pq;
}


Employee removeMin(Node *pq) {
    Employee min = pq->data;

    if (pq->left == pq->right) {  // Both are NULL
        free(pq);
        return min;
    }

    pq->size--;

    if (pq->left == NULL) {
        pq->data = removeMin(pq->right);
    } else if (pq->right == NULL) {
        pq->data = removeMin(pq->left);
    } else {  // Neither are NULL
        pq->data =
            pq->left->data.salary < pq->right->data.salary
            ? removeMin(pq->left)
            : removeMin(pq->right);
    }

    return min;
}


void findMin(Node *pq, Employee *data) {
    if (pq) {
        data->id     = pq->data.id,
        data->salary = pq->data.salary,
        data->age    = pq->data.age;
    }
}


void findMax(Node *pq, Employee *data) {
    if (pq == NULL)
        return;

    if (pq->left == pq->right) {  // Both are NULL
        data->id     = pq->data.id;
        data->salary = pq->data.salary;
        data->age    = pq->data.age;
    } else if (pq->left == NULL) {
        findMax(pq->right, data);
    } else if (pq->right == NULL) {
        findMax(pq->left, data);
    } else {
        if (pq->left->data.salary < pq->right->data.salary)
            findMax(pq->right, data);
        else
            findMax(pq->left, data);
    }
}


int findHeight(Node *pq) {
    if (pq == NULL)
        return 0;

    int height = 1;

    if (pq->left == pq->right)  // Both are NULL
        return 1;
    else if (pq->left == NULL)
        height += findHeight(pq->right);
    else if (pq->right == NULL)
        height += findHeight(pq->left);
    else {  // Neither are NULL
        height +=
            pq->left > pq->right
            ? findHeight(pq->left)
            : findHeight(pq->right);
    }

    return height;
}
