#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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
 * Return a new Rect with a height and width of 0.
 * Uses the createRect function.
 */
Rect *createZeroRect(void) {
    return createRect(0, 0);
}


/**
 * Return a new Rect with a random height and width.
 * Uses the createRect function.
 */
Rect *createRandRect(void) {
    return createRect(randInt(1,10), randInt(1,10));
}


/**
 * Return the area of a Rect.
 * @param rect The rect to use.
 */
int rectArea(Rect *rect) {
    return rect->height * rect->width;
}


/*************************************************
 * List Node
 ************************************************/


typedef struct _list {
    Rect *rect;
    struct _list *next;
} List;


/**
 * Return a new dummy Rect node;
 * Memory is allocated with malloc.
 */
List *createDummyNode(void) {
    List *dummyNode = malloc(sizeof(List));
    if (dummyNode)
        dummyNode->rect = createZeroRect();
    return dummyNode;
}


/**
 * Return a new Rect node.
 * Memory is allocated with malloc.
 */
List *createNode(void) {
    List *newNode = malloc(sizeof(List));
    if (newNode)
        newNode->rect = createRandRect();
    return newNode;
}


/**
 * Return the area of a Rect node.
 * @param n The node to use.
 */
int nodeArea(List *n) {
    return rectArea(n->rect);
}


/*************************************************
 * Linked List
 ************************************************/


/**
 * Return a new linked Rect list.
 */
List *initList(void) {
    List* tail = createDummyNode();
    if (tail == NULL || tail->rect == NULL)
        return NULL;
    tail->next = NULL;

    List *head = createDummyNode();
    if (head == NULL || head->rect == NULL)
        return NULL;
    head->next = tail;

    return head;
}


/**
 * Prepend a new node with random data to a linked Rect list.
 * @param head The list to use.
 */
int insertList(List *head) {
    List *newNode = createNode();
    if (newNode == NULL || newNode->rect == NULL)
        return -1;

    newNode->next = head->next;
    head->next = newNode;

    return 0;
}


/**
 * Return the average area of a linked Rect list.
 * @param head The list to use.
 */
float averageArea(List *head) {
    int total_area = 0, i = 0;
    // Start with second node (first is a dummy)
    // Check `p->next` instead of `p` because `p->next` of the tail == NULL
    for (List *p=head->next; p->next; p=p->next) {
        total_area += nodeArea(p);
        i++;
    }
    return (float) total_area / i;
}


/**
 * Print the area of each node in a linked Rect list.
 * @param head The list to use.
 */
void printList(List *head) {
    printf("Areas: ");
    if (head->next) {
        // Print out the first area
        printf("%d", nodeArea(head->next));
        // Start with third node (first is a dummy, second was already printed)
        // Check `p->next` instead of `p` because `p->next` of the tail == NULL
        for (List *p=head->next->next; p->next; p=p->next)
            printf(", %d", nodeArea(p));
    }
    printf("\n");
}


/**
 * Free all memory allocated for a linked Rect list.
 * @param head The list to use.
 */
List *freeList(List *head) {
    for (List *next, *curr=head; curr; curr=next) {
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
    srand(time(NULL));

    List *list = initList();
    int check = 0;
    for (int i = 0; i < 10; i++) {
        check = insertList(list);
        if (check == -1) {
            printf("Insufficient memory\n");
            return -1;
        }
    }
    printList(list);

    float aveArea = averageArea(list);
    printf("Average area is %.2f\n", aveArea);

    list = freeList(list);

    return 0;
}
