#include "prelab14.h"


int comparison(void *v_a, void *v_b) {
    Employee *a = v_a, *b = v_b;
    if (a->salary > b->salary)
        return 1;
    else if (a->salary < b->salary)
        return -1;
    else
        return 0;
}


Node *createNode(int data) {
    Node *new = malloc(sizeof(Node));
    new->data = data;
    new->left = new->right = NULL;
    new->size = 1;
    return new;
}


Node *insertPQ(Node *pq, int data) {
    // There is no pq
    if (pq == NULL)
        return createNode(data);

    pq->size++;

    if (pq->data < data) {
        // Insert into smaller sub-heap
        if (pq->right == NULL) {
            pq->right = insertPQ(pq->right, data);
        } else if (pq->left == NULL) {
            pq->left = insertPQ(pq->left, data);
        } else {  // Neither are NULL
            if (pq->left->size < pq->right->size)
                pq->left = insertPQ(pq->left, data);
            else
                pq->right = insertPQ(pq->right, data);
        }
    } else {  // p->data > data
        // Replace root with data
        int old_root_data = pq->data;
        pq->data = data;
        insertPQ(pq, old_root_data);
    }

    return pq;
}


int deletemin(Node *pq) {
    int min = pq->data;

    if (pq->left == pq->right) {  // Both are NULL
        free(pq);
        return min;
    }

    pq->size--;

    if (pq->left == NULL) {
        pq->data = deletemin(pq->right);
    } else if (pq->right == NULL) {
        pq->data = deletemin(pq->left);
    } else {  // Neither are NULL
        pq->data =
            pq->left->data < pq->right->data
            ? deletemin(pq->left)
            : deletemin(pq->right);
    }

    return min;
}


void deletePQ(Node *pq) {
    if (pq == NULL)
        return;
    deletePQ(pq->left);
    deletePQ(pq->right);
    free(pq);
}
