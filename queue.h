#ifndef QUEUE_H
#define QUEUE_H
#include "customer.h"
#define QUEUE_CAP 200
typedef struct {
    Customer data[QUEUE_CAP];
    int front;
    int rear;
    int size;
} Queue;
void queue_init(Queue *q);
int queue_is_empty(Queue *q);
int queue_is_full(Queue *q);
int queue_enqueue(Queue *q, Customer c);
Customer queue_dequeue(Queue *q);
void queue_remove_by_id(Queue *q, int id);
void queue_print(Queue *q);
#endif
