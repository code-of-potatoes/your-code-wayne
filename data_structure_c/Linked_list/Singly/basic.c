/*
    단순 이해를 위한 연습 코드
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node_
{
    char* data;
    struct node_* next;
}   NODE;

NODE* head = NULL;

int main()
{
    // create
    head = (NODE*)malloc(sizeof(NODE));
    head->data = "Tuesday";
    head->next = NULL;

    // insert end
    NODE* q = (NODE*)malloc(sizeof(NODE));
    q->data = "Thursday";
    q->next = NULL;
    head->next = q;

    // insert first
    q = (NODE*)malloc(sizeof(NODE));
    q->data = "Monday";
    q->next = head;
    head = q;

    // print
    NODE* p = head;
    while(p)
    {
        printf("%s\n", p->data);
        p = p->next;
    }

    // destroy
    NODE* tmp=NULL;
    while(head)
    {
        tmp = head;
        head = head->next;
        free(tmp);       
    }

    return 0;
}