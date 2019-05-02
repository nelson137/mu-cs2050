#include <stdio.h>
#include <stdlib.h>


typedef struct _bst {
    int value;
    struct _bst *left;
    struct _bst *right;
} bst;


bst *createBST(void) {
    return NULL;
}


bst *createNode(int value) {
    bst *new = malloc(sizeof(bst));
    new->value = value;
    new->left = new->right = NULL;
    return new;
}


void insertBST(bst **tree, bst *node) {
    if (node == NULL)
        return;
    if (*tree == NULL) {
        *tree = node;
        return;
    }
    if (node->value < (*tree)->value)
        return insertBST(&(*tree)->left, node);
    else
        return insertBST(&(*tree)->right, node);
}


bst *findBST(bst *tree, bst *node) {
    if (node == NULL || tree == NULL)
        return NULL;
    if (tree->value == node->value)
        return tree;
    else if (node->value < tree->value)
        return findBST(tree->left, node);
    else
        return findBST(tree->right, node);
}


bst *freeBST(bst *tree) {
    if (tree == NULL)
        return NULL;
    freeBST(tree->left);
    freeBST(tree->right);
    free(tree);
    return NULL;
}


int main(void) {
    bst *tree = createBST();

    freeBST(tree);
    return 0;
}
