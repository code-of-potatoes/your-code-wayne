#include <stdio.h>
#include <stdlib.h>
#include "array_queue.h"

int main()
{
    QUEUE* s;

    s = Create(MAX_Q_SIZE);
    
    /* Create test */
    printf("Is Empty? %s\n", IsEmpty(s) ? "Yes" : "No" );
    printf("Is Full? %s\n", IsFull(s) ? "Yes" : "No" );
    
    /* Push test */
    EnQueue(s, 10);
    EnQueue(s, 20);
    EnQueue(s, 30);
    EnQueue(s, 40);

    printf("Is Empty? %s\n", IsEmpty(s) ? "Yes" : "No" );
    printf("Is Full? %s\n", IsFull(s) ? "Yes" : "No" );
    
    /* Pop test */
    printf("Pop : %d\n", DeQueue(s));
    printf("Pop : %d\n", DeQueue(s));
    printf("Pop : %d\n", DeQueue(s));
    printf("Pop : %d\n", DeQueue(s));

    printf("Is Empty? %s\n", IsEmpty(s) ? "Yes" : "No" );
    printf("Is Full? %s\n", IsFull(s) ? "Yes" : "No" );
    
    /* Empty Pop test */
    printf("Pop : %d\n", DeQueue(s));

    /* Array Queue Full error */
    EnQueue(s, 10);
    EnQueue(s, 20);
    EnQueue(s, 30);
    EnQueue(s, 40);
    EnQueue(s, 50);
    EnQueue(s, 60);

    printf("Is Empty? %s\n", IsEmpty(s) ? "Yes" : "No" );
    printf("Is Full? %s\n", IsFull(s) ? "Yes" : "No" );

    printf("Pop : %d\n", DeQueue(s));
    printf("Pop : %d\n", DeQueue(s));
    printf("Pop : %d\n", DeQueue(s));
    printf("Pop : %d\n", DeQueue(s));
    printf("Pop : %d\n", DeQueue(s));
    printf("Pop : %d\n", DeQueue(s));

    printf("Is Empty? %s\n", IsEmpty(s) ? "Yes" : "No" );
    printf("Is Full? %s\n", IsFull(s) ? "Yes" : "No" );

    free(s);

    return 0;
}