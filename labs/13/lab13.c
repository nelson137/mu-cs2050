#include "lab13.h"


Employee *readRecord(FILE *fp) {
    Employee *e = malloc(sizeof(Employee));

    if (e == NULL)
        return e;

    if (fscanf(fp, "%d,%f,%d\n", &e->id, &e->salary, &e->age) == EOF) {
        free(e);
        return NULL;
    }

    return e;
}


int comparison(void *v_a, void *v_b) {
    Employee *a = v_a, *b = v_b;
    if (a->salary > b->salary)
        return 1;
    else if (a->salary < b->salary)
        return -1;
    else
        return 0;
}


Node *createNode(void *data) {
    Node *new = malloc(sizeof(Node));
    new->data = data;
    new->left = new->right = NULL;
    return new;
}


Node *insertBST(Node *tree, void *data) {
    // There is no data to insert
    if (data == NULL)
        return tree;

    // There is no tree
    if (tree == NULL)
        return createNode(data);

    if (comparison(data, tree->data) < 0)
        tree->left =
            tree->left == NULL
            ? createNode(data)
            : insertBST(tree->left, data);
    else
        tree->right =
            tree->right == NULL
            ? createNode(data)
            : insertBST(tree->right, data);

    return tree;
}


void inOrderPrintSalary(Node *tree) {
    if (tree == NULL)
        return;
    if (tree->left == tree->right) {  // Both == NULL
        printf("%.2f\n", ((Employee*)tree->data)->salary);
    } else {
        inOrderPrintSalary(tree->left);
        inOrderPrintSalary(tree->right);
    }
}


void deleteTree(Node *tree) {
    if (tree == NULL)
        return;
    deleteTree(tree->left);
    deleteTree(tree->right);
    free(tree);
}
