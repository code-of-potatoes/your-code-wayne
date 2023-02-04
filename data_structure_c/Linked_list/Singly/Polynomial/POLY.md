# Polynomial program

- Single Linked List기반 하나의 다항식을 표현하는 구조체 Polynomial 정의  
    - Term들의 Linked List  
    - 차수에 대해 내립차순 정렬  
    - 동일 차수 항은 2개 이상일 수 없다.  
    - Polynomial의 이름은 x를 제외한 영문 소문자 1글자이다. (ex. f, g)  
        
- 하나의 항에 대한 계수, 지수를 표현하기 위헤 구조체 Term 정의
    - 변수 이름은 항상 x  
    - Coefficient(계수) : 0을 제외한 정수 
    - Exponential(지수) : 양의 정수     
        
- 변수 x의 값이 주어질 때 다항식의 값을 계산하는 함수 제공  
- 동일 이름의 Polynomial을 새로 정의할 수 있고, 이 경우 기존의 Polynomial을 지워진다.  




### 실행 예시 
~~~bash
$ f= 2x^5 +    3x  -4x^2-8
$ calc f 1
-7
$ g = x^3 + 2x^2 + 1
$ g = f+ g
$ print g
g = 2x^5+x^3-2x^2+3x-7
$ f = x^2-x + 1
$ print f
f = x^2-x+1
$ exit
~~~





