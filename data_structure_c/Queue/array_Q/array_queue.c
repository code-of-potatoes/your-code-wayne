#include <stdio.h>
#include <stdlib.h>
#include "array_queue.h"

QUEUE* Create(int max_queue_size)
{
    QUEUE* tmp = (QUEUE*)malloc(sizeof(QUEUE));
    tmp->max_size = max_queue_size;
    tmp->rear = tmp->front = -1;
    return tmp;
}

char IsFull(QUEUE* q)
{
    return q->rear == q->max_size -1;
}

char IsEmpty(QUEUE* q)
{
    return q->front == q->rear;    
}

void EnQueue(QUEUE* q, int item)
{
    if(IsFull(q))   return;
    q->queue[++(q->rear)] = item;
}
int DeQueue(QUEUE* q)
{
    if(IsEmpty(q))  return -1;
    return q->queue[++(q->front)];
}