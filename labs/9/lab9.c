#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*************************************************
 * Helper Functions
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
    int width, height;
} Rect;


/**
 * Return a new Rect with random width and height.
 * The memory for the new Rect is allocated with malloc and must be free'd.
 */
Rect *createRect(void) {
    Rect *r = malloc(sizeof(Rect));
    if (r) {
        r->width = randInt(1, 10);
        r->height = randInt(1, 10);
    }
    return r;
}


/**
 * Return the area of a Rect.
 * @param rect The Rect to use.
 */
int rectArea(Rect *rect) {
    return rect ? rect->height*rect->width : -1;
}


/*************************************************
 * Queue Node
 ************************************************/


typedef struct _queuenode {
    Rect *rect;
    struct _queuenode *next;
} QueueNode;


/**
 * Return a new Rect queue node.
 * The width and height for the new Rect are randomly generated.
 */
QueueNode *createQueueNode(void) {
    QueueNode *new = malloc(sizeof(QueueNode));
    if (new) {
        new->rect = createRect();
        new->next = NULL;
    }
    return new;
}


/*************************************************
 * Queue
 ************************************************/


typedef struct _queue {
    QueueNode *head;
    QueueNode *tail;
    int size;
} Queue;


/**
 * Return a new Rect queue.
 * The memory for the new queue is allocated with malloc and must be free'd
 * with freeQueue().
 */
Queue *createQueue(void) {
    Queue *queue = malloc(sizeof(Queue));
    if (queue)
        queue->head = queue->tail = NULL;
    return queue;
}


/**
 * Append a new Rect to a queue.
 * The width and height for the new Rect are randomly generated.
 * The memory allocated for the new item is free'd when the item is dequeued or
 * freeQueue() is called.
 * @param queue The queue to use.
 */
int enqueue(Queue *queue) {
    QueueNode *new = createQueueNode();
    if (!new) return -1;

    if (queue->tail)
        queue->tail->next = new;
    else
        queue->head = new;
    queue->tail = new;

    return 1;
}


/**
 * Pop and return one Rect from the beginning of a queue.
 * The memory allocated for the QueueNode is free'd.
 * @param queue The queue to use.
 */
void *dequeue(Queue *queue) {
    if (!queue)
        return NULL;

    Rect *head_rect = NULL;

    if (queue->head) {
        QueueNode *to_rm = queue->head;
        head_rect = to_rm->rect;
        queue->head = queue->head->next;
        free(to_rm);
    }

    return head_rect;
}


/**
 * Dequeue all elements from a queue.
 * @param queue The queue to use.
 */
int dequeueAll(Queue *queue) {
    if (!queue)
        return -1;

    while (queue->head)
        free(dequeue(queue));

    return 1;
}


/**
 * Free all memory allocated for a queue.
 * @param queue The queue to use.
 */
void freeQueue(Queue *queue) {
    dequeueAll(queue);
    free(queue);
}


/**
 * Print the areas of all the Rects in a queue.
 * @param queue The queue to use.
 */
void printQueue(Queue *queue) {
    if (!queue || !queue->head) return;

    printf("%d", rectArea(queue->head->rect));
    for (QueueNode *n=queue->head->next; n; n=n->next)
        printf(", %d", rectArea(n->rect));
    printf("\n");
}


/*************************************************
 * Main
 ************************************************/


int main(void) {
    srand(time(NULL));

    Queue* queue = createQueue();
    if (queue == NULL){
        return -1;
    }
    int check = 1;;

    for (int i = 0; i < 10; i++){
        check = enqueue(queue);
        if (check == -1){
            return -1;
        }
    }
    printf("(printQueue)");
    printQueue(queue);

    Rect *r = NULL;
    for (int i = 0; i < 2; i++){
        r = (Rect*)dequeue(queue);
        if (r != NULL){
            printf("(deQueue)");
            printf("Rectangle with area %d has been dequeued\n",r->height*r->width);
        }
    }
    printf("(printQueue)");
    printQueue(queue);

    printf("(deQueueAll)");
    check = dequeueAll(queue);
    printf("(printQueue)");
    printQueue(queue);

    // final test for deQueue
    printf("(deQueue)");
    r = dequeue(queue);

    printf("(freeQueue)");
    freeQueue(queue);
    queue = NULL;

    return 0;
}
