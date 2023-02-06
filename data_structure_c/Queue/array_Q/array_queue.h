#ifndef __ARRAY_Q_H__
#define __ARRAY_Q_H__

#define MAX_Q_SIZE 5

typedef struct queue_
{
    int queue[MAX_Q_SIZE];
    int max_size;
    int rear, front;
}   QUEUE;

QUEUE* Create(int max_queue_size);
char IsFull(QUEUE* q);
char IsEmpty(QUEUE* q);
void EnQueue(QUEUE* q, int item);
int DeQueue(QUEUE* q);


#endif