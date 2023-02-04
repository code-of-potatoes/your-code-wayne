#include <stdio.h>
#include <stdlib.h>
#include "array_stack.h"

STACK* Create(int max_stack_size)
{
    STACK* tmp = (STACK*)malloc(sizeof(STACK));
    tmp->max_size = max_stack_size;
    tmp->top = -1;
    return tmp;
}

char IsFull(STACK* s)
{
    return s->top >= s->max_size - 1;
}

char IsEmpty(STACK* s)
{
    return s->top < 0;
}

void Push(STACK* s, int item)
{
    if(IsFull(s))
        return;
    
    s->stack[++(s->top)] = item;
}

int Pop(STACK* s)
{
    if(IsEmpty(s))
        return -1;
    
    return s->stack[(s->top)--];
}
