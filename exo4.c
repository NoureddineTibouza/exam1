#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
typedef struct {
    int queue[MAX_SIZE];
    int rear;
} Queue;
void initializeQueue(Queue* q) {
    q->rear = -1;
}
int is_empty_queue(Queue* q) {
    return q->rear == -1;
}
int is_full_queue(Queue* q) {
    return q->rear == MAX_SIZE - 1;
}
void enqueue(Queue* q, int value) {
    if (is_full_queue(q)) {
        printf("Queue is full! Cannot enqueue %d\n", value);
        return;
    }
    q->queue[++(q->rear)] = value;
}
int dequeue(Queue* q) {
    if (is_empty_queue(q)) {
        printf("Queue is empty! Cannot dequeue.\n");
        return -1;
    }
    int value = q->queue[0];
    for (int i = 0; i < q->rear; i++) {
        q->queue[i] = q->queue[i + 1];
    }
    q->rear--;
    return value;
}
int peek_queue(Queue* q) {
    if (is_empty_queue(q)) {
        printf("Queue is empty! Cannot peek.\n");
        return -1;
    }
    return q->queue[0];
}
typedef struct {
    Queue q;
} StackSingleQueue;
void initializeStackSingle(StackSingleQueue* stack) {
    initializeQueue(&stack->q);
}
void pushSingle(StackSingleQueue* stack, int x) {
    enqueue(&stack->q, x);
    int size = stack->q.rear + 1;
    for (int i = 1; i < size; i++) {
        enqueue(&stack->q, dequeue(&stack->q));
    }
}
int popSingle(StackSingleQueue* stack) {
    if (is_empty_queue(&stack->q)) {
        printf("Stack is empty! Cannot pop.\n");
        return -1;
    }
    return dequeue(&stack->q);
}
int peekSingle(StackSingleQueue* stack) {
    if (is_empty_queue(&stack->q)) {
        printf("Stack is empty! Cannot peek.\n");
        return -1;
    }
    return stack->q.queue[0];
}
int isEmptySingle(StackSingleQueue* stack) {
    return is_empty_queue(&stack->q);
}
typedef struct {
    Queue q1, q2;
} StackTwoQueues;
void initializeStackTwo(StackTwoQueues* stack) {
    initializeQueue(&stack->q1);
    initializeQueue(&stack->q2);
}
void pushTwo(StackTwoQueues* stack, int x) {
    enqueue(&stack->q2, x);
    while (!is_empty_queue(&stack->q1)) {
        enqueue(&stack->q2, dequeue(&stack->q1));
    }
    Queue temp = stack->q1;
    stack->q1 = stack->q2;
    stack->q2 = temp;
}
int popTwo(StackTwoQueues* stack) {
    if (is_empty_queue(&stack->q1)) {
        printf("Stack is empty! Cannot pop.\n");
        return -1;
    }
    return dequeue(&stack->q1);
}
int peekTwo(StackTwoQueues* stack) {
    if (is_empty_queue(&stack->q1)) {
        printf("Stack is empty! Cannot peek.\n");
        return -1;
    }
    return stack->q1.queue[0];
}
int isEmptyTwo(StackTwoQueues* stack) {
    return is_empty_queue(&stack->q1);
}
int main() {
    StackSingleQueue stackSingle;
    initializeStackSingle(&stackSingle);
    printf("Single Queue Stack:\n");
    pushSingle(&stackSingle, 10);
    pushSingle(&stackSingle, 20);
    pushSingle(&stackSingle, 30);
    printf("Top element (Single Queue): %d\n", peekSingle(&stackSingle));
    printf("Popped (Single Queue): %d\n", popSingle(&stackSingle));
    printf("Popped (Single Queue): %d\n", popSingle(&stackSingle));
    printf("Is empty (Single Queue): %d\n", isEmptySingle(&stackSingle));
    StackTwoQueues stackTwo;
    initializeStackTwo(&stackTwo);
    printf("\nTwo Queues Stack:\n");
    pushTwo(&stackTwo, 10);
    pushTwo(&stackTwo, 20);
    pushTwo(&stackTwo, 30);
    printf("Top element (Two Queues): %d\n", peekTwo(&stackTwo));
    printf("Popped (Two Queues): %d\n", popTwo(&stackTwo));
    printf("Popped (Two Queues): %d\n", popTwo(&stackTwo));
    printf("Is empty (Two Queues): %d\n", isEmptyTwo(&stackTwo));
    return 0;
}