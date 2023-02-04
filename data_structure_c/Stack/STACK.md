# Stack
- 삽입과 삭제가 `top`이라 불리는 한쪽 끝 지점에서 발생하는 Ordered List  
- 후입 선출 : Last-In-First-Out(LIFO)  

### ADT stack
- Object : 0개 이상의 유한 개 원소로 구성된 Ordered List  
- Opertaion : for all stack ∈ Stack, item ∈ element, max_size ∈ Positive Integer  

    `Stack Create(max_size)` ::=  
        max_size만큼의 원소를 저장할 수 있는 빈 스택 생성  

    `Boolean IsFull(Stack)` ::=  
        if(스택에 저장된 원소 수 == max_size)   return TRUE  
        else    return FALSE  
        
    `Boolean IsEmpty(Stack)` ::=  
        if(스택에 저장된 원소 수 == 0)   return TRUE  
        else    return FALSE  

    `void Push(stack, item)` ::=  
        if(IsFull(stack))   stack_full_error  
        else 스택 `top에 item을 저장`한 후 return  

    `Stack Pop(stack)` ::=  
        if(IsEmpty(stack))  stack_empty_error  
        else 스택 `top의 item을 제거`해서 return 
