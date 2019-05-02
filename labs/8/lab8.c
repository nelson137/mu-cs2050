#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INIT_MAX_SIZE 2


/*************************************************
 * Utility Functions
 ************************************************/


/**
 * Return a random integer in the interval [min,max].
 * @param min The minimum integer bound.
 * @param max The maximum integer bound.
 */
int randInt(int min, int max) {
    return rand() % (max+1-min) + min;
}


/*************************************************
 * Rect
 ************************************************/


typedef struct _rect {
    int height;
    int width;
} Rect;


/**
 * Return a new Rect with the given height and width.
 * @param height An integer height to use.
 * @param width An integer width to use.
 */
Rect *createRect(int height, int width) {
    Rect *rect = malloc(sizeof(Rect));
    if (rect) {
        rect->height = height;
        rect->width = width;
    }
    return rect;
}


/**
 * Return a new Rect with a random height and width.
 * Uses the createRect function.
 */
Rect *createRandRect(void) {
    return createRect(randInt(1,7), randInt(1,7));
}


/*************************************************
 * Node
 ************************************************/


typedef struct Node {
    Rect *rect;
    struct Node *next;
} Node;


/**
 * Return a new dummy Rect node;
 * Memory is allocated with malloc.
 */
Node *createDummyNode(void) {
    Node *dummyNode = malloc(sizeof(Node));
    if (dummyNode)
        dummyNode->rect = createRect(0, 0);
    return dummyNode;
}


/**
 * Return a new Rect.
 * Memory is allocated with malloc.
 */
Node *createNode(void) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode)
        newNode->rect = createRandRect();
    return newNode;
}


/*************************************************
 * Linked List
 ************************************************/


/**
 * Return a new linked Rect list.
 */
Node *initList(void) {
    Node* tail = createDummyNode();
    if (tail == NULL || tail->rect == NULL)
        return NULL;
    tail->next = NULL;

    Node *head = createDummyNode();
    if (head == NULL || head->rect == NULL)
        return NULL;
    head->next = tail;

    return head;
}


/**
 * Prepend a new Rect with random data to a linked Rect list.
 * @param head The list to use.
 */
int insertList(Node *head) {
    Node *newNode = createNode();
    if (newNode == NULL || newNode->rect == NULL)
        return -1;

    newNode->next = head->next;
    head->next = newNode;

    return 0;
}


/**
 * Insert a new Rect into a linked Rect list at the given index.
 * @param index The integer index of where to insert the new Rect.
 */
int insertNodeBasedOnIndex(Node *head, int index) {
    Node *newNode = createNode();
    if (newNode == NULL || newNode->rect == NULL)
        return -2;

    int i = 0;
    for (Node *p=head; p->next; p=p->next) {
        if (i++ == index) {
            newNode->next = p->next;
            p->next = newNode;
            return 1;
        }
    }

    return -1;
}


/**
 * Remove the first node in a linked Rect list with the given width.
 * @param width The integer width to look for.
 */
int removeNodeBasedOnValue(Node *head, int width) {
    for (Node *p=head; p->next->next; p=p->next) {
        if (p->next->rect->width == width) {
            Node *to_rm = p->next;
            p->next = p->next->next;
            free(to_rm->rect);
            free(to_rm);
            return 1;
        }
    }
    return -1;
}


/**
 * Print the width of each Rect in a linked Rect list.
 * @param head The list to use.
 */
void printList(Node *head) {
    printf("Width values:");
    // Start with second node (first is a dummy)
    // Check `p->next` instead of `p` because there is a dummy tail.
    for (Node *p=head->next; p->next; p=p->next)
        printf(" %d", p->rect->width);
    printf("\n");
}


/**
 * Print the width of each Rect in a linked Rect list in reverse order.
 * This could have also been accomplished with a "previous" pointer in
 *   each Node. Either way, this operation has complexity O(2n).
 * @param head The list to use.
 */
void printReverseList(Node *head) {
    printf("Reverse width values:");

    // If the second node is not the dummy tail
    if (head->next->next) {
        int max_size = INIT_MAX_SIZE, size = 0;
        int *widths = malloc(sizeof(int) * max_size);

        for (Node *p=head->next; p->next; p=p->next) {
            if (size == max_size) {
                max_size += INIT_MAX_SIZE;
                widths = realloc(widths, sizeof(int)*max_size);
            }
            widths[size++] = p->rect->width;
        }

        for (int i=size-1; i>=0; i--)
            printf(" %d", widths[i]);

        free(widths);
    }

    printf("\n");
}


/**
 * Free all memory allocated for a linked Rect list.
 * @param head The list to use.
 */
Node *freeList(Node *head) {
    for (Node *next, *curr=head; curr; curr=next) {
        // Save the next node
        next = curr->next;
        // Free the current node's Rect
        free(curr->rect);
        curr->rect = NULL;
        // Free the current node
        free(curr);
        curr = NULL;
    }
    return NULL;
}


/*************************************************
 * Main
 ************************************************/


int main(void) {
    /**
     * Main changed to accommodate for dummy nodes.
     */

    srand(time(NULL));
    Node *head = initList();
    int check;

    for (int i = 0; i < 10; i++) {
        check = insertNodeBasedOnIndex(head, i);
        if (check == -1) {
            return -1;
        }
    }
    printList(head);

    check = insertNodeBasedOnIndex(head, 7);
    printList(head);

    check = removeNodeBasedOnValue(head, rand()%10-1);
    printList(head);

    printReverseList(head);  // Bonus

    freeList(head);

    return 0;
}
