/*
    Single Linked List 
    간단한 기능 구현 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_
{
    char* data;
    struct node_* next;
}   NODE;

NODE* head = NULL;


// insert_fisrt : 맨 앞 노드 삽입

/* head가 global인 경우 */

void insert_first(char* item)
{
    NODE* tmp = (NODE*)malloc(sizeof(NODE));
    tmp->data = item;
    tmp->next = head;
    head = tmp;
}

/* head가 local인 경우 */ 

// 방법 1. 연결리스트의 head의 주소를 parameter로 넘겨줘서, 새로운 노드를 추가하고 caller의 head가 그 노드를 가리키게 할 수 있게 해줘야한다.
/*
void insert_first(NODE** phead, char* item)
{
    NODE* tmp = (NODE*)malloc(sizeof(NODE));
    tmp->data = item;
    tmp->next = *phead;
    *phead = tmp;
}
*/

// 방법 2. 연결리스트의 head(첫 NODE 주소)를 parameter로 넘겨주고 caller의 head가 새로운 노드를 가리킬 수 있게 새 노드의 주소를 return 해준다.
/*
NODE* insert_first(NODE* head, char* item)
{
    NODE* tmp = (NODE*)malloc(sizeof(NODE));
    tmp->data = item;
    tmp->next = head;
    return tmp;
}
*/


// insert_after : 어떤 노드 뒤에 삽입
// insert_before 같은 경우 간단하지 않다. 단순연결리스트에 새로운 노드를 삽입할 때 삽입할 위치의 바로 앞 노드의 주소가 필요하다. 
// 즉, 어떤 노드의 뒤에 삽입은 간단하지만, 어떤 노드의 앞에 삽입하는 것은 간단하지 않다. 그래서 before같은 것을 해야할 상황을 안만드는 것이 정답이다.
int insert_after(NODE* prev, char* item)
{
    if(!prev)
        return NULL;
    
    NODE* tmp = (NODE*)malloc(sizeof(NODE));
    tmp->data = item;
    tmp->next = prev->next;
    prev->next = tmp;

    return 1;
}



// remove_first : 맨 앞 노드 삭제
NODE* remove_first()
{
    if(!head)
        return NULL;
    else
    {
        NODE* tmp = head;
        head = head->next;
        return tmp; // free(tmp)를 언젠가 해줘야 함
    }
}
/*
NODE* remove_first(NODE** phead, char* item)
{
    if( !(*phead) )
        return NULL;
    else
    {
        NODE* tmp = *phead;
        *phead = (*phead)->next;
        return tmp; // free(tmp)를 언젠가 해줘야 함
    }
}
*/



// remove_after : 어떤 노드의 다음 노드 삭제
// 단순연결리스트에서 어떤 노드를 삭제할 때 삭제할 노드의 바로 앞 노드의 주소가 필요하다. 그래서, 삭제할 노드의 주소만으로는 삭제 불가능
NODE* remove_after(NODE* prev)
{
    NODE* tmp = prev->next;
    if(!tmp)
        return NULL;
    else
    {   
        prev->next = tmp->next;
        return tmp;
    }
}



// find
NODE* find(char* word)
{
    NODE* p = head;
    while(!p)
    {
        if(!strcmp(p->data , word))
            return p;
        p = p->next;
    }
    return NULL;
}
/*
NODE* find(NODE* head, char* word)
{
    NODE* p = head;
    while(!p)
    {
        if(!strcmp(p->data , word))
            return p;
        p = p->next;
    }
    return NULL;
}
*/



// get_node : index번째 노드의 주소를 반환
NODE* get_node(int index)
{
    if(index < 0)
        return NULL;

    NODE* p = head;
    for(int i=0; i < index && p; i++)
        p = p->next;

    return p;
}
/*
NODE* get_node(NODE* head, int index)
{
    if(index < 0 && !head)
        return NULL;

    NODE* p = head;
    for(int i=0; i < index && p; i++)
        p = p->next;

    return p;
}
*/



// insert_index : index번째 위치에 새로운 노드 삽입
int insert_index(int index, char* item)
{
    if(index < 0)
        return NULL;

    if(!index)
    {
        insert_first(item);
        return 1;
    }

    NODE* prev = get_node(index-1);
    if(prev)
    {
        insert_after(prev, item);
        return 1;
    }
    return NULL;
}



// insert_to_ordered_list : 연결리스트가 오름차순 정렬이 되어 있을때, 새로운 데이터를 삽입
void insert_to_ordered_list(char* item)
{
    NODE* curr = head;
    NODE* prev = NULL;
    
    while(curr && !strcmp(curr->data,item))
    {
        prev = curr;
        curr = curr->next;
    }

    if(!curr)
        insert_first(item);
    else
        insert_after(prev, item);
}



// remove_index : index번째 노드를 삭제하고 그 노드의 데이터 return
NODE* remove_index(int index)
{
    if(index < 0)
        return NULL;

    if(!index)
        return remove_first();
    
    NODE* prev = get_node(index-1);
    if(prev)
        return remove_after(prev);
    return NULL;
}



// remove_item : target string이 저장된 노드를 찾아 삭제
NODE* remove_item(char* item)
{
    NODE* curr = head;
    NODE* prev = NULL;

    while( curr && !strcmp(curr->data, item))
    {
        prev = curr;
        curr = curr->next;
    }

    if(!curr)
        return NULL;

    if(!prev)
        return remove_first();
    else
        return remove_after(prev);
}




