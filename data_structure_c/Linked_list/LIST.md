# List
- 기본적인 연산 : insert, remove, search, etc  
- 리스트를 구현하는 대표적인 방법 2가지 : Array, Linked-List  
  
### Array 기반  
- 장점  
    - Random Access 가능 : 접근 시간(access time)이 동일하다. O(1)
- 단점  
    - 크기 고정 : reallocation 필요  
    - List의 중간에 원소를 삽입/삭제할 경우 다수의 데이터를 옮겨야함  
    - 크기만큼 연속되는 공간 필요

### Linked-list 기반
- Node들이 Link로 연결되어있는 자료구조  
- 장점  
    - 다른 데이터의 이동없이 중간에 삽입/삭제 가능  
    - 길이의 제한 없음  
    - 연속된 공간일 필요 없음  
- 단점  
    - Random Access 불가능 : 접근 시간(access time)이 다르다. Worst: O(N)
    - Array에 비해 추가적인 데이터 공간이 필요
    - 삽입/삭제등 관리를 위한 연산을 정의해 줘야 한다.      
- Node  
    - Data field와 하나 이상의 Link field로 구성  
    - Link field는 다음 Node의 주소 저장  
- 주의  
    작성한 코드가 일반적인 경우만이 아닌 특수한 경우(special case)에도 문제가 없이 동작하는지 확인할 것  
    ex. 기존 연결리스트의 길이가 0인 경우(head가 NULL)에도 문제가 없는지 확인해야 한다.