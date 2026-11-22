#include <stdio.h>
#include <stdbool.h>


typedef struct {
    int items[5];
    int front;
    int rear;
    int count;
} Queue;

/* Initialize queue to empty state */
void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

/* Check whether queue has no elements */
bool isEmpty(const Queue *q) {
    return q->count == 0;
}

/* Check whether queue has reached MAX capacity */
bool isFull(const Queue *q) {
    return q->count == 5;
}

/* Insert an element at the rear (FIFO) */
bool enqueue(Queue *q, int value) {
    if (isFull(q)) {
        printf("Queue Overflow: cannot enqueue %d (queue is full)\n", value);
        return false;
    }
    q->rear = (q->rear + 1) % 5;
    q->items[q->rear] = value;
    q->count++;
    return true;
}

/* Remove and return the front element (FIFO) */
bool dequeue(Queue *q, int *removedValue) {
    if (isEmpty(q)) {
        printf("Queue Underflow: cannot dequeue (queue is empty)\n");
        return false;
    }
    *removedValue = q->items[q->front];
    q->front = (q->front + 1) % 5;
    q->count--;
    return true;
}

/* Inspect the front element without removing it */
bool peek(const Queue *q, int *frontValue) {
    if (isEmpty(q)) {
        printf("Queue is empty: nothing at front\n");
        return false;
    }
    *frontValue = q->items[q->front];
    return true;
}

/* Display elements from front to rear in FIFO order */
void displayQueue(const Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue (front -> rear): ");
    for (int i = 0; i < q->count; i++) {
        int idx = (q->front + i) % 5;
        printf("%d ", q->items[idx]);
    }
    printf("\n");
}

int main(void) {
    Queue q;
    initQueue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    displayQueue(&q); // Queue (front -> rear): 10 20 30

    int value;
    if (peek(&q, &value)) {
        printf("Front element: %d\n", value); // 10
    }

    if (dequeue(&q, &value)) {
        printf("Dequeued: %d\n", value); // 10
    }
    displayQueue(&q); // Queue (front -> rear): 20 30

    enqueue(&q, 40);
    enqueue(&q, 50);
    enqueue(&q, 60); // Wraps around cleanly
    enqueue(&q, 70); // Triggers Queue Overflow (MAX = 5)
    displayQueue(&q); // Queue (front -> rear): 20 30 40 50 60

    while (dequeue(&q, &value)) {
        printf("Dequeued: %d\n", value);
    }
    dequeue(&q, &value); // Triggers Queue Underflow

    return 0;
}