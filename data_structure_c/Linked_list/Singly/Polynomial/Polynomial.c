#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Polynomial.h"

// term object 생성 
TERM* create_term_instance()
{
    TERM* tmp = (TERM*)malloc(sizeof(TERM));
    tmp->coef = 0;
    tmp->expo = 0;
    tmp->next = NULL;
    return tmp;
}

// polynomial object 생성 
POLYNOMIAL* create_polynomial_instance(char name)
{
    POLYNOMIAL* ptr_poly = (POLYNOMIAL*)malloc(sizeof(POLYNOMIAL));
    ptr_poly->name = name;
    ptr_poly->size = 0;
    ptr_poly->first = NULL;
    return ptr_poly;
}

// target name의 polynomial을 polys에서 탐색
POLYNOMIAL* search(char name)
{
    for(int i=0; i<polys_num; i++)
    {
        if(polys[i]->name == name)
            return polys[i];
    }
    return NULL;
}

// 항의 값 계산 
int eval_term(TERM* term, int x)
{
    int result = term->coef;
    
    // c * x^e
    for(int i=0; i<term->expo; i++)
        result *= x;

    return result;
}

// 다항식 값 계산 */
int eval(POLYNOMIAL* poly, int x)
{
    int result = 0;
    TERM* tmp = poly->first;

    while(tmp)
    {
        result += eval_term(tmp, x);
        tmp = tmp->next;
    }
    return result;
}

// term 출력
void print_term(TERM* term)
{
    if(term->next)
    {
        if(term->coef != 1 && term->coef != -1)
        {
            if(term->coef > 0)
                printf("%d",term->coef);
            else
                printf("\b%d",term->coef);
        }

        if(term->expo == 1)
            printf("x+");
        else
            printf("x^%d+",term->expo);
    }
    else
        printf("\b%+d",term->coef);
}

// polynomial 출력
void print_poly(POLYNOMIAL* poly)
{
    printf("%c= ", poly->name);
    TERM* tmp = poly->first;

    while(tmp)
    {
        print_term(tmp);
        tmp = tmp->next;
    }
    printf("\n");
}


/* 
    poly가 가리키는 다항식에 새로운 하나의 항 (coef,expo)를 추가
    - 추가하려는 항과 동일한 차수의 항이 이미 존재하는 경우 : 기존 항의 계수만 변경
    - 아닌 경우 : 새로운 항 삽입 (항들은 차수의 내림차순으로 항상 정렬 됨)
*/
void add_term(POLYNOMIAL* poly, int c, int e)
{
    if(!c)
        return;

    TERM* prev = NULL;
    TERM* curr = poly->first;

    while(curr && curr->expo > e)
    {
        prev = curr;
        curr = curr->next;
    }

    if(curr && curr->expo == e)
    {
        curr->coef += c;

        // 계산 후 0이 될 경우
        if( !(curr->coef) )
        {
            if(!prev)
                poly->first = curr->next;
            else
                prev->next = curr->next;

            poly->size--;
            free(curr);
        }
        return;
    }

    TERM* tmp = create_term_instance();
    tmp->coef = c;
    tmp->expo = e;

    if(!prev)
    {
        tmp->next = poly->first;
        poly->first = tmp;
    }
    else
    {
        tmp->next = curr;
        prev->next = tmp;
    }
    poly->size++;
}


void destroy_polynomial(POLYNOMIAL* ptr_poly)
{
    if(!ptr_poly)
        return;

    TERM* ptr_term = ptr_poly->first, *tmp;
    
    while(ptr_term)
    {
        tmp = ptr_term;
        ptr_term = ptr_term->next;
        free(tmp);
    }
    free(ptr_poly);
}


void destroy_all()
{
    for(int i=0; i<polys_num; i++)
    {
        destroy_polynomial(polys[i]);
    }
    polys_num = 0;
}


void insert_polynomial(POLYNOMIAL* ptr_poly)
{
    for(int i=0; i<polys_num; i++)
    {
        if(polys[i]->name == ptr_poly->name)
        {
            destroy_polynomial(polys[i]);  // 다항식을 덮어쓸 경우 기존 다항식은 free

            polys[i] = ptr_poly;
            return;
        }
    }
    polys[polys_num++] = ptr_poly;
}


int parse_and_add_term(POLYNOMIAL* ptr_poly, char* expr, int begin, int end)
{
    int     i = begin,
            sign_coef = 1, 
            expo = 0,
            coef = 0; 
    
    // parse sign 
    if(expr[i] == '+')
        i++;
    else if(expr[i] == '-')
    {
        sign_coef = -1;
        i++;
    }

    // parse abs coef   ex. 34x = 3 -> 3*10 + 4 -> coef =34 , x => coef = 0
    while(i<end && '0' <= expr[i] && expr[i] <= '9')
    {
        coef = coef*10 + (int)(expr[i] - '0');
        i++;
    }

    // assign sign      coef가 0인 경우 계수는 1 or -1 
    if(!coef)
        coef = sign_coef;
    else
        coef *= sign_coef;

    // 더 이상 term을 구성하는 문자가 없다면 상수항을 의미한다.
    if(i >= end)
    {
        add_term(ptr_poly, coef, 0);
        return 1;
    }

    // 계수 다음에 미지수로 x가 아닌 다른 문자가 있으면 error
    if(expr[i] != 'x')
        return 0;
    i++;

    // 미지수 x다음 문자열이 끝나면 1차항을 의미한다.
    if(i>=end)
    {
        add_term(ptr_poly, coef, 1);
        return 1;
    }

    // x다음 ^가 아닌 다른 문자가 있으면 error
    if(expr[i] != '^')
        return 0;
    i++;

    // parse expo
    while(i<end && '0' <= expr[i] && expr[i] <= '9')
    {
        expo = expo*10 + (int)(expr[i] - '0');
        i++;
    }

    add_term(ptr_poly, coef, expo);
    return 1;
}


POLYNOMIAL* create_by_parse_polynomial(char name, char* body)
{
    POLYNOMIAL* ptr_poly = create_polynomial_instance(name);
    int         begin_term=0,           // [term start index
                i=0,                    // term end index) 
                body_len=strlen(body);

    // parse and create terms   ex. f=12x^3-x^2+13 => |12x^3|-x^2|+13|
    while( i<body_len )
    {
        // + or - 기호 인식
        if(body[i] == '+' || body[i] == '-')
            i++;
        
        // 하나의 항이 끝날때 까지 index 증가 => body[begin_term, i)까지가 하나의 term
        while(i<body_len && body[i] != '+' && body[i] != '-')
            i++;

        int result = parse_and_add_term(ptr_poly, body, begin_term, i);

        // 잘못된 term인 경우 0을 반환하기 때문에 다항식 자체를 destroy한다.
        if(!result)
        {
            destroy_polynomial(ptr_poly);
            return NULL;
        }
        begin_term = i; // 다음 항 시작 위치
    }
    return ptr_poly;
}


POLYNOMIAL* create_by_add_two_polynomias(char name, char f, char g)
{
    POLYNOMIAL  * ptr_poly = create_polynomial_instance(name),
                * f_pol = search(f),
                * g_pol = search(g);
               
    if(!f_pol)
    {
        printf("polynomial '%c' does not exists.\n", f);
        return NULL;
    }    
    if(!g_pol)
    {
        printf("polynomial '%c' does not exists.\n", g);
        return NULL;
    }
    
    TERM    * ftmp = f_pol->first,
            * gtmp = g_pol->first;


    for(int i=0; i<f_pol->size; i++)
    {
        add_term(ptr_poly, ftmp->coef, ftmp->expo);
        ftmp = ftmp->next;
    }

    for(int i=0; i<g_pol->size; i++)
    {
        add_term(ptr_poly, gtmp->coef, gtmp->expo);
        gtmp = gtmp->next;
    }
    

    return ptr_poly;
}


