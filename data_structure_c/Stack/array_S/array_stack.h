#ifndef __ARRAY_S_H__
#define __ARRAY_S_H__

#define MAX_STACK_SIZE 5

typedef struct stack_
{
    int stack[MAX_STACK_SIZE];
    int max_size;
    int top;    
}   STACK;

STACK* Create(int max_stack_size);
char IsFull(STACK* s);
char IsEmpty(STACK* s);
void Push(STACK* s, int item);
int Pop(STACK* s);

#endif