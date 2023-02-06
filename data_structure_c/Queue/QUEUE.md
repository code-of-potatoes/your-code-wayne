# QUEUE
- 삽입과 삭제가 다른 쪽에서 발생하는 Ordered List  
    - 삽입이 발생하는 위치 : rear  
    - 삭제가 발생하는 위치 : front  
- 선입선출 : First-In-First-Out(FIFO)  

### ADT QUEUE
- Object : 0개 이상의 유한 개 원소로 구성된 Ordered List  
- Opertaion : for all queue ∈ Queue, item ∈ element, max_size ∈ Positive Integer  

    `Queue Create(max_size)` ::=  
        max_size만큼의 원소를 저장할 수 있는 빈 큐 생성  

    `Boolean IsFull(queue, max_size)` ::=  
        if(큐의 원소 수 == max_size)   return TRUE  
        else    return FALSE  
        
    `Boolean IsEmpty(queue)` ::=  
        if(큐의 원소 수 == 0)   return TRUE  
        else    return FALSE  

    `Queue Add(queue, item)` ::=  
        if(IsFull(queue,max_size))   queue_full_error  
        else 큐의 `rear에 item을 저장`한 후 return  

    `Element Delete(queue)` ::=  
        if(IsEmpty(queue,max_size))  queue_full_error  
        else 스택 `front의 item을 제거`해서 return 

# Circular Queue
- 배열을 이용한 큐를 구현할 때 발생하는 문제점   
    - QueueFull의 조건 : rear == max_Q_size -1  
    - 문제점 : 큐에 저장된 원소의 수 < max_Q_size  

데이터를 넣을 때마다 rear가 증가하고, 데이터를 빼낼 때마다 front가 증가한다.  
rear가 끝에 도달하면 Queue Full 조건이 만족되어 더 이상 데이터를 넣을 수 없게된다.  
하지만, 이때 항상 Queue에 데이터가 가득 차있다고 할 수는 없다.  

why? front를 통해 데이터를 빼내면서 왔으면 그 만큼의 빈 공간이 앞 부분에 남아있게 된다.  
그렇지만 rear는 끝에 도달했기 때문에 더 이상 데이터를 넣을 수 없게 된다.

이것은 Queue에 할당된 해당 공간을 비효율적으로 사용하게 되는 문제를 발생시킨다.  