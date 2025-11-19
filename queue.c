#include "queue.h"
#include <stdio.h>
void queue_init(Queue *q){ q->front=0; q->rear=-1; q->size=0; }
int queue_is_empty(Queue *q){ return q->size==0; }
int queue_is_full(Queue *q){ return q->size==QUEUE_CAP; }
int queue_enqueue(Queue *q, Customer c){
    if(queue_is_full(q)) return 0;
    q->rear=(q->rear+1)%QUEUE_CAP;
    q->data[q->rear]=c;
    q->size++;
    return 1;
}
Customer queue_dequeue(Queue *q){
    Customer empty; empty.id=-1;
    if(queue_is_empty(q)) return empty;
    Customer c=q->data[q->front];
    q->front=(q->front+1)%QUEUE_CAP;
    q->size--;
    return c;
}
void queue_remove_by_id(Queue *q, int id){
    if(queue_is_empty(q)) return;
    int count=q->size;
    int idx=q->front;
    Customer tmp[QUEUE_CAP];
    int t=0;
    for(int i=0;i<count;i++){
        Customer c=q->data[idx];
        if(c.id!=id) tmp[t++]=c;
        idx=(idx+1)%QUEUE_CAP;
    }
    // rebuild
    q->front=0; q->rear=-1; q->size=0;
    for(int i=0;i<t;i++) queue_enqueue(q,tmp[i]);
}
void queue_print(Queue *q){
    if(queue_is_empty(q)){ printf("None\n"); return; }
    int idx=q->front;
    for(int i=0;i<q->size;i++){
        Customer *c=&q->data[idx];
        printf("ID:%d Name:%s Priority:%d\n", c->id, c->name, c->priority);
        idx=(idx+1)%QUEUE_CAP;
    }
}
