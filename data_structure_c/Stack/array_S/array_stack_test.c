#include <stdio.h>
#include <stdlib.h>
#include "array_stack.h"

int main()
{
    STACK* s;

    s = Create(MAX_STACK_SIZE);
    
    /* Create test */
    printf("Is Empty? %s\n", IsEmpty(s) ? "Yes" : "No" );
    printf("Is Full? %s\n", IsFull(s) ? "Yes" : "No" );
    
    /* Push test */
    Push(s, 10);
    Push(s, 20);
    Push(s, 30);
    Push(s, 40);

    printf("Is Empty? %s\n", IsEmpty(s) ? "Yes" : "No" );
    printf("Is Full? %s\n", IsFull(s) ? "Yes" : "No" );
    
    /* Pop test */
    printf("Pop : %d\n", Pop(s));
    printf("Pop : %d\n", Pop(s));
    printf("Pop : %d\n", Pop(s));
    printf("Pop : %d\n", Pop(s));

    printf("Is Empty? %s\n", IsEmpty(s) ? "Yes" : "No" );
    printf("Is Full? %s\n", IsFull(s) ? "Yes" : "No" );
    
    /* Empty Pop test */
    printf("Pop : %d\n", Pop(s));

    /* Max test*/
    Push(s, 10);
    Push(s, 20);
    Push(s, 30);
    Push(s, 40);
    Push(s, 50);
    Push(s, 60);

    printf("Is Empty? %s\n", IsEmpty(s) ? "Yes" : "No" );
    printf("Is Full? %s\n", IsFull(s) ? "Yes" : "No" );

    printf("Pop : %d\n", Pop(s));
    printf("Pop : %d\n", Pop(s));
    printf("Pop : %d\n", Pop(s));
    printf("Pop : %d\n", Pop(s));
    printf("Pop : %d\n", Pop(s));
    printf("Pop : %d\n", Pop(s));

    printf("Is Empty? %s\n", IsEmpty(s) ? "Yes" : "No" );
    printf("Is Full? %s\n", IsFull(s) ? "Yes" : "No" );

    free(s);

    return 0;
}